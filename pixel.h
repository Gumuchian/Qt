#ifndef PIXEL_H
#define PIXEL_H
#include "BBFB.h"
#include "TES.h"

class Pixel
{
    public:
        Pixel();
        Pixel(double frequency, double real_frequency, int phase);
        double getfeedback();
        double getmodule();
        void setinputLC(double input);
        void computeLC();
        void computeBBFB(double demoduI, double remoduI, double demoduQ, double remoduQ, double input);
        int getcomptR_I();
        int getcomptR_Q();
        int getcomptD_I();
        int getcomptD_Q();
        double getbiasm();
        double getI();
        void setI(double p);

    protected:

    private:
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
        double I;
        double input_adc;
        TES tes;
};

#endif // PIXEL_H
