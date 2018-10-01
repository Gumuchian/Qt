#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

typedef double (*ptrm) (double,double,double,double);

class Pulse_generator
{
    public:
        Pulse_generator();
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
};

#endif // PULSE_GENERATOR_H
