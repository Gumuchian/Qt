#include "squid.h"
#include <random>
#include "global.h"


SQUID::SQUID()
{
    mode=false;
}

double SQUID::computeSQUID(double bias, double feedback, bool mode)
{
    double Mb=5.8*pow(10,-6),Mf=58*pow(10,-6),Gsquid=17*pow(10,-3);
    std::mt19937 gen;
    std::normal_distribution<double> SQUID_noise(0.0,SQUID_dsl*sqrt(B_SQUID));
    if (mode)
    {
        return Gsquid*(bias/Mb-feedback/Mf)+SQUID_noise(gen);
    }
    else
    {
        return Gsquid*sin(Mb*bias-Mf*feedback)+SQUID_noise(gen);
    }
}
