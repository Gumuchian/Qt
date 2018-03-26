#include "xifu.h"
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
#include "global.h"
#include <DDS.h>
#include <Butterworth.h>
#include <Pulse_generator.h>
#include <complex>
#include <valarray>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <QString>

using namespace std;
using namespace boost::numeric;

typedef complex<double> Complex;
typedef valarray<Complex> CArray;

xifu::xifu()
{
    pulse = new double[Npul];
    puls_inter = new double[Npat];
    pattern = new double[Npat];
    mode=2;
}

xifu::~xifu()
{

}

void xifu::simulate()
{
    Channel ch0;
    Butterworth Butter;
    Pulse_generator pulse_generator;
    progress=0; 
    int i,k,ip=0,l=0,n_alea=0,m;
    vector<double> module(Npat,0);
    vector<double> E;
    string str;
    double sum,Em=0,var=0,P=0,maxi=0,a=0,energy_mode,puls;
    ublas::matrix<double> X(Nfit,order_fit+1),Z(order_fit+1,order_fit+1);
    for (i=0;i<Nfit;i++)
    {
        for (int j=0;j<order_fit+1;j++)
        {
            X(i,j)=pow(i-Nfit/2,order_fit-j);
        }
    }
    ublas::vector<double> Y(Nfit),poly_max(order_fit+1);
    fstream file1,file2,file3;
    file3.open("test.txt",ios::out);
    CArray sig_fft (Npat);
    CArray sig_ph (Npat);
    CArray noise_fft (Npat);
    for (i=0;i<Npat;i++)
    {
        noise_fft[i]=0;
        sig_fft[i]=0;
    }
    CArray div_fft (Npat);
    Complex *c = new Complex[Npat];
    const Complex const_i(0,1);

    if (mode==1)
    {
        file1.open("Pattern.txt",ios::out);
        file2.open("Facteur.txt",ios::out);
        energy_mode=1000;
    }
    else
    {
        file1.open("Pattern.txt",ios::in);
        file2.open("Facteur.txt",ios::in);
        energy_mode=energy;
        file2 >> P;
    }

    for (i=0;i<3000000;i++)
    {
        if (i==1000000)
        {
            pulse_generator.setPopt(energy_mode);
        }
        puls=pulse_generator.compute();
        if (i>=1000000 && i<1000000+Npul)
        {
        pulse[ip]=puls;
        ip++;
        }
    }
    ip=0;

    if (mode==2)
    {
       for (i=0;i<Npat;i++)
       {
           file1 >> pattern[i];
       }
    }

    for (long i=0;i<N;i++)
    {
        if (i%10000==0)
        {
            progress=(int)(100*(double)i/N);
            emit getProgress(progress);
        }
        ch0.sumPolar();
        if (mode==2)
        {
           if (ip>=n_alea+decimation && ip<Npul+n_alea+decimation)
           {
              ch0.setI(pulse[ip-n_alea-decimation]);
           }
        }
        else
        {
            if (i<N/2 && ip<Npul)
            {
                 ch0.setI(pulse[ip]);
            }
        }

        ch0.computeLC_TES();
        ch0.computeBBFB();

        if (i==Npat*decimation)
        {
            maxi=ch0.getmod();
        }

        if (mode==2)
        {
            if (i>Npat*decimation-Nfit/2*decimation+decimation)
            {
                a=Butter.compute(maxi-ch0.getmod());
                if (Butter.getaccess())
                {
                    module.push_back(a);
                    module.erase(module.begin());
                    if (l<Nfit)
                    {
                        if (l==0)
                        {
                            n_alea=rand()%decimation-decimation/2;
                        }
                        sum=0;
                        for (k=0;k<Npat;k++)
                        {
                            sum+=module[k]*pattern[k];
                        }
                        Y(l)=sum;
                    }
                    if (l==Nfit)
                    {
                        InvertMatrix(ublas::matrix<double> (ublas::prod(ublas::trans(X),X)),Z);
                        poly_max=ublas::prod(ublas::prod(Z,ublas::trans(X)),Y);
                        E.push_back(1000.0*(poly_max(2)-pow(poly_max(1),2)/(2*poly_max(0)))/P);
                    }
                    l++;
                    l=l%Npat;
                }
            }
        }
        else
        {
            if (i>Npat*decimation+decimation)
            {
                a=Butter.compute(maxi-ch0.getmod());
                if (Butter.getaccess())
                {
                    module.push_back(a);
                    module.erase(module.begin());
                    if (l==0)
                    {
                        for (k=0;k<Npat;k++)
                        {
                            c[k]=module[k];
                        }
                        CArray mod(c,Npat);
                        fft(mod);
                        if (i<N/2)
                        {
                            sig_fft+=abs(mod);
                            for (m=0;m<Npat;m++)
                            {
                                sig_ph[m]=arg(mod[m]);
                                puls_inter[m]=module[m];
                            }
                        }
                        else
                        {
                            noise_fft+=abs(mod);
                        }
                    }
                    l++;
                    l=l%Npat;
                }
            }
        }
        ip++;
        ip=ip%(Npat*decimation);
    }

    if (mode==1)
    {
        div_fft=sig_fft/noise_fft;
        for (i=0;i<Npat;i++)
        {
            div_fft[i]*=exp(const_i*sig_ph[i]);
        }
        ifft(div_fft);
        for (i=0;i<Npat;i++)
        {
            file1 << real(div_fft[i]) << endl;
            P+=puls_inter[i]*real(div_fft[i]);
        }
        file2 << P;
    }
    else
    {
        for (i=3;i<(int)E.size();i++)
        {
            Em+=abs(E[i]);
        }
        Em/=(E.size()-3);

        for (i=3;i<(int)E.size();i++)
        {
            var+=pow(abs(E[i]-Em),2);
        }
        var=energy/Em*2.35*sqrt(var/(E.size()-3));

        results=QString::fromStdString("Input energy: "+to_string(energy)+" eV\n"
               +"Number of estimations: "+to_string(E.size()-3)+"\n"
               +"pattern @ "+to_string(1000)+" eV"+"\n"
               +"Energy estimation: "+to_string(Em)+" eV\n"
               +"Relative error: "+to_string(abs(energy-Em)/energy)+"\n"
               +"Resolution: "+to_string(var)+" eV\n");
    }
    file1.close();
    file2.close();
    file3.close();
    progress=100;
    emit getProgress(progress);
    emit simulation_ended();
}

void xifu::fft(CArray& x)
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

void xifu::ifft(CArray& x)
{
    x = x.apply(conj);
    fft(x);
    x = x.apply(conj);
    x /= x.size();
}

template<class T>
bool xifu::InvertMatrix(const ublas::matrix<T>& input, ublas::matrix<T>& inverse)
{
    typedef ublas::permutation_matrix<std::size_t> pmatrix;
    ublas::matrix<T> A(input);
    pmatrix pm(A.size1());
    int res = lu_factorize(A, pm);
    if (res != 0) return false;
    inverse.assign(ublas::identity_matrix<T> (A.size1()));
    lu_substitute(A, pm, inverse);
    return true;
}

QString xifu::getResults()
{
    return results;
}

void xifu::setMode(int mod)
{
    mode=mod;
}
