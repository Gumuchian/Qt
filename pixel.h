#ifndef PIXEL_H
#define PIXEL_H
#include "bbfb.h"
#include "tes.h"

class Pixel
{
    public:
        Pixel();
        virtual ~Pixel();
        Pixel(double f_s, double frequency, int phase, int Delay, int npt, int interpol,int npr, int nd, int ni, int nr);
        double getfeedback();
        double getmodule();
        void computeBBFB(double demoduI, double remoduI, double demoduQ, double remoduQ, double input);
        int getcomptR_I();
        int getcomptR_Q();
        int getcomptD_I();
        int getcomptD_Q();
        double getbiasm();
        void setFrequency(double freq);

    protected:

    private:
        double f_s;
        double frequency;
        double real_frequency;
        int phase;
        BBFB bbfb;
        int comptD_I;
        int comptR_I;
        int comptD_Q;
        int comptR_Q;
        int step;
        double feedback;
        double input_adc;
        int npt;
        int interpol;
        int Delay;
};

#endif // PIXEL_H
