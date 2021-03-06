#ifndef CONFIG_H
#define CONFIG_H
#include <QWidget>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QDateTimeEdit>
#include <QLayout>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>


class config: public QWidget
{
    Q_OBJECT
public:
    config();
    virtual ~config();
public slots:
    void setVal();
    void load();
    void saved();
    void openTruncation();
private:
    QDoubleSpinBox *sampling_frequency;
    QSpinBox *Npoint;
    QSpinBox *Npixels;
    QSpinBox *N_fit;
    QDoubleSpinBox *pulse_energy;
    QDoubleSpinBox *bin;
    QSpinBox *N_pt;
    QSpinBox *N_pr;
    QSpinBox *interpol;
    QDoubleSpinBox *Int0;
    QDoubleSpinBox *Res0;
    QDoubleSpinBox *Temp0;
    QDoubleSpinBox *G_b;
    QDoubleSpinBox *alpha_cst;
    QDoubleSpinBox *beta_cst;
    QDoubleSpinBox *Rl_cst;
    QDoubleSpinBox *C_therm;
    QDoubleSpinBox *T_bath;
    QDoubleSpinBox *TTR;
    QDoubleSpinBox *L_crit;
    QDoubleSpinBox *TESdsl;
    QDoubleSpinBox *B_TES;
    QDoubleSpinBox *f_c;
    QDoubleSpinBox *n_therm;
    QSpinBox *N_pat;
    QSpinBox *decimation_f;
    QSpinBox *filter_order;
    QDoubleSpinBox *gain_bbfb;
    QLabel *BandLabel;
    QSpinBox *delay_step;
    QDoubleSpinBox *full_scale;
    QSpinBox *DAC_bits;
    QDoubleSpinBox *DAC_B;
    QDoubleSpinBox *DACdslf;
    QDoubleSpinBox *DACdslb;
    QDoubleSpinBox *full_scale_adc;
    QSpinBox *ADC_bits;
    QDoubleSpinBox *ADC_B;
    QDoubleSpinBox *ADCdsl;
    QDoubleSpinBox *GLNA;
    QDoubleSpinBox *LNAdsl;
    QDoubleSpinBox *BLNA;
    QDoubleSpinBox *GSQUID;
    QDoubleSpinBox *SQUIDdsl;
    QDoubleSpinBox *BSQUID;
    QCheckBox *Ites;
    QCheckBox *Error;
    QCheckBox *Feedback;
    QCheckBox *IQ;

    QPushButton *Valider;
    QPushButton *Load;
    QPushButton *Annuler;
    QPushButton *Save;
    QPushButton *Trunc;

};

#endif // CONFIG_H
