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

class xifu: public QObject
{
    Q_OBJECT
public:
    xifu();
    virtual ~xifu();
    void fft(CArray& x);
    void ifft(CArray& x);
    template<class T> bool InvertMatrix(const ublas::matrix<T>& input, ublas::matrix<T>& inverse);
    QString getResults();
    void sweepLC(Channel &ch);
    void setMode(int mod);
    void getE(vector<double> &En);
    void getSpectrum(QVector<double> &Spect);
public slots:
    void simulate();
signals:
    void getProgress(int prog);
    void simulation_ended();
private:
    int mode;
    QString results;
    vector<double> E;
    ublas::vector<double> energy_gain;
    double *pulse;
    double frequency[40];
    double max_LC;
    double *puls_inter;
    double *pattern;
    long progress;
};

#endif // XIFU_H
