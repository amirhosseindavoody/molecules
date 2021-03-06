#pragma once

class Atom;
class ThreadControl;
class Settings;
class MDIO;
class MDTimer;
class Random;
class UnitConverter;

#include <fstream>
#include <vector>
#include <QVector3D>

#define EMPTY -1

typedef double atomDataType;

using namespace std;

class System {
public:
    System();
    void apply_harmonic_oscillator();
    void countAtomTypes();

    void setup(Settings *settings_);
    void step();

    QVector3D systemSize() const;
    void reset();
    void setSystemSize(const QVector3D &systemSize, bool autoResetCells = true);
    double volume();
    double rCut() const;
    void setRCut(double rCut, bool autoResetCells = true);
    double dt() const;
    void setDt(double dt);
    double potentialEnergy() const;
    double time() const;
    void setTime(double time);
    double startTime() const;
    void setStartTime(double startTime);
    void printMaxPositionComponent();
    unsigned long numAtoms() const;
    void setNumAtoms(unsigned long numAtoms);
    bool didScaleVelocitiesDueToHighValues() const;
    void setDidScaleVelocitiesDueToHighValues(bool didScaleVelocitiesDueToHighValues);
    void resetCells();

    Settings *settings;
    MDIO *mdio;
    Random *rnd;
    UnitConverter *unit_converter;

    bool sample_statistics;
    unsigned long steps;
    unsigned long num_atoms_free;
    unsigned long num_atoms_fixed;
    unsigned long num_atoms_frozen;
    unsigned long num_atoms_ghost;
    double mass_inverse, pressure_forces;

    long count_periodic[3];


    vector<atomDataType> positions;
    vector<atomDataType> velocities;
    vector<atomDataType> accelerations;

    vector<unsigned long> atom_type;
    vector<float> initial_positions;
private:
    void allocate(int numberOfAtoms);
    void move();
    void mpi_move();
    void mpi_copy();
    void calculate_accelerations();
    void calculate_accelerations_many_frozen_atoms();
    void apply_gravity();
    void full_kick();
    void half_kick();

    void set_topology();
    void init_parameters();
    void create_FCC();
    inline bool atom_did_change_node(atomDataType* ri, int ku);
    inline bool atom_should_be_copied(atomDataType *ri, int ku);
    inline void cell_index_from_ijk(const int &i, const int &j, const int &k, unsigned int &cell_index);
    inline void cell_index_from_vector(unsigned int *mc, unsigned int &cell_index);
    void createForcesAndPotentialTable();
    void ensureAllAtomsAreInsideSystem();

    vector<vector<unsigned int> > move_queue;
    int numberOfPrecomputedTwoParticleForces;
    double deltaR2;
    double oneOverDeltaR2;
    QVector3D m_systemSize;
    QVector3D cellLength;
    vector<atomDataType> m_dataBuffer;
    vector<bool> atom_moved;
    vector<unsigned long> atom_ids;
    vector<int> head_all_atoms;
    vector<int> head_free_atoms;
    vector<int> linked_list_all_atoms;
    vector<int> linked_list_free_atoms;
    vector<bool> is_ghost_cell;
    vector<atomDataType> precomputed_forces;
    vector<atomDataType> precomputed_potential;
    unsigned int num_cells_including_ghosts_yz,cell_index, cell_index_2,num_cells_including_ghosts_xyz;
    unsigned int num_cells[3];
    unsigned int num_cells_including_ghosts[3];
    double shift_vector[6][3];
    unsigned int mc[3];  // Usually cell index vector
    unsigned int mc1[3]; // Usually cell index vector
    atomDataType m_rCut;
    double m_dt;
    atomDataType m_potentialEnergy;
    double m_time;
    double m_startTime;
    double one_over_r_cut_squared;
    unsigned long m_numAtoms;
    bool m_didScaleVelocitiesDueToHighValues;
};
