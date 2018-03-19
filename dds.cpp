#include "DDS.h"
#include <math.h>
#include "global.h"

DDS::DDS()
{

}

DDS::~DDS()
{

}

DDS::DDS(int taille, int precision, int interp)
{
    taille = taille;
    precision = precision;
    interp = interp;
    table = new int[interp*taille+1];
    int i,j;
    for (i=0;i<taille+1;i++){
        table[i*interp]=trunc(precision*cos(2*PI*i/taille));
    }
    for (i=0;i<taille;i++){
        for (j=0;j<interp;j++){
            table[j+i*interp]=(((table[(i+1)*interp]-table[i*interp])*j)/interp)+table[i*interp];
        }
    }
}
int DDS::getvalue(int indice)
{
    return table[indice];
}


