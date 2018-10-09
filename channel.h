#ifndef CHANNEL_H
#define CHANNEL_H
#include <vector>
#include "pixel.h"
#include "dds.h"
#include "dac.h"
#include "squid.h"
#include "adc.h"
#include <random>

class Channel
{
    public:
        Channel();
        virtual ~Channel();
        double sumPolar();
        void setPolar(double polar);
        double computeLC_TES();
        double computeBBFB();
        double getinput();
        double getfck();
        double getmod();
        void setI(double p);
        void setFrequencies(double freq[]);
        void setMax(double maxLC);
    protected:
    private:
        std::vector<Pixel> ch;
        DDS dds;
        DAC dac;
        ADC adc;
        SQUID squid;
        double input;
        double *feedback;
        std::mt19937 gen;
};

#endif // CHANNEL_H
