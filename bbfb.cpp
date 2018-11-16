#include "bbfb.h"
#include <math.h>
#include "global.h"

BBFB::BBFB()
{

}

BBFB::BBFB(int npr, int trunc_demodulation, int ni, int nr):npr(npr),nd(nd),ni(ni),nr(nr)
{
    I=0;
    Q=0;
    feedback=0;
    mode=true;
}

BBFB::~BBFB()
{

}

void BBFB::compute_feedback(double demoduI, double remoduI, double demoduQ, double remoduQ, double input)
{
    if (mode)
    {
        I+=G*(demoduI*input/Npr);
        Q+=G*(demoduQ*input/Npr);
        feedback = ((remoduI*I+remoduQ*Q)/Npr);
    }
    else
    {
        I+=G*trunc(demoduI*input/nd);
        Q+=G*trunc(demoduQ*input/nd);
        feedback = trunc((remoduI*I+remoduQ*Q)/nr);
    }
}

double BBFB::getfeedback()
{
    return feedback;
}

double BBFB::module()
{
    return (sqrt(pow(I,2)+pow(Q,2)));
}
