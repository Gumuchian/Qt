#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <math.h>
#include <Channel.h>
#include <fstream>
#include <string>
#include <Pixel.h>
#include <Channel.h>
#include <stdlib.h>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>
#include "ressources.h"
#include <CIC.h>
#include <DDS.h>
#include <Butterworth.h>
#include <Pulse_generator.h>
#include <complex>
#include <valarray>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
using namespace boost::numeric;

typedef complex<double> Complex;
typedef valarray<Complex> CArray;


template<class T>
bool InvertMatrix(const ublas::matrix<T>& input, ublas::matrix<T>& inverse)
{
    typedef ublas::permutation_matrix<std::size_t> pmatrix;
    ublas::matrix<T> A(input);
    pmatrix pm(A.size1());
    int res = lu_factorize(A, pm);
    if (res != 0)
        return false;
    inverse.assign(ublas::identity_matrix<T> (A.size1()));
    lu_substitute(A, pm, inverse);
    return true;
}


void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    CArray even = x[slice(0,N/2,2)];
    CArray  odd = x[slice(1,N/2,2)];

    fft(even);
    fft(odd);

    for (size_t k=0;k<N/2;++k)
    {
        Complex t = polar(1.0,-2*PI*k/N)*odd[k];
        x[k]=even[k]+t;
        x[k+N/2]=even[k]-t;
    }
}

void ifft(CArray& x)
{
    x = x.apply(conj);
    fft(x);
    x = x.apply(conj);
    x /= x.size();
}

double gradient_descent(ublas::vector<double> coeff)
{
    double pas=Nfit/2;
    double x[2]={-3,0};
    ublas::vector<double> X0(order_fit+1),X1(order_fit+1);
    for (int i=0;i<20;i++)
    {
        x[1]=x[0]+pas;
        for (int j=0;j<order_fit+1;j++)
        {
            X0(j)=pow(x[0],order_fit-j);
            X1(j)=pow(x[1],order_fit-j);
        }
        pas/= (ublas::inner_prod(X1,coeff)<ublas::inner_prod(X0,coeff) ? -2:2);
        x[0]=x[1];
    }
    return (double) ublas::inner_prod(X1,coeff);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
