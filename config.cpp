#include "config.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDoubleSpinBox>
#include <QScrollArea>
#include "global.h"
#include <QGroupBox>
#include <math.h>
#include "tinyxml.h"
#include <tinystr.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QRadioButton>
#include <importation.h>


config::config()
{
    this->setWindowTitle("Configuration");
    this->setFixedSize(350,950);

    QTabWidget *onglets = new QTabWidget(this);

    QGroupBox *Simulation_parameter = new QGroupBox(tr(""));
    QLabel *fsLabel = new QLabel(tr("Sampling frequency:"));
    sampling_frequency = new QDoubleSpinBox;
    sampling_frequency->setRange(0,20000000);
    sampling_frequency->setValue(fs);
    sampling_frequency->setSuffix(" Hz");

    QLabel *NLabel = new QLabel(tr("Step number"));
    Npoint = new QSpinBox;
    Npoint->setRange(0, 500000000);
    Npoint->setValue(N);

    QLabel *Npixel = new QLabel(tr("Number of pixels"));
    Npixels = new QSpinBox;
    Npixels->setRange(1, 40);
    Npixels->setValue(Npix);

    QLabel *NfitLabel = new QLabel(tr("Number of points for fit"));
    N_fit = new QSpinBox;
    N_fit->setRange(1, 10);
    N_fit->setValue(Nfit);

    QLabel *energyLabel = new QLabel(tr("Energy of the pulse:"));
    pulse_energy = new QDoubleSpinBox;
    pulse_energy->setSuffix(" eV");
    pulse_energy->setRange(200,12000);
    pulse_energy->setValue(energy);

    QLabel *binLabel = new QLabel(tr("Bin width:"));
    bin = new QDoubleSpinBox;
    bin->setSuffix(" eV");
    bin->setRange(0,2);
    bin->setValue(binWidth);

    QVBoxLayout *SimuLayout = new QVBoxLayout;
    SimuLayout->addWidget(fsLabel);
    SimuLayout->addWidget(sampling_frequency);
    SimuLayout->addWidget(NLabel);
    SimuLayout->addWidget(Npoint);
    SimuLayout->addWidget(Npixel);
    SimuLayout->addWidget(Npixels);
    SimuLayout->addWidget(NfitLabel);
    SimuLayout->addWidget(N_fit);
    SimuLayout->addWidget(energyLabel);
    SimuLayout->addWidget(pulse_energy);
    SimuLayout->addWidget(binLabel);
    SimuLayout->addWidget(bin);
    Simulation_parameter->setLayout(SimuLayout);
    Simulation_parameter->setFixedHeight(320);


    QGroupBox *Saving = new QGroupBox(tr(""));
    Ites = new QCheckBox("I(TES)");
    Error = new QCheckBox("Error signal");
    Feedback = new QCheckBox("Feedback signal");
    IQ = new QCheckBox("IQ module");
    QVBoxLayout *SaveLayout = new QVBoxLayout;
    SaveLayout->addWidget(Ites);
    SaveLayout->addWidget(Error);
    SaveLayout->addWidget(Feedback);
    SaveLayout->addWidget(IQ);
    Saving->setLayout(SaveLayout);
    Saving->setFixedHeight(250);

    QGroupBox *DDS_parameter = new QGroupBox(tr(""));
    QLabel *NptLabel = new QLabel(tr("Number of value in table as a power of 2 :"));
    N_pt = new QSpinBox;
    N_pt->setRange(1,15);
    N_pt->setValue((int)(std::log2(Npt)));

    QLabel *NprLabel = new QLabel(tr("Number of bits to encode a value:"));
    N_pr = new QSpinBox;
    N_pr->setRange(1,26);
    N_pr->setValue((int)(std::log2(Npr)));

    QLabel *interpolLabel = new QLabel(tr("Power of 2 as interpolation factor:"));
    interpol = new QSpinBox;
    interpol->setRange(1,15);
    interpol->setValue((int)(std::log2(interpolation)));

    QVBoxLayout *DDSLayout = new QVBoxLayout;
    DDSLayout->addWidget(NptLabel);
    DDSLayout->addWidget(N_pt);
    DDSLayout->addWidget(NprLabel);
    DDSLayout->addWidget(N_pr);
    DDSLayout->addWidget(interpolLabel);
    DDSLayout->addWidget(interpol);
    DDS_parameter->setLayout(DDSLayout);
    DDS_parameter->setFixedHeight(250);


    QGroupBox *LC_TES_parameter = new QGroupBox(tr(""));
    QLabel *I0Label = new QLabel(tr("I0 :"));
    Int0 = new QDoubleSpinBox;
    Int0->setSuffix(" µA");
    Int0->setValue(I0*pow(10,6));

    QLabel *R0Label = new QLabel(tr("R0 :"));
    Res0 = new QDoubleSpinBox;
    Res0->setSuffix(" mOhms");
    Res0->setValue(R0*pow(10,3));

    QLabel *T0Label = new QLabel(tr("T0 :"));
    Temp0 =new QDoubleSpinBox;
    Temp0->setSuffix(" mK");
    Temp0->setValue(T0*pow(10,3));

    QLabel *VpLabel = new QLabel(tr("Vp :"));
    Vpol = new QDoubleSpinBox;
    Vpol->setSuffix(" nV");
    Vpol->setValue(Vp*pow(10,9));

    QLabel *alphaLabel = new QLabel(tr("alpha :"));
    alpha_cst = new QDoubleSpinBox;
    alpha_cst->setValue(alpha);

    QLabel *betaLabel = new QLabel(tr("beta :"));
    beta_cst = new QDoubleSpinBox;
    beta_cst->setValue(beta);

    QLabel *RlLabel = new QLabel(tr("Rl :"));
    Rl_cst = new QDoubleSpinBox;
    Rl_cst->setSuffix(" µOhms");
    Rl_cst->setValue(Rl*pow(10,6));

    QLabel *CthermLabel = new QLabel(tr("C_therm :"));
    C_therm = new QDoubleSpinBox;
    C_therm->setSuffix(" pJ/K");
    C_therm->setValue(Ctherm*pow(10,12));

    QLabel *Tbathlabel = new QLabel(tr("Tbath :"));
    T_bath = new QDoubleSpinBox;
    T_bath->setSuffix(" mK");
    T_bath->setValue(Tbath*pow(10,3));

    QLabel *TRLabel = new QLabel(tr("TR :"));
    TTR = new QDoubleSpinBox;
    TTR->setValue(TR);

    QLabel *LLabel = new QLabel(tr("L :"));
    LL = new QDoubleSpinBox;
    LL->setSuffix(" µH");
    LL->setValue(L*pow(10,6));

    QLabel *TESdslLabel = new QLabel(tr("Spectral linear density of TES :"));
    TESdsl = new QDoubleSpinBox;
    TESdsl->setRange(0,1000);
    TESdsl->setSuffix(" pA/sqrt(Hz)");
    TESdsl->setValue(TES_dsl*pow(10,12));

    QLabel *BTESLabel = new QLabel(tr("Noise bandwidth :"));
    B_TES = new QDoubleSpinBox;
    B_TES->setRange(0,20000000);
    B_TES->setSuffix(" Hz");
    B_TES->setValue(Btes);

    QLabel *fcLabel = new QLabel(tr("Fréquence de coupure du bruit du TES :"));
    f_c = new QDoubleSpinBox;
    f_c->setRange(0,20000000);
    f_c->setSuffix(" Hz");
    f_c->setValue(fc);

    QVBoxLayout *LCTESLayout = new QVBoxLayout;
    LCTESLayout->addWidget(I0Label);
    LCTESLayout->addWidget(Int0);
    LCTESLayout->addWidget(R0Label);
    LCTESLayout->addWidget(Res0);
    LCTESLayout->addWidget(T0Label);
    LCTESLayout->addWidget(Temp0);
    LCTESLayout->addWidget(VpLabel);
    LCTESLayout->addWidget(Vpol);
    LCTESLayout->addWidget(alphaLabel);
    LCTESLayout->addWidget(alpha_cst);
    LCTESLayout->addWidget(betaLabel);
    LCTESLayout->addWidget(beta_cst);
    LCTESLayout->addWidget(RlLabel);
    LCTESLayout->addWidget(Rl_cst);
    LCTESLayout->addWidget(CthermLabel);
    LCTESLayout->addWidget(C_therm);
    LCTESLayout->addWidget(Tbathlabel);
    LCTESLayout->addWidget(T_bath);
    LCTESLayout->addWidget(TRLabel);
    LCTESLayout->addWidget(TTR);
    LCTESLayout->addWidget(LLabel);
    LCTESLayout->addWidget(LL);
    LCTESLayout->addWidget(TESdslLabel);
    LCTESLayout->addWidget(TESdsl);
    LCTESLayout->addWidget(BTESLabel);
    LCTESLayout->addWidget(B_TES);
    LCTESLayout->addWidget(fcLabel);
    LCTESLayout->addWidget(f_c);
    LC_TES_parameter->setLayout(LCTESLayout);
    LC_TES_parameter->setFixedHeight(800);


    QGroupBox *Pattern_parameter = new QGroupBox(tr(""));
    QLabel *NpatLabel = new QLabel(tr("Number of point for pattern:"));
    N_pat = new QSpinBox;
    N_pat->setRange(0,8192);
    N_pat->setValue(Npat);

    QVBoxLayout *patternLayout = new QVBoxLayout;
    patternLayout->addWidget(NpatLabel);
    patternLayout->addWidget(N_pat);
    Pattern_parameter->setLayout(patternLayout);
    Pattern_parameter->setFixedHeight(100);


    QGroupBox *Decimation_filter_parameter = new QGroupBox(tr(""));
    QLabel *decimationLabel = new QLabel(tr("Decimation factor:"));
    decimation_f = new QSpinBox;
    decimation_f->setRange(0,1000);
    decimation_f->setValue(decimation);

    QLabel *orderLabel = new QLabel(tr("Filter order:"));
    filter_order = new QSpinBox;
    filter_order->setValue(order);

    QVBoxLayout *filterLayout = new QVBoxLayout;
    filterLayout->addWidget(decimationLabel);
    filterLayout->addWidget(decimation_f);
    filterLayout->addWidget(orderLabel);
    filterLayout->addWidget(filter_order);
    Decimation_filter_parameter->setLayout(filterLayout);
    Decimation_filter_parameter->setFixedHeight(150);


    QGroupBox *BBFB_parameter = new QGroupBox(tr(""));
    QLabel *GainLabel = new QLabel(tr("Gain:"));
    gain_bbfb = new QDoubleSpinBox;
    gain_bbfb->setDecimals(10);
    gain_bbfb->setValue(G);

    QLabel *delayLabel = new QLabel(tr("Delay step:"));
    delay_step = new QSpinBox;
    delay_step->setValue(delay);

    QVBoxLayout *bbfbLayout = new QVBoxLayout;
    bbfbLayout->addWidget(GainLabel);
    bbfbLayout->addWidget(gain_bbfb);
    bbfbLayout->addWidget(delayLabel);
    bbfbLayout->addWidget(delay_step);
    BBFB_parameter->setLayout(bbfbLayout);
    BBFB_parameter->setFixedHeight(150);


    QGroupBox *DAC_parameter = new QGroupBox(tr(""));
    QLabel *FSLabel = new QLabel(tr("Full scale:"));
    full_scale = new QDoubleSpinBox;
    full_scale->setSuffix(" mA");
    full_scale->setValue(PE_DAC*pow(10,3));

    QLabel *bitLabel = new QLabel(tr("Number of bits:"));
    DAC_bits = new QSpinBox;
    DAC_bits->setValue(DAC_bit);

    QLabel *BLabel = new QLabel(tr("Noise bandwidth:"));
    DAC_B = new QDoubleSpinBox;
    DAC_B->setSuffix(" Hz");
    DAC_B->setRange(0,20000000);
    DAC_B->setValue(B_DAC);

    QLabel *dslfLabel = new QLabel(tr("Spectral linear density of feedback:"));
    DACdslf = new QDoubleSpinBox;
    DACdslf->setSuffix(" pA/sqrt(Hz)");
    DACdslf->setRange(0,1000);
    DACdslf->setValue(DAC_dsl*pow(10,12));

    QLabel *dslbLabel = new QLabel(tr("Relative level of noise for bias DAC:"));
    DACdslb = new QDoubleSpinBox;
    DACdslb->setSuffix(" dB");
    DACdslb->setRange(0,1000);
    DACdslb->setValue(-(std::log10(2*DAC_dsl_b))*20);

    QVBoxLayout *dacLayout = new QVBoxLayout;
    dacLayout->addWidget(FSLabel);
    dacLayout->addWidget(full_scale);
    dacLayout->addWidget(bitLabel);
    dacLayout->addWidget(DAC_bits);
    dacLayout->addWidget(BLabel);
    dacLayout->addWidget(DAC_B);
    dacLayout->addWidget(dslfLabel);
    dacLayout->addWidget(DACdslf);
    dacLayout->addWidget(dslbLabel);
    dacLayout->addWidget(DACdslb);
    DAC_parameter->setLayout(dacLayout);
    DAC_parameter->setFixedHeight(300);


    QGroupBox *ADC_parameter = new QGroupBox(tr(""));
    QLabel *FSadcLabel = new QLabel(tr("Full scale:"));
    full_scale_adc = new QDoubleSpinBox;
    full_scale_adc->setSuffix(" V");
    full_scale_adc->setValue(PE_ADC);

    QLabel *bitadcLabel = new QLabel(tr("Number of bits:"));
    ADC_bits = new QSpinBox;
    ADC_bits->setValue(ADC_bit);

    QLabel *BadcLabel = new QLabel(tr("Noise bandwidth:"));
    ADC_B = new QDoubleSpinBox;
    ADC_B->setSuffix(" Hz");
    ADC_B->setRange(0,20000000);
    ADC_B->setValue(B_ADC);

    QLabel *dslLabel = new QLabel(tr("Spectral linear density of feedback:"));
    ADCdsl = new QDoubleSpinBox;
    ADCdsl->setSuffix(" nV/sqrt(Hz)");
    ADCdsl->setRange(0,1000);
    ADCdsl->setValue(ADC_dsl*pow(10,9));

    QVBoxLayout *adcLayout = new QVBoxLayout;
    adcLayout->addWidget(FSadcLabel);
    adcLayout->addWidget(full_scale_adc);
    adcLayout->addWidget(bitadcLabel);
    adcLayout->addWidget(ADC_bits);
    adcLayout->addWidget(BadcLabel);
    adcLayout->addWidget(ADC_B);
    adcLayout->addWidget(dslLabel);
    adcLayout->addWidget(ADCdsl);
    ADC_parameter->setLayout(adcLayout);
    ADC_parameter->setFixedHeight(250);


    QGroupBox *LNA_parameter = new QGroupBox(tr(""));
    QLabel *GLNALabel = new QLabel(tr("LNA gain:"));
    GLNA = new QDoubleSpinBox;
    GLNA->setValue(G_LNA);

    QLabel *LNAdslLabel = new QLabel(tr("Spectral linear density:"));
    LNAdsl = new QDoubleSpinBox;
    LNAdsl->setSuffix(" pA/sqrt(Hz)");
    LNAdsl->setRange(0,1000);
    LNAdsl->setValue(LNA_dsl*pow(10,9));

    QLabel *BLNALabel = new QLabel(tr("Noise bandwidth:"));
    BLNA = new QDoubleSpinBox;
    BLNA->setSuffix(" Hz");
    BLNA->setRange(0,20000000);
    BLNA->setValue(B_LNA);

    QVBoxLayout *LNALayout = new QVBoxLayout;
    LNALayout->addWidget(GLNALabel);
    LNALayout->addWidget(GLNA);
    LNALayout->addWidget(LNAdslLabel);
    LNALayout->addWidget(LNAdsl);
    LNALayout->addWidget(BLNALabel);
    LNALayout->addWidget(BLNA);
    LNA_parameter->setLayout(LNALayout);
    LNA_parameter->setFixedHeight(200);


    QGroupBox *SQUID_parameter = new QGroupBox(tr(""));
    QLabel *GSQUIDLabel = new QLabel(tr("SQUID gain:"));
    GSQUID = new QDoubleSpinBox;
    GSQUID->setRange(0,10000);
    GSQUID->setValue(G_SQUID);

    QLabel *SQUIDdslLabel = new QLabel(tr("Spectral linear density:"));
    SQUIDdsl = new QDoubleSpinBox;
    SQUIDdsl->setSuffix(" pA/sqt(Hz)");
    SQUIDdsl->setValue(SQUID_dsl*pow(10,12));

    QLabel *BSQUIDLabel = new QLabel(tr("Noise bandwidth:"));
    BSQUID = new QDoubleSpinBox;
    BSQUID->setSuffix(" Hz");
    BSQUID->setRange(0,20000000);
    BSQUID->setValue(B_SQUID);

    QVBoxLayout *SQUIDLayout = new QVBoxLayout;
    SQUIDLayout->addWidget(GSQUIDLabel);
    SQUIDLayout->addWidget(GSQUID);
    SQUIDLayout->addWidget(SQUIDdslLabel);
    SQUIDLayout->addWidget(SQUIDdsl);
    SQUIDLayout->addWidget(BSQUIDLabel);
    SQUIDLayout->addWidget(BSQUID);
    SQUID_parameter->setLayout(SQUIDLayout);
    SQUID_parameter->setFixedHeight(200);

    onglets->setFixedSize(350,900);
    onglets->addTab(Simulation_parameter,"Simulation parameters");
    onglets->addTab(Saving,"Data saving");
    onglets->addTab(DDS_parameter,"DDS");
    onglets->addTab(LC_TES_parameter,"LC/TES");
    onglets->addTab(Pattern_parameter,"Pattern");
    onglets->addTab(Decimation_filter_parameter,"Decimation filter");
    onglets->addTab(BBFB_parameter,"BBFB");
    onglets->addTab(DAC_parameter,"DAC");
    onglets->addTab(ADC_parameter,"ADC");
    onglets->addTab(LNA_parameter,"LNA");
    onglets->addTab(SQUID_parameter,"SQUID");

    Valider = new QPushButton("Valider",this);
    Load = new QPushButton("Load",this);
    Annuler = new QPushButton("Annuler",this);
    connect(Valider,SIGNAL(clicked()), this, SLOT(setVal()));
    connect(Load,SIGNAL(clicked()), this, SLOT(load()));
    connect(Annuler,SIGNAL(clicked()), this, SLOT(close()));
    connect(Valider,SIGNAL(clicked()), this, SLOT(saved()));
    Valider->move(20,910);
    Load->move(127,910);
    Annuler->move(235,910);
}

