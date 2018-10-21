#ifndef ADC_H
#define ADC_H


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
};

#endif // ADC_H
