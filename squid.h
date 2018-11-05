#ifndef SQUID_H
#define SQUID_H
#include <random>

class SQUID
{
public:
    SQUID();
    SQUID(double M_b, double M_f, double G_squid, double squid_dsl, double b_squid);
    double computeSQUID(double bias, double feedback, bool mode);
private:
    bool mode;
    double M_b;
    double M_f;
    double G_squid;
    double squid_dsl;
    double b_squid;
    std::mt19937 gen;
    std::normal_distribution<double> SQUID_noise;
};

#endif // SQUID_H