config::~config()
{

}

void config::saved()
{
    QMessageBox::information(this, "", "Configuration saved");
}

void config::setVal()
{
    fs=sampling_frequency->value();
    N=Npoint->value();
    Npix=Npixels->value();
    Nfit=N_fit->value();
    energy=pulse_energy->value();
    Npt=pow(2,N_pt->value());
    Npr=pow(2,N_pr->value());
    interpolation=pow(2,interpol->value());
    I0=(Int0->value())*pow(10,-6);
    R0=(Res0->value())*pow(10,-3);
    T0=(Temp0->value())*pow(10,-3);
    Vp=(Vpol->value())*pow(10,-9);
    alpha=alpha_cst->value();
    beta=beta_cst->value();
    Rl=(Rl_cst->value())*pow(10,-6);
    Ctherm=(C_therm->value())*pow(10,-12);
    Tbath=T_bath->value()*pow(10,-3);
    TR=TTR->value();
    L=(LL->value())*pow(10,-6);
    TES_dsl=(TESdsl->value())*pow(10,-12);
    Btes=B_TES->value();
    fc=f_c->value();
    Npat=N_pat->value();
    decimation=decimation_f->value();
    G=gain_bbfb->value();
    delay=delay_step->value();
    PE_DAC=(full_scale->value())*pow(10,-3);
    DAC_bit=DAC_bits->value();
    B_DAC=DAC_B->value();
    DAC_dsl_b=0.5*pow(10,-(DACdslb->value())/20);
    DAC_dsl=(DACdslf->value())*pow(10,-12);
    PE_ADC=full_scale_adc->value();
    ADC_bit=ADC_bits->value();
    B_ADC=ADC_B->value();
    ADC_dsl=(ADCdsl->value())*pow(10,-9);
    G_LNA=GLNA->value();
    LNA_dsl=(LNAdsl->value())*pow(10,-9);
    B_LNA=BLNA->value();
    G_SQUID=GSQUID->value();
    SQUID_dsl=(SQUIDdsl->value())*pow(10,-12);
    B_SQUID=BSQUID->value();
    binWidth=bin->value();
    saveIQ=IQ->checkState();
    saveItes=Ites->checkState();
    saveError=Error->checkState();
    saveFeedback=Feedback->checkState();
}

