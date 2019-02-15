#include "simulation.h"
#include <fstream>
#include <qmessagebox.h>
#define PI 3.14159265358979

Simulation::Simulation(int Nsim, unsigned seed,int decimation_factor, double f_s, double L_crit, double TTR, double G_b, double n_therm, double T_bath, double C_therm, double R_l, double R_0, double T_0, double I_0, int N_pt, int N_pr, int interpol, int N_pix, int Delay, int nd, int ni, int nr, double adc_dsl, double b_adc, double fs_adc, int adc_bit, double dac_dsl, double b_dac, double fs_dac, int dac_bit, double G_LNA, double dsl_LNA, double b_LNA, double M_b, double M_f, double G_squid, double squid_dsl, double b_squid, int N_pattern):N_sim(Nsim),instrument(seed,decimation_factor,f_s,L_crit,TTR,G_b,n_therm,T_bath,C_therm,R_l,R_0,T_0,I_0,N_pt,N_pr,interpol,N_pix,Delay,nd,ni,nr,adc_dsl,b_adc,fs_adc,adc_bit,dac_dsl,b_dac,fs_dac,dac_bit,G_LNA,dsl_LNA,b_LNA,M_b,M_f,G_squid,squid_dsl,b_squid,N_pattern)
{

}

Simulation::~Simulation()
{

}

void Simulation::setIR(ublas::vector<double> IR)
{
    instrument.setParameters(IR,10);
    instrument.sweepLC();
}

void Simulation::setNsim(int Nsim)
{
    N_sim = Nsim;
}

void Simulation::setEnergy(double energy)
{
    Energy = energy;
}

void Simulation::simulate()
{
    std::fstream file,file1;
    file.open("Bias.txt",std::ios::out);
    file1.open("mIQ.txt",std::ios::out);
    QVector<double> Energies;
    for (int i=0;i<N_sim;i++)
    {
        file << instrument.getBiasing() << std::endl;
        instrument.compute(Energy);
        file1 << instrument.getmIQ() << std::endl;
        if (instrument.readyToSendToEP() && instrument.getNewOutput())
        {
            Energies.push_back(instrument.getEnergy());
        }
    }
    file.close();
    file1.close();
    emit energies(Energies);
}

double Simulation::EstimateOffset()
{
    std::vector<double> offset;
    double sum=0;
    for (int i=0;i<100000;i++)
    {
        instrument.compute(0.0);
        if (i>50000)
        {
            offset.push_back(instrument.getData());
        }
    }
    for (int i=0;i<(int)offset.size();i++)
    {
        sum+=offset[i];
    }
    sum/=offset.size();
    return sum;
}

void Simulation::setOffset(double offset)
{
    instrument.setOffset(offset);
}

void Simulation::setCoefficientEnergyCurve(ublas::vector<double> energies)
{
    ublas::vector<double> Energies(7,0);
    for (int i=0;i<7;i++)
    {
        Energies(i)=(200+i*1000);
    }
    instrument.computeEnergyCurve(energies,Energies);
}

ublas::vector<double> Simulation::EstimateEnergyCurve()
{
    double sum;
    int count;
    instrument.setEP();
    ublas::vector<double> energies(7,0);
    for (int i=0;i<9;i++)
    {
        count=0;
        sum=0;
        for (int j=0;j<1000000;j++)
        {
            instrument.compute(200+i*1000);
            if (instrument.readyToSendToEP())
            {
                if (instrument.getNewOutput())
                {
                    count++;
                    sum+=instrument.getOutput();
                }
            }
        }
        if (i>1)
        {
            energies(i-2)=sum/count;           
        }
    }
    return energies;
}

void Simulation::computeImpulseResponse()
{
    instrument.setEP();
    double Energy=7000.0;
    bool pulse_mode=true;
    ublas::vector<double> IR(2048);
    for (int i=0;i<N_sim;i++)
    {
        if (i>N_sim/2)
        {
            Energy = 0.0;
            pulse_mode = false;
            instrument.setParameters(IR,0);
        }
        instrument.compute(Energy);
        if (i>N_sim/5)
        {
            if (instrument.readyToSendToEP())
            {
                instrument.recordImpulseResponse(pulse_mode);
            }
        }
    }
    emit pulses(instrument.getPulse());
    emit noises(instrument.getNoise());
    emit phase(instrument.getPhase());
}

void Simulation::setImpulseResponse(QVector<double> pulse,QVector<double> noise,QVector<double> phase)
{

    CArray TF(2048);
    ublas::vector<double> IR(2048);
    const Complex const_i(0,1);
    for (int i=0;i<2048;i++)
    {
        TF[i]=pulse[i]/noise[i]*std::exp(const_i*phase[i]);
    }
    ifft(TF);
    std::fstream file;
    file.open("Papat.txt",std::ios::out);
    for (int i=0;i<2048;i++)
    {
        IR[i]=std::real(TF[i]);
        file << IR[i] << std::endl;
    }
    file.close();
    setIR(IR);
}

void Simulation::fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    CArray even = x[std::slice(0,N/2,2)];
    CArray  odd = x[std::slice(1,N/2,2)];

    fft(even);
    fft(odd);

    for (size_t k=0;k<N/2;++k)
    {
        Complex t = std::polar(1.0,-2*PI*k/N)*odd[k];
        x[k]=even[k]+t;
        x[k+N/2]=even[k]-t;
    }
}

void Simulation::ifft(CArray& x)
{
    x = x.apply(std::conj);
    fft(x);
    x = x.apply(std::conj);
    x /= x.size();
}
