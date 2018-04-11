#include "importation.h"
#include <iostream>
#include <stdlib.h>
#include <tinyxml.h>
#include <tinystr.h>
#include "global.h"
#include <math.h>
#include <string>

using namespace std;

Importation::Importation()
{

}

Importation::~Importation()
{

}

void Importation::setGlobal(QString path)
{
    const char *c=path.toStdString().c_str();
    TiXmlDocument doc(c);
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
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &binWidth);
    elem = elem->NextSiblingElement();
    elem->QueryDoubleAttribute("value", &ntherm);
}

void Importation::saveConfig(QString path)
{
    TiXmlDocument doc;

    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild(decl);

    TiXmlElement * global = new TiXmlElement( "Global_var" );
    doc.LinkEndChild(global);

    TiXmlElement *var = new TiXmlElement( "var" );
    global->LinkEndChild(var);
    var->SetAttribute("name", "fs");
    var->SetAttribute("value", fs);
    TiXmlElement *var1 = new TiXmlElement( "var" );
    global->LinkEndChild(var1);
    var1->SetAttribute("name", "N");
    var1->SetAttribute("value", N);
    TiXmlElement *var2 = new TiXmlElement( "var" );
    global->LinkEndChild(var2);
    var2->SetAttribute("name", "Npix");
    var2->SetAttribute("value", Npix);
    TiXmlElement *var3 = new TiXmlElement( "var" );
    global->LinkEndChild(var3);
    var3->SetAttribute("name", "Nfit");
    var3->SetAttribute("value", Nfit);
    TiXmlElement *var4 = new TiXmlElement( "var" );
    global->LinkEndChild(var4);
    var4->SetAttribute("name", "Npt");
    var4->SetAttribute("value", (int)(log2(Npt)));
    TiXmlElement *var5 = new TiXmlElement( "var" );
    global->LinkEndChild(var5);
    var5->SetAttribute("name", "Npr");
    var5->SetAttribute("value", (int)(log2(Npr)));
    TiXmlElement *var6 = new TiXmlElement( "var" );
    global->LinkEndChild(var6);
    var6->SetAttribute("name", "interpolation");
    var6->SetAttribute("value", (int)(log2(interpolation)));
    TiXmlElement *var7 = new TiXmlElement( "var" );
    global->LinkEndChild(var7);
    var7->SetAttribute("name", "TES_dsl");
    var7->SetDoubleAttribute("value", TES_dsl*pow(10,12));
    TiXmlElement *var8 = new TiXmlElement( "var" );
    global->LinkEndChild(var8);
    var8->SetAttribute("name", "Btes");
    var8->SetAttribute("value", Btes);
    TiXmlElement *var9 = new TiXmlElement( "var" );
    global->LinkEndChild(var9);
    var9->SetAttribute("name", "fc");
    var9->SetAttribute("value", fc);
    TiXmlElement *var10 = new TiXmlElement( "var" );
    global->LinkEndChild(var10);
    var10->SetAttribute("name", "Npat");
    var10->SetAttribute("value", Npat);
    TiXmlElement *var11 = new TiXmlElement( "var" );
    global->LinkEndChild(var11);
    var11->SetAttribute("name", "energy");
    var11->SetAttribute("value", energy);
    TiXmlElement *var12 = new TiXmlElement( "var" );
    global->LinkEndChild(var12);
    var12->SetAttribute("name", "decimation");
    var12->SetAttribute("value", decimation);
    TiXmlElement *var13 = new TiXmlElement( "var" );
    global->LinkEndChild(var13);
    var13->SetAttribute("name", "G");
    var13->SetDoubleAttribute("value", G);
    TiXmlElement *var14 = new TiXmlElement( "var" );
    global->LinkEndChild(var14);
    var14->SetAttribute("name", "delay");
    var14->SetAttribute("value", delay);
    TiXmlElement *var15 = new TiXmlElement( "var" );
    global->LinkEndChild(var15);
    var15->SetAttribute("name", "PE_DAC");
    var15->SetDoubleAttribute("value", PE_DAC*pow(10,3));
    TiXmlElement *var16 = new TiXmlElement( "var" );
    global->LinkEndChild(var16);
    var16->SetAttribute("name", "DAC_bit");
    var16->SetAttribute("value", DAC_bit);
    TiXmlElement *var17 = new TiXmlElement( "var" );
    global->LinkEndChild(var17);
    var17->SetAttribute("name", "B_DAC");
    var17->SetAttribute("value", B_DAC);
    TiXmlElement *var18 = new TiXmlElement( "var" );
    global->LinkEndChild(var18);
    var18->SetAttribute("name", "DAC_dsl");
    var18->SetDoubleAttribute("value", DAC_dsl*pow(10,12));
    TiXmlElement *var19 = new TiXmlElement( "var" );
    global->LinkEndChild(var19);
    var19->SetAttribute("name", "DAC_dsl_b");
    var19->SetAttribute("value", -(log10(2*DAC_dsl_b))*20);
    TiXmlElement *var20 = new TiXmlElement( "var" );
    global->LinkEndChild(var20);
    var20->SetAttribute("name", "PE_ADC");
    var20->SetAttribute("value", PE_ADC);
    TiXmlElement *var21 = new TiXmlElement( "var" );
    global->LinkEndChild(var21);
    var21->SetAttribute("name", "ADC_bit");
    var21->SetAttribute("value", ADC_bit);
    TiXmlElement *var22 = new TiXmlElement( "var" );
    global->LinkEndChild(var22);
    var22->SetAttribute("name", "ADC_dsl");
    var22->SetDoubleAttribute("value", ADC_dsl*pow(10,9));
    TiXmlElement *var23 = new TiXmlElement( "var" );
    global->LinkEndChild(var23);
    var23->SetAttribute("name", "B_ADC");
    var23->SetAttribute("value", B_ADC);
    TiXmlElement *var24 = new TiXmlElement( "var" );
    global->LinkEndChild(var24);
    var24->SetAttribute("name", "G_LNA");
    var24->SetDoubleAttribute("value", G_LNA);
    TiXmlElement *var25 = new TiXmlElement( "var" );
    global->LinkEndChild(var25);
    var25->SetAttribute("name", "LNA_dsl");
    var25->SetDoubleAttribute("value", LNA_dsl*pow(10,9));
    TiXmlElement *var26 = new TiXmlElement( "var" );
    global->LinkEndChild(var26);
    var26->SetAttribute("name", "B_LNA");
    var26->SetAttribute("value", B_LNA);
    TiXmlElement *var27 = new TiXmlElement( "var" );
    global->LinkEndChild(var27);
    var27->SetAttribute("name", "G_SQUID");
    var27->SetDoubleAttribute("value", G_SQUID);
    TiXmlElement *var28 = new TiXmlElement( "var" );
    global->LinkEndChild(var28);
    var28->SetAttribute("name", "SQUID_dsl");
    var28->SetDoubleAttribute("value", SQUID_dsl*pow(10,12));
    TiXmlElement *var29 = new TiXmlElement( "var" );
    global->LinkEndChild(var29);
    var29->SetAttribute("name", "B_SQUID");
    var29->SetAttribute("value", B_SQUID);
    TiXmlElement *var30 = new TiXmlElement( "var" );
    global->LinkEndChild(var30);
    var30->SetAttribute("name", "R0");
    var30->SetDoubleAttribute("value", R0*pow(10,3));
    TiXmlElement *var31 = new TiXmlElement( "var" );
    global->LinkEndChild(var31);
    var31->SetAttribute("name", "T0");
    var31->SetDoubleAttribute("value", T0*pow(10,3));
    TiXmlElement *var32 = new TiXmlElement( "var" );
    global->LinkEndChild(var32);
    var32->SetAttribute("name", "Vp");
    var32->SetDoubleAttribute("value", Vp*pow(10,9));
    TiXmlElement *var33 = new TiXmlElement( "var" );
    global->LinkEndChild(var33);
    var33->SetAttribute("name", "alpha");
    var33->SetDoubleAttribute("value", alpha);
    TiXmlElement *var34 = new TiXmlElement( "var" );
    global->LinkEndChild(var34);
    var34->SetAttribute("name", "beta");
    var34->SetDoubleAttribute("value", beta);
    TiXmlElement *var35 = new TiXmlElement( "var" );
    global->LinkEndChild(var35);
    var35->SetAttribute("name", "Rl");
    var35->SetDoubleAttribute("value", Rl*pow(10,6));
    TiXmlElement *var36 = new TiXmlElement( "var" );
    global->LinkEndChild(var36);
    var36->SetAttribute("name", "Ctherm");
    var36->SetDoubleAttribute("value", Ctherm*pow(10,12));
    TiXmlElement *var37 = new TiXmlElement( "var" );
    global->LinkEndChild(var37);
    var37->SetAttribute("name", "Tbath");
    var37->SetDoubleAttribute("value", Tbath*pow(10,3));
    TiXmlElement *var38 = new TiXmlElement( "var" );
    global->LinkEndChild(var38);
    var38->SetAttribute("name", "I0");
    var38->SetDoubleAttribute("value", I0*pow(10,6));
    TiXmlElement *var39 = new TiXmlElement( "var" );
    global->LinkEndChild(var39);
    var39->SetAttribute("name", "TR");
    var39->SetDoubleAttribute("value", TR);
    TiXmlElement *var40 = new TiXmlElement( "var" );
    global->LinkEndChild(var40);
    var40->SetAttribute("name", "L");
    var40->SetDoubleAttribute("value", L*pow(10,6));
    TiXmlElement *var41 = new TiXmlElement( "var" );
    global->LinkEndChild(var41);
    var41->SetAttribute("name", "binWidth");
    var41->SetDoubleAttribute("value", binWidth);
    TiXmlElement *var42 = new TiXmlElement( "var" );
    global->LinkEndChild(var42);
    var42->SetAttribute("name", "ntherm");
    var42->SetDoubleAttribute("value", ntherm);
    const char *c=path.toStdString().c_str();
    doc.SaveFile(c);
}

