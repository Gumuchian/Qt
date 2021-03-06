#include "dac.h"
#include <random>
#include "global.h"
#include <ctime>

DAC::DAC()
{

}

DAC::DAC(double dac_dsl, double b_dac, double fs_dac, double dac_bit):dac_dsl(dac_dsl), b_dac(b_dac), fs_dac(fs_dac), dac_bit(dac_bit), gen(std::random_device{}()),dac_f_noise(0.0,dac_dsl*sqrt(b_dac))
{

}

double DAC::computeDAC(double input)
{
    return G_filter*(input*fs_dac/pow(2,dac_bit)+dac_f_noise(gen));
}
