#include "lna.h"

LNA::LNA(double G_LNA, double dsl_LNA, double b_LNA):G_LNA(G_LNA),dsl_LNA(dsl_LNA),b_LNA(b_LNA),lna_noise(0.0,dsl_LNA*sqrt(b_LNA)),gen(std::random_device{}())
{

}

double LNA::compute(double input)
{
    return input*G_LNA+lna_noise(gen);
}
