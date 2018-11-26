#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H
#include <random>

typedef double (*ptrm) (double,double,double,double,double,double,double,double);

class Pulse_generator
{
    public:
        Pulse_generator();
        Pulse_generator(unsigned seed, double G_b, double n_therm, double T_bath, double C_therm, double R_l, double L_crit, double f_s, double R_0, double T_0, double I_0);
        static double dT(double T, double Pj, double Po, double noise, double n_therm, double T_bath, double C_therm, double G_b);
        static double dI(double I, double V, double R, double noise, double R_l, double L_crit, double unused1, double unused2);
        double RK4(ptrm f, double dt, double y0, double y1, double y2, double y3, double y4, double y5, double y6, double y7);
        double compute();
        void setPopt(double Po);
        virtual ~Pulse_generator();

    protected:

    private:
        double Rtes;
        double Ites;
        double Ttes;
        double Popt;
        double G_b;
        double n_therm;
        double T_bath;
        double C_therm;
        double R_l;
        double L_crit;
        double f_s;
        double R_0;
        double T_0;
        double I_0;
        std::mt19937 gen;
};

#endif // PULSE_GENERATOR_H
