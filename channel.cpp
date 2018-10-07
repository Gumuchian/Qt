#include "channel.h"
#include "dds.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "global.h"

Channel::Channel():dds(Npt,Npr,interpolation)
{
    int i;
    input=0;
    for (i=0;i<Npix;i++){
        ch.push_back(Pixel(1000000.0+i*100000.0,(Npt*interpolation)-((int)trunc(pow(i,2)*(Npt*interpolation)/(2*Npix)))%(Npt*interpolation)));
    }
    feedback = new double[delay+1];
    for (i=0;i<delay+1;i++)
    {
        feedback[i]=0;
    }
}

Channel::~Channel()
{

}

void Channel::setFrequencies(double freq[])
{
    for (int i=0;i<Npix;i++)
    {
        ch[i].setFrequency(freq[i]);
    }
}

double Channel::sumPolar()
{
    int i;
    double sum=0;
    std::normal_distribution<double> dac_b_noise(0.0,DAC_dsl_b*sqrt(B_DAC));
    for (i=0;i<Npix;i++)
    {
        sum+=dds.getvalue(ch[i].getcomptR_I());
    }
    sum=sum/Npr+dac_b_noise(gen);
    for (i=0;i<Npix;i++)
    {
        ch[i].setinputLC(sum);
    }
    return sum;
}

void Channel::setPolar(double polar)
{
    for (int i=0;i<Npix;i++)
    {
        ch[i].setinputLC(polar);
    }
}

double Channel::computeLC_TES()
{
    int i;
    double sum=0;
    for (i=0;i<Npix;i++)
    {
        ch[i].computeLC();
        sum+=ch[i].getI();
    }
    input=sum;
    return ch[0].getI();
}

double Channel::computeBBFB()
{
    int i;
    double adc;
    std::normal_distribution<double> lna_noise  (0.0,LNA_dsl*sqrt(B_LNA)),
                                     SQUID_noise(0.0,SQUID_dsl*sqrt(B_SQUID)),
                                     dac_f_noise(0.0,DAC_dsl*sqrt(B_DAC)),
                                     adc_noise  (0.0,ADC_dsl*sqrt(B_ADC));
    feedback[0]=0;
    for (i=0;i<Npix;i++)
    {
        feedback[0]+=ch[i].getfeedback();
    }
    feedback[0]*=G_filter*PE_DAC/pow(2,DAC_bit);
    adc=G_filter*(G_LNA*G_SQUID*(input+SQUID_noise(gen)-0.1*(feedback[delay]+dac_f_noise(gen)))+lna_noise(gen))+adc_noise(gen);

    for (i=0;i<Npix;i++)
    {
        ch[i].computeBBFB(dds.getvalue(ch[i].getcomptD_I()),
                          dds.getvalue(ch[i].getcomptR_I()),
                          dds.getvalue(ch[i].getcomptD_Q()),
                          dds.getvalue(ch[i].getcomptR_Q()),
                          round(pow(2,ADC_bit)/PE_ADC*adc));
    }

    for (i=delay;i>0;i--)
    {
        feedback[i]=feedback[i-1];
    }
    return adc;
}

 double Channel::getinput()
 {
     return input;
 }

 double Channel::getfck()
 {
     return feedback[delay];
 }

 double Channel::getmod()
 {
     return ch[0].getmodule();
 }

 void Channel::setI(double p)
 {
     ch[0].setI(p);
 }

 void Channel::setMax(double maxLC)
 {
     for (int i=0;i<Npix;i++)
     {
        ch[i].setMaxLC(maxLC);
     }
 }
