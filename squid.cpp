#include "squid.h"
#include <random>
#include <ctime>
#include "global.h"


SQUID::SQUID()
{

}

SQUID::SQUID(double M_b, double M_f, double G_squid, double squid_dsl, double b_squid):M_b(M_b),M_f(M_f),G_squid(G_squid),squid_dsl(squid_dsl),b_squid(b_squid),gen(time(0)),SQUID_noise(0.0,SQUID_dsl*sqrt(B_SQUID))
{
    mode=false;
}

double SQUID::computeSQUID(double bias, double feedback, bool mode)
{
    if (mode)
    {
        return G_squid*(bias/M_b-feedback/M_f)+SQUID_noise(gen);
    }
    else
    {
        return G_squid*sin(M_b*bias-M_f*feedback)+SQUID_noise(gen);
    }
}
