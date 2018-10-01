#include "tes.h"
#include <math.h>
#include <fstream>
#include <random>
#include "global.h"

TES::TES():gen((std::random_device())())
{
    I=I0;
    biasm[0]=0;biasm[1]=0;biasm[2]=0;
    bias[0]=0;bias[1]=0;bias[2]=0;
}

TES::~TES()
{

}

double TES::computeLCTES(double freq)
{
    double Ccar=(1/(4*pow(PI,2)*Lcrit*pow(TR,2)*pow(freq,2))),
    Ccp=Ccar/100.0,
    A=Ccp,
    B=pow(TR,2)*R0*(Ccar+Ccp),
    C=Lcrit*pow(TR,2)*(Ccar+Ccp);
    biasm[2]=(-(2-8*C*pow(fs,2))*biasm[1]-(1-2*fs*B+4*pow(fs,2)*C)*biasm[0]+2*fs*A*(bias[2]-bias[0]))/(2*fs*B+1+4*C*pow(fs,2));
    biasm[0]=biasm[1];biasm[1]=biasm[2];
    bias[0]=bias[1];bias[1]=bias[2];
    return biasm[2]/0.594528739972466*I*sqrt(2)/TR;
}

void TES::setbias(double biass)
{
    bias[2]=biass;
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
