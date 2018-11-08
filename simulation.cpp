#include "simulation.h"
#include <iostream>
#include <fstream>

Simulation::Simulation(int decimation_factor, double f_s, double L_crit, double TTR, double G_b, double n_therm, double T_bath, double C_therm, double R_l, double R_0, double T_0, double I_0, int N_pt, int N_pr, int interpol, int N_pix, int Delay, int nd, int ni, int nr, double adc_dsl, double b_adc, double fs_adc, int adc_bit, double dac_dsl, double b_dac, double fs_dac, int dac_bit, double G_LNA, double dsl_LNA, double b_LNA, double M_b, double M_f, double G_squid, double squid_dsl, double b_squid, int N_pattern):instrument(decimation_factor,f_s,L_crit,TTR,G_b,n_therm,T_bath,C_therm,R_l,R_0,T_0,I_0,N_pt,N_pr,interpol,N_pix,Delay,nd,ni,nr,adc_dsl,b_adc,fs_adc,adc_bit,dac_dsl,b_dac,fs_dac,dac_bit,G_LNA,dsl_LNA,b_LNA,M_b,M_f,G_squid,squid_dsl,b_squid,N_pattern)
{
    std::fstream file;
    file.open("Pattern.txt",std::ios::in);
    vector<double> IR(N_pattern);
    for (int i=0;i<N_pattern;i++)
    {
        file >> IR[i];
    }
    file.close();
    instrument.setParameters(IR);
    instrument.sweepLC();
}

void Simulation::simulate(int Npoint)
{
    for (int i=0;i<Npoint;i++)
    {
        instrument.compute(7000);
        if (instrument.getNewOutput())
        {
            //file << instrument.getEnergy() << std::endl;
        }
    }
}

void Simulation::EstimateOffset()
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
    instrument.setOffset(sum);
}

void Simulation::EstimateEnergyCurve()
{
    double sum;
    int count;
    vector<double> energies(7,0),Energies(7,0);
    for (int i=0;i<7;i++)
    {
        Energies(i)=100+i*1000;
        sum=0;
        count=0;
        for (int j=0;j<1000000;j++)
        {
            instrument.compute(Energies(i));
            if (instrument.getNewOutput())
            {
                count++;
                sum+=instrument.getOutput();
            }
        }
        energies(i)=sum;
    }
    instrument.computeEnergyCurve(energies,Energies);
}
