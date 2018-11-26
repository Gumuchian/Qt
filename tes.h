#ifndef TES_H
#define TES_H

class TES
{
    public:
        TES(unsigned seed, double L_crit, double TTR, double f_s, double frequency);
        virtual ~TES();
        double computeLCTES();
        void setBias(double sig);
        double getI();
        double getbiasm();
        void setI(double p);
        void setMax(double max);
    protected:

    private:
        double frequency;
        double Ccar;
        double Ccp;
        double coeff_1;
        double coeff_2;
        double coeff_3;
        double I;
        double biasm[3];
        double bias[3];
        double max_LC;
        double L_crit;
        double TTR;
        double f_s;
};

#endif // TES_H