void config::load()
{  
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(),"XML (*.xml)");
    if (fichier!="")
    {
        Importation::setGlobal(fichier);
        sampling_frequency->setValue(fs);
        Npoint->setValue(N);
        Npixels->setValue(Npix);
        N_fit->setValue(Nfit);
        N_pt->setValue((int)(std::log2(Npt)));
        N_pr->setValue((int)(std::log2(Npr)));
        interpol->setValue((int)(std::log2(interpolation)));
        TESdsl->setValue(TES_dsl*pow(10,12));
        B_TES->setValue(Btes);
        f_c->setValue(fc);
        N_pat->setValue(Npat);
        pulse_energy->setValue(energy);
        decimation_f->setValue(decimation);
        filter_order->setValue(order);
        gain_bbfb->setValue(G);
        delay_step->setValue(delay);
        full_scale->setValue(PE_DAC*pow(10,3));
        DAC_bits->setValue(DAC_bit);
        DAC_B->setValue(B_DAC);
        DACdslf->setValue(DAC_dsl*pow(10,12));
        DACdslb->setValue(-(std::log10(2*DAC_dsl_b))*20);
        full_scale_adc->setValue(PE_ADC);
        ADC_bits->setValue(ADC_bit);
        ADCdsl->setValue(ADC_dsl*pow(10,9));
        ADC_B->setValue(B_ADC);
        GLNA->setValue(G_LNA);
        LNAdsl->setValue(LNA_dsl*pow(10,9));
        BLNA->setValue(B_LNA);
        GSQUID->setValue(G_SQUID);
        SQUIDdsl->setValue(SQUID_dsl*pow(10,12));
        BSQUID->setValue(B_SQUID);
        Res0->setValue(R0*pow(10,3));
        Temp0->setValue(T0*pow(10,3));
        Vpol->setValue(Vp*pow(10,9));
        alpha_cst->setValue(alpha);
        beta_cst->setValue(beta);
        Rl_cst->setValue(Rl*pow(10,6));
        C_therm->setValue(Ctherm*pow(10,12));
        T_bath->setValue(Tbath*pow(10,3));
        Int0->setValue(I0*pow(10,6));
        TTR->setValue(TR);
        LL->setValue(L*pow(10,6));
        bin->setValue(binWidth);
    }
}
