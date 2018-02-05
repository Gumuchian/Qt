#ifndef BBFB_H
#define BBFB_H


class BBFB
{
    public:
        BBFB();
        void compute_feedback(double demoduI, double remoduI, double demoduQ, double remoduQ, double input);
        double getfeedback();
        double module();

    protected:

    private:
        double I;
        double Q;
        double feedback;
};

#endif // BBFB_H
