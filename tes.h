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
    protected:

    private:

        double I;
        double biasm[3];
        double bias[3];
        double bbfi[2];
        double bbfo[2];
        std::mt19937 gen;
};

#endif // TES_H
