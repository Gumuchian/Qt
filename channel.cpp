#include "channel.h"
#include "dds.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "global.h"

Channel::Channel(double f_s,int N_pt, int N_pr, int interpol, int N_pix, int Delay, int nd, int ni ,int nr):N_pt(N_pt),N_pr(N_pr),interpol(interpol),N_pix(N_pix),Delay(Delay),dds(N_pt,N_pr,interpol)
{
    int i;
    input=0;
    for (i=0;i<N_pix;i++){
        ch.push_back(Pixel(f_s,1000000.0+i*100000.0,(N_pt*interpol)-((int)trunc(pow(i,2)*(N_pt*interpol)/(2*N_pix)))%(N_pt*interpol), Delay, N_pt, interpol, N_pr, nd, ni, nr));
    }
    feedback = new double[Delay+1];
    for (i=0;i<Delay+1;i++)
    {
        feedback[i]=0;
    }
}

Channel::~Channel()
{

}

void Channel::setFrequencies(double freq[])
{
    for (int i=0;i<N_pix;i++)
    {
        ch[i].setFrequency(freq[i]);
    }
}

double Channel::sumBias()
{
    int i;
    double sum=0;
    for (i=0;i<N_pix;i++)
    {
        sum+=dds.getvalue(ch[i].getcomptR_I());
    }
    sum/=Npr;
    return sum;
}

void Channel::computeAllBBFB(double input)
{
    for (int i=0;i<N_pix;i++)
    {
        ch[i].computeBBFB(dds.getvalue(ch[i].getcomptD_I()),
                          dds.getvalue(ch[i].getcomptR_I()),
                          dds.getvalue(ch[i].getcomptD_Q()),
                          dds.getvalue(ch[i].getcomptR_Q()),
                          input);
    }
    feedback[0]=0;
    for (int i=0;i<N_pix;i++)
    {
        feedback[0]+=ch[i].getfeedback();
    }
    for (int i=Delay;i>0;i--)
    {
        feedback[i]=feedback[i-1];
    }
}

 double Channel::getfck()
 {
     return feedback[Delay];
 }

 double Channel::getmod()
 {
     return ch[0].getmodule();
 }
