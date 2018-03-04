#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QWidget>
#include <string>
#include "xifu.h"

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
    void openConfig();

private:
    Ui::MainWindow *ui;
    xifu instrument;
    QPushButton *bouton;
    QPushButton *bouton_launch;
    QPushButton *Calibration_mode;
    QPushButton *Resolution_mode;
    QWidget *fenetre;
    QProgressBar *progress;
    QThread *thread;
};

#endif // MAINWINDOW_H
