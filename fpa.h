#ifndef FPA_H
#define FPA_H
#include "tes.h"
#include "pulse_generator.h"

class FPA
{
public:
    FPA(double f_s, int N_pix, double L_crit, double TTR, double G_b, double n_therm, double T_bath, double C_therm, double R_l, double R_0, double T_0, double I_0);
    void setBiasingVoltage(double bias);
    double getCurrent();
    void setEnergy(double Energy, int index);
    void setMax(double max_LC);
private:
    int N_pix;
    std::vector<TES> TES_array;
    std::vector<Pulse_generator> pulse_generator;
};

#endif // FPA_H
