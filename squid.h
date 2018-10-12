#ifndef SQUID_H
#define SQUID_H


class SQUID
{
public:
    SQUID();
    double computeSQUID(double bias, double feedback, bool mode);
private:
    bool mode;
};

#endif // SQUID_H
