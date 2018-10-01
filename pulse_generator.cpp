#include "pulse_generator.h"
#include "global.h"
#include <math.h>
#include <random>

typedef double (*ptrm) (double,double,double,double);

Pulse_generator::Pulse_generator()
{
    Ites=I0;
    Ttes=T0;
    Rtes=R0;
    Popt=0;
}

double Pulse_generator::dT(double T, double Pj, double Po, double noise)
{
    return (Po+Pj-Gb/(3*pow(T,2))*(pow(T,ntherm)-pow(Tbath,ntherm))+noise)/Ctherm;
}

double Pulse_generator::dI(double I, double V, double R, double noise)
{
    return (V-I*Rl-I*R+noise)/(2*Lcrit);
}

double Pulse_generator::RK4(ptrm f, double dt, double y0, double y1, double y2, double y3)
{
    double k1,k2,k3,k4;
    k1=f(y0,y1,y2,y3);
    k2=f(y0+dt/2*k1,y1,y2,y3);
    k3=f(y0+dt/2*k2,y1,y2,y3);
    k4=f(y0+dt*k3,y1,y2,y3);
    return y0+dt/6*(k1+2*k2+2*k3+k4);
}

double Pulse_generator::compute()
{
    std::mt19937 gen;
    double gamma=0.5*(pow(Tbath/Ttes,ntherm+1)+1);
    double kb=1.38*pow(10,-23);
    double M=0;
    std::normal_distribution<double> Vn_TES(0,sqrt(4*kb*Ttes*Rtes*(1+2*beta)*(1+pow(M,2))*fs)),
                                     Vn_load(0,sqrt(4*kb*Ttes*Rl*fs)),
                                     Pn_bath(0,sqrt(4*kb*pow(Ttes,2)*Gb*gamma*fs));
    ptrm ptrdT,ptrdI;
    ptrdT=&Pulse_generator::dT;
    ptrdI=&Pulse_generator::dI;
    Ites=RK4(ptrdI,1.0/fs,Ites,R0*I0,Rtes,Vn_load(gen)+Vn_TES(gen));
    Ttes=RK4(ptrdT,1.0/fs,Ttes,pow(R0*I0,2)/Rtes,Popt,Ites*Vn_TES(gen)+Pn_bath(gen));
    Rtes=R0+alpha*R0/T0*(Ttes-T0)+beta*R0/I0*(Ites-I0);
    Popt=0;
    return Ites;
}

void Pulse_generator::setPopt(double Po)
{
    Popt=(Po+59.29)/(2.83694382*pow(10,11));
}

Pulse_generator::~Pulse_generator()
{

}
