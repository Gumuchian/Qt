#ifndef GLOBAL_H
#define GLOBAL_H
#include <math.h>

// Simulation parameters
extern double fs; // sampling frequency
extern int N; // simulation step
extern int Npix; // pixels number
const double PI=3.14159265358979;
extern int Nfit;
const int order_fit=2;
extern double binWidth;



// DDS parameters
extern int Npt; // DDS values
extern int Npr; // DDS value accuracy
extern int interpolation; // Interpolation factor



// TES Noise parameters
extern double TES_dsl; // Spectral linear density of a TES (DC) (A/sqrt(Hz))
extern double Btes; // TES noise bandwidth
extern double fc; // cut frequency of TES noise bandwidth



// Pulse and pattern parameters
extern int Npat;
const int Npul=200000;
extern double energy; // energy of the injected X-rays (eV)



// CIC or Butterworth
extern int decimation; // down sampling factor
const int order=2; // CIC/Butterworth order, if Butterworth order must be equal to 2



// BBFB
extern double G; // Integrator gain
extern int delay; // loop delay (simulation step)



// DAC
extern double PE_DAC; // full scale (A)
extern int DAC_bit; // number of bits of DAC
extern double B_DAC; // DAC feedback noise bandwidth
extern double DAC_dsl; // Spectral linear density of DAC feedback
extern double DAC_dsl_b;



// ADC
extern double PE_ADC;
extern int ADC_bit; // number of bits of ADC
extern double ADC_dsl; // Spectral linear density of ADC
extern double B_ADC; // ADC noise bandwidth



// Filter
const double G_filter=1; // anti-aliasing/reexternruction filter gain



// LNA
extern double G_LNA; // LNA gain
extern double LNA_dsl; // Spectral linear density of LNA (V/sqrt(Hz))
extern double B_LNA; // LNA noise bandwidth



// SQUID
extern double G_SQUID; // SQUID transimpedance
extern double SQUID_dsl; // SQUID noise
extern double B_SQUID; // SQUID noise bandwidth



// LC-TES parameters
extern double R0;
extern double T0;
extern double Gb;
extern double alpha;
extern double beta;
extern double Rl;
extern double Ctherm;
extern double Tbath;
extern double I0;
extern double TR;
extern double Lcrit;
extern double ntherm;

extern bool saveIQ;
extern bool saveError;
extern bool saveFeedback;
extern bool saveItes;


#endif
