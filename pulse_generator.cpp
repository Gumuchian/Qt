#include "pulse_generator.h"
#include "global.h"
#include <math.h>


Pulse_generator::Pulse_generator()
{

}

Pulse_generator::Pulse_generator(unsigned seed, double G_b, double n_therm, double T_bath, double C_therm, double R_l, double L_crit, double f_s, double R_0, double T_0, double I_0):G_b(G_b), n_therm(n_therm), T_bath(T_bath), C_therm(C_therm), R_l(R_l), L_crit(L_crit), f_s(f_s), R_0(R_0), T_0(T_0), I_0(I_0), gen(seed)
{
    Ites=I_0;
    Ttes=T_0;
    Rtes=R_0;
    Popt=0;
}

double Pulse_generator::dT(double T, double Pj, double Po, double noise, double n_therm, double T_bath, double C_therm, double G_b)
{
    return (Po+Pj-G_b/(3*pow(T,2))*(pow(T,n_therm)-pow(T_bath,n_therm))+noise)/C_therm;
}

double Pulse_generator::dI(double I, double V, double R, double noise, double R_l, double L_crit, double unused1, double unused2)
{
    return (V-I*R_l-I*R+noise)/(2*L_crit);
}

double Pulse_generator::RK4(ptrm f, double dt, double y0, double y1, double y2, double y3, double y4, double y5, double y6, double y7)
{
    double k1,k2,k3,k4;
    k1=f(y0,y1,y2,y3,y4,y5,y6,y7);
    k2=f(y0+dt/2*k1,y1,y2,y3,y4,y5,y6,y7);
    k3=f(y0+dt/2*k2,y1,y2,y3,y4,y5,y6,y7);
    k4=f(y0+dt*k3,y1,y2,y3,y4,y5,y6,y7);
    return y0+dt/6*(k1+2*k2+2*k3+k4);
}

double Pulse_generator::compute()
{
    double gamma=0.5*(pow(T_bath/Ttes,n_therm+1)+1);
    double kb=1.38*pow(10,-23);
    double M=0;
    std::normal_distribution<double> Vn_TES(0,sqrt(4*kb*Ttes*Rtes*(1+2*beta)*(1+pow(M,2))*f_s)),
                                     Vn_load(0,sqrt(4*kb*Ttes*R_l*fs)),
                                     Pn_bath(0,sqrt(4*kb*pow(Ttes,2)*G_b*gamma*f_s));
    ptrm ptrdT,ptrdI;
    ptrdT=&Pulse_generator::dT;
    ptrdI=&Pulse_generator::dI;
    Ites=RK4(ptrdI,1.0/f_s,Ites,R_0*I_0,Rtes,Vn_load(gen)+Vn_TES(gen),R_l,L_crit,0.0,0.0);
    Ttes=RK4(ptrdT,1.0/f_s,Ttes,pow(R_0*I_0,2)/Rtes,Popt,Ites*Vn_TES(gen)+Pn_bath(gen),n_therm,T_bath,C_therm,G_b);
    Rtes=R_0+alpha*R_0/T_0*(Ttes-T_0)+beta*R_0/I_0*(Ites-I_0);
    Popt=0;
    return Ites;
}

void Pulse_generator::setPopt(double Po)
{
    Popt=Po*1.6*pow(10,-19)*f_s;
}

Pulse_generator::~Pulse_generator()
{

}
