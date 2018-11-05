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
        Channel(double f_s, int N_pt, int N_pr, int interpol, int N_pix, int Delay, int nd, int ni, int nr);
        virtual ~Channel();
        double sumBias();
        void computeAllBBFB(double input);
        double getfck();
        double getmod();
        void setFrequencies(double freq[]);
    protected:
    private:
        std::vector<Pixel> ch;
        int N_pt;
        int N_pr;
        int interpol;
        int N_pix;
        int Delay;
        DDS dds;
        double input;
        double *feedback;
        std::mt19937 gen;
};

#endif // CHANNEL_H
