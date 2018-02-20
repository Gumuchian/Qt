#include "CIC.h"
#include <math.h>
#include "global.h"


CIC::CIC()
{
    int i;
    index = 0;
    access = false;
    integ = new double*[order+1];
    comb = new double*[order+1];
    coeff_i=new double[order+1];
    coeff_c=new double[order+1];
    coeff_i[0]=0;coeff_i[1]=3;coeff_i[2]=5;coeff_i[3]=4;coeff_i[4]=2;
    coeff_c[0]=0;coeff_c[1]=1;coeff_c[2]=1;coeff_c[3]=1;coeff_c[4]=2;
    for (i=0;i<order+1;i++)
    {
        integ[i]=new double[2];
        comb[i]=new double[2];
        comb[i][0]=0;comb[i][1]=0;
        integ[i][0]=0;integ[i][1]=0;
    }
}


double CIC::compute(double input)
{
    int i;
    integ[0][1]=input;
    for (i=1;i<order+1;i++)
    {
        integ[i][1]=integ[i][0]+trunc(integ[i-1][1]/pow(2,coeff_i[i-1]));
    }
    if (index==0)
    {
        comb[0][1]=trunc(integ[order][1]/pow(2,coeff_i[order]));
        for (i=1;i<order+1;i++)
        {
            comb[i][1]=trunc(comb[i-1][1]/pow(2,coeff_c[i]))-comb[i-1][0];
        }
        for (i=0;i<order+1;i++)
        {
            comb[i][0]=comb[i][1];
        }
        access = true;
    }
    else {access = false;}
    for (i=0;i<order+1;i++)
    {
        integ[i][0]=integ[i][1];
    }
    index++;
    index=index%decimation;
    return comb[order][1]/pow(2,coeff_c[order]);
}

bool CIC::getaccess()
{
    return access;
}
