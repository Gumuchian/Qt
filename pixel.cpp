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

Pixel::Pixel(double frequency, double real_frequency, int phase):frequency(frequency)
{
    comptR_I=phase%(Npt*interpolation);
    comptR_Q=(comptR_I+(Npt*interpolation)/4)%(Npt*interpolation);
    comptD_I=(comptR_I+(((int)(Npt*interpolation*delay*real_frequency/fs))%(Npt*interpolation)))%(Npt*interpolation);
    comptD_Q=(comptD_I+(Npt*interpolation)/4)%(Npt*interpolation);
    step=(int)round((Npt*interpolation)*(real_frequency/fs));
    feedback=0;
}

double Pixel::getfeedback()
{
    return feedback;
}

double Pixel::getmodule()
{
    return bbfb.module();
}

void Pixel::computeLC()
{
    I=tes.computeLCTES(frequency);
}

double Pixel::getI()
{
    return I;
}

void Pixel::computeBBFB(double demoduI, double remoduI, double demoduQ, double remoduQ, double input)
{
    bbfb.compute_feedback(demoduI,remoduI,demoduQ,remoduQ,input);
    comptR_I=(comptR_I+step)%(Npt*interpolation);
    comptD_I=(comptD_I+step)%(Npt*interpolation);
    comptR_Q=(comptR_Q+step)%(Npt*interpolation);
    comptD_Q=(comptD_Q+step)%(Npt*interpolation);
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

void Pixel::setinputLC(double input)
{
    tes.setbias(input);
}

double Pixel::getbiasm()
{
    return tes.getbiasm();
}

void Pixel::setI(double p)
{
    tes.setI(p);
}
