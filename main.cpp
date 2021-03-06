#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include "moleculardynamics.h"
#include <QSurfaceFormat>
#include <QGLFormat>
#include <QOpenGLContext>

#include <settings.h>
#include <system.h>
#include <thermostat.h>
#include <statisticssampler.h>
#include <iostream>
#include <QFontDatabase>
using namespace std;

# if defined (Q_OS_IOS)
extern "C" int qtmn (int argc, char * argv [])
#else
int main (int argc, char * argv [])
# endif
{
    qmlRegisterType<MolecularDynamics>("MolecularDynamics", 1, 0, "MolecularDynamics");

    QGuiApplication app(argc, argv);
    QQuickView view;

    QFontDatabase::addApplicationFont(":/fonts/SourceSansPro-Regular.ttf");
    app.setFont(QFont("Source Sans Pro"));

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///Molecules.qml"));
    view.show();

    return app.exec();
}
