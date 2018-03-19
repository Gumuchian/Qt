#ifndef BUTTERWORTH_H
#define BUTTERWORTH_H


class Butterworth
{
    public:
        Butterworth();
        virtual ~Butterworth();
        double compute(double in);
        bool getaccess();

    protected:

    private:
        int index;
        double *input;
        double *output;
        double **coeff;
        bool access;
};

#endif // BUTTERWORTH_H
