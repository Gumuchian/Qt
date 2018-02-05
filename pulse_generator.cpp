#include "Pulse_generator.h"
#include "ressources.h"

typedef double (*ptrm) (double,double,double);

Pulse_generator::Pulse_generator()
{
    Ites=I0;
    Ttes=T0;
    Rtes=R0;
    Popt=0;
}

double Pulse_generator::dT(double T, double Pj, double Po)
{
    return (Po+Pj-Gtes/(3*pow(T,2))*(pow(T,3)-pow(Tbath,3)))/C_therm;
}


double Pulse_generator::dI(double I, double V, double R)
{
    return (V-I*Rl-I*R)/(L/pow(TR,2));
}

double Pulse_generator::RK4(ptrm f, double dt, double y0, double y1, double y2)
{
    double k1,k2,k3,k4;
    k1=f(y0,y1,y2);
    k2=f(y0+dt/2*k1,y1,y2);
    k3=f(y0+dt/2*k2,y1,y2);
    k4=f(y0+dt*k3,y1,y2);
    return y0+dt/6*(k1+2*k2+2*k3+k4);
}

double Pulse_generator::compute()
{
    ptrm ptrdT,ptrdI;
    ptrdT=&Pulse_generator::dT;
    ptrdI=&Pulse_generator::dI;
    Ites=RK4(ptrdI,1.0/fs,Ites,Vp,Rtes);
    Ttes=RK4(ptrdT,1.0/fs,Ttes,pow(Vp,2)/Rtes,Popt);
    Rtes=R0+alpha*R0/T0*(Ttes-T0)+beta*R0/I0*(Ites-I0);
    Popt=0;
    return Ites;
}

void Pulse_generator::setPopt(double Po)
{
    Popt=Po/12000*4.388*pow(10,-8)*1.0246;
}

Pulse_generator::~Pulse_generator()
{

}
