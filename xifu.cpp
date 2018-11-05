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

xifu::xifu():energy_gain(6)
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
    /*Channel ch0;
    Butterworth Butter;
    Pulse_generator pulse_generator;
    progress=0; 
    int i,k,l=0,n_alea=0,m;
    double sum,Em=0,var=0,maxi=0,a=0,energy_mode,error=0;
    vector<double> module(Npat,0);
    ublas::vector<double> Y(Nfit),poly_max(order_fit+1);
    ublas::matrix<double> X(Nfit,order_fit+1),Z(order_fit+1,order_fit+1);
    CArray sig_fft (Npat), sig_ph (Npat), noise_fft (Npat), div_fft (Npat);
    Complex *c = new Complex[Npat];
    const Complex const_i(0,1);
    fstream file1,file2,file3;
    file3.open("test.txt",ios::out);

    if (E.size()!=0)
    {
        E.erase(E.begin(),E.end());
    }

    for (i=0;i<Nfit;i++)
    {
        for (int j=0;j<order_fit+1;j++)
        {
            X(i,j)=pow(i-Nfit/2,order_fit-j);
        }
    }

    for (i=0;i<Npat;i++)
    {
        noise_fft[i]=0;
        sig_fft[i]=0;
    }

    if (mode==1)
    {
        file1.open("Pattern.txt",ios::out);
        energy_mode=1000;
    }
    else
    {
        file1.open("Pattern.txt",ios::in);
        for (i=0;i<Npat;i++)
        {
            file1 >> pattern[i];
        }
        energy_mode=energy;
    }

    sweepLC(ch0);

    if (mode==3)
    {
        sum=0;
        int l=0;
        ublas::matrix<double> UA(7,6),M(6,6);
        ublas::vector<double> energies(7);
        for (int i=0;i<Npat;i++)
        {
            file1 >> pattern[i];
        }

        for (int i=0;i<7;i++)
        {
            progress=(int)(100*(double)i/7);
            emit getProgress(progress);
            energy=200+i*1000;
            energies(i)=energy;

            for (int k=0;k<3*Npat*decimation;k++)
            {
                ch0.sumPolar();
                ch0.setI(pulse_generator.compute());
                ch0.computeLC_TES();
                ch0.computeBBFB();
                if (k==Npat*decimation)
                {
                    maxi=ch0.getmod();
                }
                if (k>Npat*decimation)
                {
                    a=Butter.compute(maxi-ch0.getmod());
                    if (Butter.getaccess())
                    {
                        module.push_back(a);
                        module.erase(module.begin());
                        if (l==0)
                        {
                            pulse_generator.setPopt(energy);
                            sum=0;
                            for (m=0;m<Npat;m++)
                            {
                                sum+=module[m]*pattern[m];
                            }
                        }
                        l++;
                        l=l%Npat;
                    }
                }
            }
            for (int n=0;n<6;n++)
            {
                UA(i,n)=pow(sum/10000,5-n);
            }
        }
        InvertMatrix(ublas::matrix<double> (ublas::prod(ublas::trans(UA),UA)),M);
        energy_gain=ublas::prod(ublas::prod(M,ublas::trans(UA)),energies);
    }
    else
    {
        for (long i=0;i<N;i++)
        {
            if (saveItes)
            {
                file3 << ch0.getinput() << "\t";
            }
            if (saveError)
            {
                file3 << error << "\t";
            }
            if (saveFeedback)
            {
                file3 << ch0.getfck() << "\t";
            }
            if (saveIQ)
            {
                file3 << ch0.getmod() << "\t";
            }
            if (saveItes || saveError || saveFeedback || saveIQ)
            {
                file3 << std::endl;
            }
            if (i%10000==0)
            {
                progress=(int)(100*(double)i/N);
                emit getProgress(progress);
            }
            ch0.sumPolar();
            if (mode==2)
            {
                ch0.setI(pulse_generator.compute());
            }
            else
            {
                if (i<N/2)
                {
                    ch0.setI(pulse_generator.compute());
                }
            }

            ch0.computeLC_TES();
            error=ch0.computeBBFB();

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
                                pulse_generator.setPopt(energy_mode);
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
                            double ua=poly_max(2)-pow(poly_max(1),2)/(2*poly_max(0)),en=0;
                            for(int u=0;u<6;u++)
                            {
                                en+=energy_gain(u)*pow(ua/10000,5-u);
                            }
                            E.push_back(en);
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
                            pulse_generator.setPopt(energy_mode);
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
                file1 << real(div_fft[i]) << "\n";
            }
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
            var=2.35*sqrt(var/(E.size()-3));
            results=QString::fromStdString("Input energy: "+to_string(energy)+" eV\n"
               +"Number of estimations: "+to_string(E.size()-3)+"\n"
               +"pattern @ "+to_string(1000)+" eV"+"\n"
               +"Energy estimation: "+to_string(Em)+" eV\n"
               +"Relative error: "+to_string(abs(energy-Em)/energy)+"\n"
               +"Resolution: "+to_string(var)+" eV\n");
        }
    }
    file1.close();
    file2.close();
    file3.close();
    progress=100;
    emit getProgress(progress);
    emit simulation_ended();*/
}

void xifu::sweepLC(Channel &ch)
{/*
    double sig=1;
    int Nsweep=21;
    CArray TF((int)pow(2,Nsweep));
    for (int i=0;i<(int)pow(2,Nsweep);i++)
    {
        ch.setPolar(sig);
        ch.computeLC_TES();
        TF[i]=ch.getinput();
        sig=0;
    }
    fft(TF);
    int index=950000*pow(2,Nsweep)/fs;
    double max_LC=0;
    for (int i=0;i<Npix;i++)
    {
       max_LC=0;
       for (int j=0;j<(int)(50000/fs*pow(2,Nsweep));j++)
       {

           if (max_LC < abs(TF[index+j]))
           {
               frequency[i]=(index+j)*fs/pow(2,Nsweep);
               max_LC=abs(TF[index+j]);
           }
       }
       index=(int)((frequency[i]+50000)*pow(2,Nsweep)/fs)+1000;
    }
    max_LC=0;
    for (int i=0;i<(int)pow(2,Nsweep);i++)
    {
        sig=cos(2*PI*frequency[0]/fs*i);
        ch.setPolar(sig);
        ch.computeLC_TES();
        TF[i]=ch.getinput();
    }
    for (int i=0;i<(int)pow(2,Nsweep-1);i++)
    {
        if (max_LC < abs(TF[pow(2,Nsweep-1)+i]))
        {
            max_LC=abs(TF[pow(2,Nsweep-1)+i]);
        }
    }
    ch.setFrequencies(frequency);
    max_LC/=I0*sqrt(2)/TR;
    ch.setMax(max_LC);*/
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

void xifu::getE(vector<double> &En)
{
    En=E;
}

void xifu::getSpectrum(QVector<double> &Spect)
{
    Complex cp[Npat];
    for (int i=0;i<Npat;i++)
    {
        cp[i]=pattern[i];
    }
    CArray spectrum(cp,Npat);
    fft(spectrum);
    QVector<double> spec(Npat/2);
    for (int i=0;i<Npat/2;i++)
    {
        spec[i]=20*log10(abs(spectrum[i]));
    }
    Spect=spec;
}
