#include "dre.h"

DRE::DRE(double f_s, int N_pt, int N_pr, int interpol, int N_pix, int Delay, int nd, int ni ,int nr, double adc_dsl, double b_adc, double fs_adc, int adc_bit, double dac_dsl, double b_dac, double fs_dac, double dac_bit):channel(f_s,N_pt,N_pr,interpol,N_pix,Delay,nd,ni,nr),adc(adc_dsl,b_adc,fs_adc,adc_bit),dac_bias(dac_dsl,b_dac,fs_dac,dac_bit),dac_feedback(dac_dsl,b_dac,fs_dac,dac_bit)
{

}

void DRE::setInput(double input)
{
    channel.computeAllBBFB(adc.computeADC(input));
}

double DRE::getFeedback()
{
    return dac_feedback.computeDAC(channel.getfck());
}

double DRE::getBiasing()
{
    return dac_bias.computeDAC(channel.sumBias());
}

double DRE::getmIQ()
{
    return channel.getmod();
}

void DRE::setFrequencies(double freq[])
{
    channel.setFrequencies(freq);
}
