#ifndef CHANNEL_H
#define CHANNEL_H
#include <vector>
#include "pixel.h"
#include "dds.h"
#include <random>

class Channel
{
    public:
        Channel();
        virtual ~Channel();
        double sumPolar();
        void computeLC_TES();
        double computeBBFB();
        double getinput();
        double getfck();
        double getmod();
        void setI(double p);
    protected:
    private:
        std::vector<Pixel> ch;
        DDS dds;
        double input;
        double *feedback;
        std::mt19937 gen;
};

#endif // CHANNEL_H
