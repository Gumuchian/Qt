#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qstring>
#include "xifu.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("X-IFU SImulator");
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    bouton = new QPushButton("Display results",this);
    bouton->setFixedSize(300,50);
    bouton->move(60,100);
    connect(bouton, SIGNAL(clicked()), this, SLOT(displayresult()));

    bouton_launch = new QPushButton("Launch simulation",this);
    bouton_launch->setFixedSize(300,50);
    bouton_launch->move(60,50);
    connect(bouton_launch, SIGNAL(clicked()), this, SLOT(simulate()));

    Calibration_mode = new QPushButton("Calibration",this);
    Calibration_mode->move(60,150);
    Calibration_mode->setFixedSize(150,50);
    connect(Calibration_mode, SIGNAL(clicked()), this, SLOT(setmode1()));

    Resolution_mode = new QPushButton("Resolution",this);
    Resolution_mode->move(210,150);
    Resolution_mode->setFixedSize(150,50);
    connect(Resolution_mode, SIGNAL(clicked()), this, SLOT(setmode2()));

    //progress->setValue(instrument.getProgress());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayresult()
{
    QMessageBox::information(this, "Results", instrument.getResults());
}

void MainWindow::simulate()
{
    instrument.simulate();
}

void MainWindow::setmode1()
{
    instrument.setMode(1);
    QMessageBox::information(this, "Mode", "Calibration mode selected");
}

void MainWindow::setmode2()
{
    instrument.setMode(2);
    QMessageBox::information(this, "Mode", "Resolution estimation selected");
}
