#ifndef INSTRUMENT_H
#define INSTRUMENT_H
#include "fpa.h"
#include "dre.h"
#include "event_processor.h"
#include "lna.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric;

class Instrument
{
public:
    Instrument(int decimation_factor, double f_s, double L_crit, double TTR, double G_b, double n_therm, double T_bath, double C_therm, double R_l, double R_0, double T_0, double I_0, int N_pt, int N_pr, int interpol, int N_pix, int Delay, int nd, int ni, int nr, double adc_dsl, double b_adc, double fs_adc, int adc_bit, double dac_dsl, double b_dac, double fs_dac, int dac_bit, double G_LNA, double dsl_LNA, double b_LNA, double M_b, double M_f, double G_squid, double squid_dsl, double b_squid, int N_pattern);
    void compute();
    void setParameters(vector<double> IR,double factor);
    void sweepLC();
    void fft(CArray& x);
    void setPulse(double Energy);
    double getData();
private:
    FPA fpa;
    DRE dre;
    SQUID squid;
    Event_Processor EP;
    LNA lna;
    int count;
    int count_pulse;
    int decimation_factor;
    double f_s;
    double I_0;
    double TTR;
};

#endif // INSTRUMENT_H
