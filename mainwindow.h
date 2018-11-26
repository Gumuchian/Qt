#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QWidget>
#include <string>
#include "xifu.h"
#include "simulation.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void displayresult();
    void simulate();
    void setmode1();
    void setmode2();
    void setmode3();
    void openConfig();
    void Export();
    void computeHist(QVector<double> &hist, QVector<double> data, int Nbin, double binW, double MidBin);
    void test(QVector<double> energies);

private:
    Ui::MainWindow *ui;
    QVector<Simulation *> simulation;
    QVector<double> Energies;
    QPushButton *bouton;
    QPushButton *bouton_launch;
    QPushButton *Calibration_mode;
    QPushButton *Resolution_mode;
    QPushButton *Gain;
    QWidget *fenetre;
    QProgressBar *progress;
    int mode;
    QString results;
};

#endif // MAINWINDOW_H
