#ifndef ADC_H
#define ADC_H
#include <random>

class ADC
{
public:
    ADC();
    ADC(double adc_dsl, double b_adc, double fs_adc, int adc_bit);
    double computeADC(double input);
private:
    double adc_dsl;
    double b_adc;
    double fs_adc;
    int adc_bit;
    std::normal_distribution<double> adc_noise;
    std::mt19937 gen;
};

#endif // ADC_H
