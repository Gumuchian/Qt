#ifndef LNA_H
#define LNA_H
#include<random>
#include<ctime>

class LNA
{
public:
    LNA(double G_LNA, double dsl_LNA, double b_LNA);
    double compute(double input);
private:
    double G_LNA;
    double dsl_LNA;
    double b_LNA;
    std::normal_distribution<double> lna_noise;
    std::mt19937 gen;
};

#endif // LNA_H
