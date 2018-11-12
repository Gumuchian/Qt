#include "instrument.h"
#include <iostream>
#include <fstream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric;

Instrument::Instrument(int decimation_factor, double f_s, double L_crit, double TTR, double G_b, double n_therm, double T_bath, double C_therm, double R_l, double R_0, double T_0, double I_0, int N_pt, int N_pr, int interpol, int N_pix, int Delay, int nd, int ni, int nr, double adc_dsl, double b_adc, double fs_adc, int adc_bit, double dac_dsl, double b_dac, double fs_dac, int dac_bit, double G_LNA, double dsl_LNA, double b_LNA, double M_b, double M_f, double G_squid, double squid_dsl, double b_squid, int N_pattern):fpa(f_s,N_pix,L_crit,TTR,G_b,n_therm,T_bath,C_therm,R_l,R_0,T_0,I_0),dre(f_s,N_pt,N_pr,interpol,N_pix,Delay,nd,ni,nr,adc_dsl,b_adc,fs_adc,adc_bit,dac_dsl,b_dac,fs_dac,dac_bit),squid(M_b,M_f,G_squid,squid_dsl,b_squid),EP(N_pattern),lna(G_LNA,dsl_LNA,b_LNA),decimation_factor(decimation_factor),f_s(f_s),I_0(I_0),TTR(TTR)
{
    count = 0;
    count_pulse = 1;
    DataSentToEP = false;
}

void Instrument::compute(double Energy)
{
    fpa.setBiasingVoltage(pow(2,16)/0.02*dre.getBiasing());
    dre.setInput(lna.compute(squid.computeSQUID(fpa.getCurrent(),dre.getFeedback(),true)));
    DataSentToEP = false;
    if (count == 0)
    {
        EP.setInput(dre.getmIQ());
        DataSentToEP = true;
    }
    if (count_pulse == 0)
    {
        fpa.setEnergy(Energy,0);
    }
    count ++;
    count=count%decimation_factor;
    count_pulse ++;
    count_pulse=count_pulse%500000;
}

void Instrument::setParameters(vector<double> IR,double threshold)
{
    EP.setImpulseResponse(IR);
    EP.setThreshold(threshold);
}


void Instrument::setPulse(double Energy, int index)
{
    fpa.setEnergy(Energy,index);
}

void Instrument::sweepLC()
{
    double sig=1;
    int Nsweep=21;
    double frequency[40];
    CArray TF((int)pow(2,Nsweep));
    for (int i=0;i<(int)pow(2,Nsweep);i++)
    {
        fpa.setBiasingVoltage(sig);
        TF[i]=fpa.getCurrent();
        sig=0;
    }
    fft(TF);
    int index=950000*pow(2,Nsweep)/f_s;
    double max_LC=0;
    for (int i=0;i<40;i++)
    {
       max_LC=0;
       for (int j=0;j<(int)(50000/f_s*pow(2,Nsweep));j++)
       {

           if (max_LC < abs(TF[index+j]))
           {
               frequency[i]=(index+j)*f_s/pow(2,Nsweep);
               max_LC=abs(TF[index+j]);
           }
       }
       index=(int)((frequency[i]+50000)*pow(2,Nsweep)/f_s)+1000;
    }
    max_LC=0;
    for (int i=0;i<(int)pow(2,Nsweep);i++)
    {
        sig=cos(2*3.14159265358979*frequency[0]/f_s*i);
        fpa.setBiasingVoltage(sig);
        TF[i]=fpa.getCurrent();
    }
    for (int i=0;i<(int)pow(2,Nsweep-1);i++)
    {
        if (max_LC < abs(TF[pow(2,Nsweep-1)+i]))
        {
            max_LC=abs(TF[pow(2,Nsweep-1)+i]);
        }
    }
    dre.setFrequencies(frequency);
    max_LC/=I_0*sqrt(2)/TTR;
    fpa.setMax(max_LC);
}

void Instrument::fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    CArray even = x[std::slice(0,N/2,2)];
    CArray  odd = x[std::slice(1,N/2,2)];

    fft(even);
    fft(odd);

    for (size_t k=0;k<N/2;++k)
    {
        Complex t = std::polar(1.0,-2*3.14159265358979*k/N)*odd[k];
        x[k]=even[k]+t;
        x[k+N/2]=even[k]-t;
    }
}

double Instrument::getData()
{
    return dre.getmIQ();
}

void Instrument::setOffset(double offset)
{
    EP.setOffset(offset);
}

double Instrument::getOutput()
{
    return EP.getOutput();
}

bool Instrument::getNewOutput()
{
    return EP.getRecording();
}

void Instrument::computeEnergyCurve(ublas::vector<double> AU, ublas::vector<double> energies)
{
    EP.computeCorrCoeff(AU,energies);
}

void Instrument::recordImpulseResponse(bool pulse_mode)
{
    EP.setMode(pulse_mode);
    EP.recordImpulseResponse();
}

void Instrument::computeImpulseResponse()
{
    EP.computeImpulseResponse();
}

double Instrument::getEnergy()
{
    return EP.getEnergy();
}

bool Instrument::readyToSendToEP()
{
    return DataSentToEP;
}
