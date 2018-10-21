#include "adc.h"
#include <random>
#include "global.h"

ADC::ADC()
{

}

ADC::ADC(double adc_dsl, double b_adc, double fs_adc, int adc_bit):adc_dsl(adc_dsl),b_adc(b_adc),fs_adc(fs_adc),adc_bit(adc_bit)
{

}

double ADC::computeADC(double input)
{
    std::mt19937 gen;
    std::normal_distribution<double> adc_noise(0.0,adc_dsl*sqrt(b_adc));
    return round((input+adc_noise(gen))*pow(2,adc_bit)/fs_adc);
}
