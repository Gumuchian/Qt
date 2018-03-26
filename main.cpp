#include "mainwindow.h"
#include <QApplication>
#include "global.h"
#include <iostream>
#include <fstream>
#include "importation.h"

int main(int argc, char *argv[])
{

    Importation import;
    std::fstream file;
    file.open("global.txt",std::ios::in);

    file >> fs;
    file >> N;
    file >> Npix;
    file >> Nfit;
    file >> Npt;Npt=pow(2,Npt);
    file >> Npr;Npr=pow(2,Npr);
    file >> interpolation;interpolation=pow(2,interpolation);
    file >> TES_dsl;TES_dsl=TES_dsl*pow(10,-12);
    file >> Btes;
    file >> fc;
    file >> Npat;
    file >> energy;
    file >> decimation;
    file >> order;
    file >> G;
    file >> delay;
    file >> PE_DAC;
    file >> DAC_bit;
    file >> B_DAC;
    file >> DAC_dsl;DAC_dsl=DAC_dsl*pow(10,-12);
    file >> DAC_dsl_b;DAC_dsl_b=0.5*pow(10,-DAC_dsl_b/20);
    file >> PE_ADC;
    file >> ADC_bit;
    file >> ADC_dsl;ADC_dsl=ADC_dsl*pow(10,-9);
    file >> B_ADC;
    file >> G_LNA;
    file >> LNA_dsl;LNA_dsl=LNA_dsl*pow(10,-9);
    file >> B_LNA;
    file >> G_SQUID;
    file >> SQUID_dsl;SQUID_dsl=SQUID_dsl*pow(10,-12);
    file >> B_SQUID;
    file >> R0;R0=R0*pow(10,-3);
    file >> T0;T0=T0*pow(10,-3);
    file >> Vp;Vp=Vp*pow(10,-9);
    file >> alpha;
    file >> beta;
    file >> Rl;Rl=Rl*pow(10,-6);
    file >> Ctherm;Ctherm=Ctherm*pow(10,-12);
    file >> Tbath;Tbath=Tbath*pow(10,-3);
    file >> I0;I0=I0*pow(10,-6);
    file >> TR;
    file >> L;L=L*pow(10,-6);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/icon.jpg"));
    MainWindow w;
    w.show();
    return app.exec();
}
