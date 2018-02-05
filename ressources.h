#ifndef RESSOURCES_H_INCLUDED
#define RESSOURCES_H_INCLUDED
#include <math.h>

// Simulation parameters
const double fs=20000000; // sampling frequency
const int N=40000000; // simulation step
const int Npix=1; // pixels number
const double PI=3.14159265358979; // don't touch !!
const int Nfit=5;
const int order_fit=2;



// DDS parameters
const int Npt=pow(2,9); // DDS values
const int Npr=pow(2,18); // DDS value accuracy
const int interpolation=pow(2,20-9); // Interpolation factor



// TES Noise parameters
const double TES_dsl=105*pow(10,-12); // Spectral linear density of a TES (DC) (A/sqrt(Hz))
//const double TES_dsl=0;
const double Btes=20000000; // TES noise bandwidth
const double fc=560; // cut frequency of TES noise bandwidth



// Pulse and pattern parameters
const int Npat=2048;
const int Npul=200000;
const double energy=200; // energy of the injected X-rays (eV)



// CIC or Butterworth
const int decimation=128; // down sampling factor
const int order=2; // CIC/Butterworth order, if Butterworth order must be equal to 2
const int Np=Npat*decimation; // don't touch !!



// BBFB
const double G=0.0001549644569; // Integrator gain
const int delay=1; // loop delay (simulation step)



// DAC
const double PE_DAC=0.02; // full scale (A)
const int DAC_bit=16; // number of bits of DAC
const double B_DAC=20000000; // DAC feedback noise bandwidth
const double DAC_dsl=28*pow(10,-12); // Spectral linear density of DAC feedback
//const double DAC_dsl=0;
const double DAC_dsl_b=0.5*pow(10,-140/20);
//const double DAC_dsl_b=0;



// ADC
const double PE_ADC=1.0;
const int ADC_bit=12; // number of bits of ADC
const double ADC_dsl=6.448*pow(10,-9); // Spectral linear density of ADC
//const double ADC_dsl=0;
const double B_ADC=20000000; // ADC noise bandwidth



// Filter
const double G_filter=1; // anti-aliasing/reconstruction filter gain



// LNA
const double G_LNA=83; // LNA gain
const double LNA_dsl=258*pow(10,-9); // Spectral linear density of LNA (V/sqrt(Hz))
//const double LNA_dsl=0;
const double B_LNA=20000000; // LNA noise bandwidth



// SQUID
const double G_SQUID=0.017/(5.8*pow(10,-6)); // SQUID transimpedance
const double SQUID_dsl=2.2*pow(10,-12); // SQUID noise
//const double SQUID_dsl=0; // SQUID noise
const double B_SQUID=20000000; // SQUID noise bandwidth



// LC-TES parameters
const double R0=0.001;
const double T0=0.09;
const double Vp=51.5*pow(10,-9);
const double alpha=75;
const double beta=1.25;
const double Gtes=115.0*pow(10,-12);
const double Rl=60*pow(10,-6);
const double C_therm=0.8*pow(10,-12);
const double Tbath=0.055;
const double I0=51.5*pow(10,-6);
const double TR=4.08;
const double L=2*pow(10,-6);

#endif // RESSOURCES_H_INCLUDED
