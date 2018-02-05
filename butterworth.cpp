#include "Butterworth.h"
#include <ressources.h>

Butterworth::Butterworth()
{
    int i;
    index = 0;
    access = false;
    input = new double[order+1];
    output = new double[order+1];
    coeff = new double*[order+1];
    for (i=0;i<order+1;i++)
    {
        coeff[i]= new double[2];
        input[i]=0;
        output[i]=0;
    }
    coeff[0][0]=0.000582076134236026;
    coeff[1][0]=0.00116415226847205;
    coeff[2][0]=0.000582076134236026;
    coeff[0][1]=1;
    coeff[1][1]=-1.93060642721967;
    coeff[2][1]=0.932934731756612;
}

double Butterworth::compute(double in)
{
    int i;
    input[0]=in;
    output[0]=0;
    output[0]+=coeff[0][0]*input[0];
    for (i=1;i<order+1;i++)
    {
        output[0]+=coeff[i][0]*input[i]-coeff[i][1]*output[i];
    }
    output[0]/=coeff[0][1];
    if (index==0)
    {
        access=true;
    }
    else
    {
        access=false;
    }
    index++;
    index=index%decimation;
    for (i=order;i>0;i--)
    {
        output[i]=output[i-1];
        input[i]=input[i-1];
    }
    return output[0];
}

bool Butterworth::getaccess()
{
    return access;
}
