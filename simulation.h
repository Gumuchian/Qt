#ifndef SIMULATION_H
#define SIMULATION_H
#include "instrument.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <QWidget>
#include <QVector>

using namespace boost::numeric;

class Simulation: public QObject
{
    Q_OBJECT
public:
    Simulation(int decimation_factor, double f_s, double L_crit, double TTR, double G_b, double n_therm, double T_bath, double C_therm, double R_l, double R_0, double T_0, double I_0, int N_pt, int N_pr, int interpol, int N_pix, int Delay, int nd, int ni, int nr, double adc_dsl, double b_adc, double fs_adc, int adc_bit, double dac_dsl, double b_dac, double fs_dac, int dac_bit, double G_LNA, double dsl_LNA, double b_LNA, double M_b, double M_f, double G_squid, double squid_dsl, double b_squid, int N_pattern);
    virtual ~Simulation();
    void simulate(int Npoint);
    void EstimateEnergyCurve();
    void computeImpulseResponse();
public slots:
    void cacalibrate();
    void EstimateOffset();
signals:
    void simulation_end(int value);
    void energies(QVector<double> E);
    void pulses(QVector<double> pulse);
    void noises(QVector<double> noise);
private:
    Instrument instrument;
};

#endif // SIMULATION_H
