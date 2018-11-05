#ifndef DAC_H
#define DAC_H
#include <random>

class DAC
{
public:
    DAC();
    DAC(double dac_dsl, double b_dac, double fs_dac, double dac_bit);
    double computeDAC(double input);
private:
    double dac_dsl;
    double b_dac;
    double fs_dac;
    double dac_bit;
    std::mt19937 gen;
    std::normal_distribution<double> dac_f_noise;
};

#endif // DAC_H
