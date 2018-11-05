#include "adc.h"
#include <random>
#include "global.h"
#include <ctime>

ADC::ADC(double adc_dsl, double b_adc, double fs_adc, int adc_bit):adc_dsl(adc_dsl),b_adc(b_adc),fs_adc(fs_adc),adc_bit(adc_bit),adc_noise(0.0,adc_dsl*sqrt(b_adc)),gen(time(0))
{

}

double ADC::computeADC(double input)
{
    return round((input+adc_noise(gen))*pow(2,adc_bit)/fs_adc);
}
