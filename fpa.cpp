#include "fpa.h"

FPA::FPA(unsigned seed, double f_s, int N_pix, double L_crit, double TTR, double G_b, double n_therm, double T_bath, double C_therm, double R_l, double R_0, double T_0, double I_0):N_pix(N_pix)
{
    for (int i=0;i<N_pix;i++)
    {
        TES_array.push_back(TES(seed, L_crit,TTR,f_s,pow(10,6)+i*pow(10,5)));
        pulse_generator.push_back(Pulse_generator(seed+(unsigned)i,G_b,n_therm,T_bath,C_therm,R_l,L_crit,f_s,R_0,T_0,I_0));
    }
}

void FPA::setBiasingVoltage(double bias)
{
    for (int i=0;i<N_pix;i++)
    {
        TES_array[i].setBias(bias);
    }
}

double FPA::getCurrent()
{
    double sum=0;
    for (int i=0;i<N_pix;i++)
    {
        TES_array[i].setI(pulse_generator[i].compute());
        sum+=TES_array[i].computeLCTES();
    }
    return sum;
}

void FPA::setEnergy(double Energy, int index)
{
    pulse_generator[index].setPopt(Energy);
}


void FPA::setMax(double max_LC)
{
    for (int i=0;i<N_pix;i++)
    {
        TES_array[i].setMax(max_LC);
    }
}
