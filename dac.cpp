#include "dac.h"
#include <random>
#include "global.h"

DAC::DAC()
{

}

double DAC::computeDAC(double input)
{
    std::mt19937 gen;
    std::normal_distribution<double> dac_f_noise(0.0,DAC_dsl*sqrt(B_DAC));
    return G_filter*(input*PE_DAC/pow(2,DAC_bit)+dac_f_noise(gen));
}
