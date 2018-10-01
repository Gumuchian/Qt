#include "bbfb.h"
#include <math.h>
#include "global.h"

BBFB::BBFB()
{
    I=0;
    Q=0;
    feedback=0;
}

BBFB::~BBFB()
{

}

void BBFB::compute_feedback(double demoduI, double remoduI, double demoduQ, double remoduQ, double input)
{
    /*I+=G*trunc(demoduI*input/Npr);
    Q+=G*trunc(demoduQ*input/Npr);
    feedback = trunc((remoduI*I+remoduQ*Q)/Npr);*/
    I+=G*(demoduI*input/Npr);
    Q+=G*(demoduQ*input/Npr);
    feedback = ((remoduI*I+remoduQ*Q)/Npr);
}

double BBFB::getfeedback()
{
    return feedback;
}

double BBFB::module()
{
    return (sqrt(pow(I,2)+pow(Q,2)));
}
