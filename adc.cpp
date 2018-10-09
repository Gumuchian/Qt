#include "adc.h"
#include <random>

ADC::ADC()
{

}

double ADC::computeADC(double input)
{
    std::mt19937 gen;
    std::normal_distribution<double> adc_noise(0.0,ADC_dsl*sqrt(B_ADC));
    return round((G_filter*input+adc_noise(gen))*pow(2,ADC_bit)/PE_ADC);
}
