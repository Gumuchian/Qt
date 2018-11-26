#ifndef EVENT_PROCESSOR_H
#define EVENT_PROCESSOR_H
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <valarray>
#include <QString>
#include <QVector>

using namespace boost::numeric;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

class Event_Processor
{
    public:
        Event_Processor();
        Event_Processor(int Npattern);
        virtual ~Event_Processor();
        void trigger_function();
        void computeOptimalFilter();
        void computeFit();
        void computeEventProcessor();
        double getEnergy();
        template<class T> bool InvertMatrix(const ublas::matrix<T>& input, ublas::matrix<T>& inverse);
        void setInput(double input);
        void setThreshold(double thres);
        void setImpulseResponse(ublas::vector<double> IR);
        bool getRecording();
        void computeImpulseResponse();
        void recordImpulseResponse();
        void ExtractData(QString path, char *buffer, int &ind, int &size);
        double getData(char buffer[]);
        void fft(CArray& x);
        void ifft(CArray& x);
        void setMode(bool mod);
        CArray getIR();
        void setRecording();
        double gett0();
        void setOffset(double off);
        double getOutput();
        double convert(double au);
        void computeCorrCoeff(ublas::vector<double> AU, ublas::vector<double> energies);
        CArray getPulseSpectrum();
        CArray getNoiseSpectrum();
        CArray getPulsePhase();

    private:
        int counter;
        int count;
        bool wait;
        double Threshold;
        bool ReadyToCompute;
        bool recording;
        ublas::vector<double> Trigger_coeff;
        ublas::vector<double> Buffer;
        ublas::vector<double> corr_coeff;
        ublas::vector<double> Record;
        ublas::vector<double> OutputFilter;
        ublas::vector<double> ImpulseResponse;
        ublas::vector<double> Poly_coeff;
        double Trigger_output;
        int RecordSize;
        double factor;
        double energy;
        double offset;
        double t0;
        ublas::matrix<double> Z;
        int noise_size;
        int pulse_size;
        int noise_offset;
        int pulse_offset;
        char *noise;
        char *pulse;
        bool mode;
        int factor_count;
        CArray pulse_fft;
        CArray noise_fft;
        CArray pulse_phase;
        CArray IR;
        ublas::vector<double> energy_curve_coeff;
};

#endif // EVENT_PROCESSOR_H
