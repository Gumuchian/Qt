#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

typedef double (*ptrm) (double,double,double,double);

class Pulse_generator
{
    public:
        Pulse_generator();
        Pulse_generator(double G_b, double n_therm, double T_bath, double C_therm, double R_l, double L_crit, double f_s, double R_0, double T_0, double I_0);
        static double dT(double T, double Pj, double Po, double noise);
        static double dI(double I, double V, double R, double noise);
        double RK4(ptrm f, double dt, double y0, double y1, double y2, double y3);
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
};

#endif // PULSE_GENERATOR_H
