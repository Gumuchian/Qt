#include "importation.h"
#include <iostream>
#include <tinyxml.h>
#include <tinystr.h>
#include "global.h"
#include <math.h>

using namespace std;

Importation::Importation()
{

}

void Importation::setGlobal()
{
    TiXmlDocument doc("global.xml");
    if(!doc.LoadFile()){
        cerr << "erreur lors du chargement" << endl;
        cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
    }
    TiXmlHandle hdl(&doc);
    TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();
    if(!elem)
    {
        cerr << "le nœud à atteindre n'existe pas" << endl;
    }
    elem->QueryDoubleAttribute("value", &fs);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &N);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &Npix);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &Nfit);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &Npt);Npt=(int)pow(2,Npt);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &Npr);Npr=(int)pow(2,Npr);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &interpolation);interpolation=(int)pow(2,interpolation);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &TES_dsl);TES_dsl=TES_dsl*pow(10,-12);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &Btes);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &fc);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &Npat);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &energy);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &decimation);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &G);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &delay);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &PE_DAC);PE_DAC=PE_DAC*pow(10,-3);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &DAC_bit);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &B_DAC);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &DAC_dsl);DAC_dsl=DAC_dsl*pow(10,-12);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &DAC_dsl_b);DAC_dsl_b=0.5*pow(10,-DAC_dsl_b/20);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &PE_ADC);
    elem = elem->NextSiblingElement();
    elem->QueryIntAttribute("value", &ADC_bit);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &ADC_dsl);ADC_dsl=ADC_dsl*pow(10,-9);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &B_ADC);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &G_LNA);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &LNA_dsl);LNA_dsl=LNA_dsl*pow(10,-9);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &B_LNA);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &G_SQUID);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &SQUID_dsl);SQUID_dsl=SQUID_dsl*pow(10,-12);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &B_SQUID);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &R0);R0=R0*pow(10,-3);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &T0);T0=T0*pow(10,-3);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &Vp);Vp=Vp*pow(10,-9);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &alpha);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &beta);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &Rl);Rl=Rl*pow(10,-6);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &Ctherm);Ctherm=Ctherm*pow(10,-12);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &Tbath);Tbath=Tbath*pow(10,-3);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &I0);I0=I0*pow(10,-6);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &TR);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &L);L=L*pow(10,-6);
}
