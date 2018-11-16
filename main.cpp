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
    //Importation::setInitial();
    //int nd=20,ni=20,nr=20;
    //Simulation sim(decimation,fs,Lcrit,TR,Gb,ntherm,Tbath,Ctherm,Rl,R0,T0,I0,Npt,Npr,interpolation,1,delay,nd,ni,nr,ADC_dsl,B_ADC,PE_ADC,ADC_bit,0,B_DAC,PE_DAC,DAC_bit,G_LNA,LNA_dsl,B_LNA,5.8*pow(10,-6),58*pow(10,-6),0.017,SQUID_dsl,B_SQUID,2048);
    //sim.EstimateOffset();
    //sim.computeImpulseResponse();
    //sim.EstimateEnergyCurve();
    //sim.simulate(10000000);
    return app.exec();
}
