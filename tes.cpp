#include "tes.h"
#include <math.h>
#include <fstream>
#include <random>
#include "global.h"

TES::TES(unsigned seed, double L_crit, double TTR, double f_s, double frequency):L_crit(L_crit),TTR(TTR),f_s(f_s),frequency(frequency)
{
    I=I0;
    Ccar=(1/(4*pow(PI,2)*L_crit*pow(TTR,2)*pow(frequency,2)));
    Ccp=Ccar/100.0;
    coeff_1=-(2-8*L_crit*pow(TTR,2)*(Ccar+Ccp)*pow(f_s,2))/(2*f_s*pow(TTR,2)*R0*(Ccar+Ccp)+1+4*L_crit*pow(TTR,2)*(Ccar+Ccp)*pow(f_s,2));
    coeff_2=-(1-2*fs*pow(TTR,2)*R0*(Ccar+Ccp)+4*pow(f_s,2)*L_crit*pow(TTR,2)*(Ccar+Ccp))/(2*f_s*pow(TTR,2)*R0*(Ccar+Ccp)+1+4*L_crit*pow(TTR,2)*(Ccar+Ccp)*pow(f_s,2));
    coeff_3=2*f_s*Ccp/(2*f_s*pow(TTR,2)*R0*(Ccar+Ccp)+1+4*L_crit*pow(TTR,2)*(Ccar+Ccp)*pow(f_s,2));
    biasm[0]=0;biasm[1]=0;biasm[2]=0;
    bias[0]=0;bias[1]=0;bias[2]=0;
    max_LC=1;
}

TES::~TES()
{

}

double TES::computeLCTES()
{
    biasm[2]=coeff_1*biasm[1]+coeff_2*biasm[0]+coeff_3*(bias[2]-bias[0]);
    biasm[0]=biasm[1];biasm[1]=biasm[2];
    bias[0]=bias[1];bias[1]=bias[2];

    return biasm[2]/max_LC*I*sqrt(2)/TTR;
}

void TES::setBias(double sig)
{
    bias[2]=sig;
}

double TES::getI()
{
    return I;
}

double TES::getbiasm()
{
    return biasm[2];
}

void TES::setI(double p)
{
    I=p;
}

void TES::setMax(double max)
{
    max_LC=max;
}