void Importation::setInitial()
{
    fs=20000000;
    N=50000000;
    Npix=1;
    Nfit=3;
    Npt=pow(2,9);
    Npr=pow(2,18);
    interpolation=pow(2,11);
    TES_dsl=105*pow(10,-12);
    Btes=20000000;
    fc=560;
    Npat=2048;
    energy=3600;
    decimation=128;
    G=0.0001549644569;
    delay=1;
    PE_DAC=0.02;
    DAC_bit=16;
    B_DAC=20000000;
    DAC_dsl=28*pow(10,-12);
    DAC_dsl_b=0.5*pow(10,-160/20);
    PE_ADC=1.0;
    ADC_bit=12;
    ADC_dsl=6.448*pow(10,-9);
    B_ADC=20000000;
    G_LNA=83;
    LNA_dsl=258*pow(10,-9);
    B_LNA=20000000;
    G_SQUID=2931.0;
    SQUID_dsl=2.2*pow(10,-12);
    B_SQUID=20000000;
    R0=0.001;
    T0=0.09;
    Vp=51.5*pow(10,-9);
    alpha=75;
    beta=1.25;
    Rl=60*pow(10,-6);
    Ctherm=0.8*pow(10,-12);
    Tbath=0.055;
    I0=51.5*pow(10,-6);
    TR=4.08;
    L=2*pow(10,-6);
    binWidth=0.7;
    ntherm=3;
}
