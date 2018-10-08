#ifndef PIXEL_H
#define PIXEL_H
#include "bbfb.h"
#include "tes.h"

class Pixel
{
    public:
        Pixel();
        virtual ~Pixel();
        Pixel(double frequency, int phase);
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
        void setFrequency(double freq);
        void setMaxLC(double maxLC);

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
