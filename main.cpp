#include <QApplication>
#include "mainwindow.h"
#include "importation.h"
#include <QString>
#include "adc.h"
#include "simulation.h"
#include "global.h"

using namespace boost::numeric::ublas;

int main(int argc, char *argv[])
{
    saveItes=false;
    saveError=false;
    saveIQ=false;
    saveFeedback=false;
    QApplication app(argc, argv);
    Importation::setInitial();
    app.setWindowIcon(QIcon(":/images/icon.jpg"));
    MainWindow w;
    w.show();
    return app.exec();
}
