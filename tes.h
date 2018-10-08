#ifndef TES_H
#define TES_H
#include <random>

class TES
{
    public:
        TES();
        virtual ~TES();
        double computeLCTES(double freq);
        void setbias(double biass);
        double getI();
        double getbiasm();
        void setI(double p);
        void setMax(double max);
    protected:

    private:

        double I;
        double biasm[3];
        double bias[3];
        std::mt19937 gen;
        double max_LC;
};

#endif // TES_H
