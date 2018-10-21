#ifndef DAC_H
#define DAC_H


class DAC
{
public:
    DAC();
    DAC(double dac_dsl, double b_dac, double fs_dac, double dac_bit);
    double computeDAC(double input);
private:
    double dac_dsl;
    double b_dac;
    double fs_dac;
    double dac_bit;
};

#endif // DAC_H
