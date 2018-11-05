#include "pixel.h"
#include "bbfb.h"
#include "tes.h"
#include <math.h>
#include <random>
#include "global.h"

Pixel::Pixel()
{

}

Pixel::~Pixel()
{

}

Pixel::Pixel(double f_s, double frequency, int phase, int Delay,int npt, int interpol, int npr, int nd, int ni, int nr):f_s(f_s),frequency(frequency),phase(phase),bbfb(npr,nd,ni,nr),npt(npt),interpol(interpol),Delay(Delay)
{
    comptR_I=phase%(npt*interpol);
    comptR_Q=(comptR_I+(npt*interpol)/4)%(npt*interpol);
    feedback=0;
}

void Pixel::setFrequency(double freq)
{
    comptD_I=(comptR_I+(((int)(npt*interpol*Delay*freq/fs))%(npt*interpol)))%(npt*interpol);
    comptD_Q=(comptD_I+(npt*interpol)/4)%(npt*interpol);
    step=(int)round((npt*interpol)*(freq/f_s));
}

double Pixel::getfeedback()
{
    return feedback;
}

double Pixel::getmodule()
{
    return bbfb.module();
}

void Pixel::computeBBFB(double demoduI, double remoduI, double demoduQ, double remoduQ, double input)
{
    bbfb.compute_feedback(demoduI,remoduI,demoduQ,remoduQ,input);
    comptR_I=(comptR_I+step)%(npt*interpol);
    comptD_I=(comptD_I+step)%(npt*interpol);
    comptR_Q=(comptR_Q+step)%(npt*interpol);
    comptD_Q=(comptD_Q+step)%(npt*interpol);
    feedback=bbfb.getfeedback();
}

int Pixel::getcomptD_I()
{
    return comptD_I;
}

int Pixel::getcomptD_Q()
{
    return comptD_Q;
}

int Pixel::getcomptR_I()
{
    return comptR_I;
}

int Pixel::getcomptR_Q()
{
    return comptR_Q;
}
