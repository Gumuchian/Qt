#ifndef DRE_H
#define DRE_H
#include "channel.h"

class DRE
{
public:
    DRE(double f_s, int N_pt, int N_pr, int interpol, int N_pix, int Delay, int nd, int ni, int nr, double adc_dsl, double b_adc, double fs_adc, int adc_bit, double dac_dsl, double b_dac, double fs_dac, double dac_bit);
    void setInput(double input);
    double getFeedback();
    double getBiasing();
    double getmIQ();
    void setFrequencies(double freq[]);
private:
    Channel channel;
    ADC adc;
    DAC dac_bias;
    DAC dac_feedback;
};

#endif // DRE_H
