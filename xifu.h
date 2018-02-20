#ifndef XIFU_H
#define XIFU_H
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
#include "global.h"
#include <CIC.h>
#include <DDS.h>
#include <Butterworth.h>
#include <Pulse_generator.h>
#include <complex>
#include <valarray>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <QString>
#include <QWidget>

using namespace std;
using namespace boost::numeric;

typedef complex<double> Complex;
typedef valarray<Complex> CArray;

class xifu: public QWidget
{
public:
    xifu();
    void fft(CArray& x);
    void ifft(CArray& x);
    template<class T> bool InvertMatrix(const ublas::matrix<T>& input, ublas::matrix<T>& inverse);
    QString getResults();
    void simulate();
    int getProgress();
    void setMode(int mod);
private:
    int mode;
    Channel ch0;
    Butterworth Butter;
    Pulse_generator pulse_generator;
    QString results;
    double *pulse;
    double *puls_inter;
    double *pattern;
    int progress;
};

#endif // XIFU_H
