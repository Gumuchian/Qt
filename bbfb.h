#ifndef BBFB_H
#define BBFB_H


class BBFB
{
    public:
        BBFB();
        BBFB(int npr, int nd, int ni, int nr);
        virtual ~BBFB();
        void compute_feedback(double demoduI, double remoduI, double demoduQ, double remoduQ, double input);
        double getfeedback();
        double module();

    protected:

    private:
        int npr;
        int nd;
        int ni;
        int nr;
        double I;
        double Q;
        double feedback;
        bool mode;
};

#endif // BBFB_H
