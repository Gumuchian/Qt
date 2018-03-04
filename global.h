#ifndef GLOBAL_H
#define GLOBAL_H
#include <math.h>

// Simulation parameters
static double fs=20000000; // sampling frequency
static int N=10000000; // simulation step
static int Npix=1; // pixels number
const double PI=3.14159265358979;
static int Nfit=3;
const int order_fit=2;



// DDS parameters
static int Npt=pow(2,9); // DDS values
static int Npr=pow(2,18); // DDS value accuracy
static int interpolation=pow(2,20-9); // Interpolation factor



// TES Noise parameters
static double TES_dsl=105*pow(10,-12); // Spectral linear density of a TES (DC) (A/sqrt(Hz))
static double Btes=20000000; // TES noise bandwidth
static double fc=560; // cut frequency of TES noise bandwidth



// Pulse and pattern parameters
static int Npat=2048;
const int Npul=200000;
static double energy=3600; // energy of the injected X-rays (eV)



// CIC or Butterworth
static int decimation=128; // down sampling factor
static int order=2; // CIC/Butterworth order, if Butterworth order must be equal to 2
static int Np=Npat*decimation; // don't touch !!



// BBFB
static double G=0.0001549644569; // Integrator gain
static int delay=1; // loop delay (simulation step)



// DAC
static double PE_DAC=0.02; // full scale (A)
static int DAC_bit=16; // number of bits of DAC
static double B_DAC=20000000; // DAC feedback noise bandwidth
static double DAC_dsl=28*pow(10,-12); // Spectral linear density of DAC feedback
static double DAC_dsl_b=0.5*pow(10,-140/20);



// ADC
static double PE_ADC=1.0;
static int ADC_bit=12; // number of bits of ADC
static double ADC_dsl=6.448*pow(10,-9); // Spectral linear density of ADC
static double B_ADC=20000000; // ADC noise bandwidth



// Filter
static double G_filter=1; // anti-aliasing/restaticruction filter gain



// LNA
static double G_LNA=83; // LNA gain
static double LNA_dsl=258*pow(10,-9); // Spectral linear density of LNA (V/sqrt(Hz))
//static double LNA_dsl=0;
static double B_LNA=20000000; // LNA noise bandwidth



// SQUID
static double G_SQUID=0.017/(5.8*pow(10,-6)); // SQUID transimpedance
static double SQUID_dsl=2.2*pow(10,-12); // SQUID noise
//static double SQUID_dsl=0; // SQUID noise
static double B_SQUID=20000000; // SQUID noise bandwidth



// LC-TES parameters
static double R0=0.001;
static double T0=0.09;
static double Vp=51.5*pow(10,-9);
static double alpha=75;
static double beta=1.25;
const double Gtes=115.0*pow(10,-12);
static double Rl=60*pow(10,-6);
static double Ctherm=0.8*pow(10,-12);
static double Tbath=0.055;
static double I0=51.5*pow(10,-6);
static double TR=4.08;
static double L=2*pow(10,-6);

#endif
