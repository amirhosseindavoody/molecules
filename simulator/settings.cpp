#include <settings.h>
Settings::Settings() {
    FCC_b = 2.0;
    temperature = 1.0;
    dt = 0.02;
    r_cut = 2.5;
    thermostat_relaxation_time = 1;
    gravity_force = 0;
    mass = 39.948;
    gravity_direction = -1;
    unit_cells_x = 10;
    unit_cells_y = 10;
    unit_cells_z = 10;
    nodes_x = 1;
    nodes_y = 1;
    nodes_z = 1;
    statistics_interval = 100;
    max_number_of_atoms = 10000;
    max_number_of_cells = 1000;
    thermostat_enabled = false;
    thermostat_frozen_enabled = false;
}
