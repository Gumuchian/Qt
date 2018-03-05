#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qstring>
#include "xifu.h"
#include "config.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(420,260);
    this->setWindowTitle("X-IFU Simulator");
    QPixmap bkgnd("fenetre.jpg");
    bkgnd = bkgnd.scaled(100,200, Qt::KeepAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionConfig = new QAction("&Configuration", this);
    menuFichier->addAction(actionConfig);
    connect(actionConfig, SIGNAL(triggered()), this, SLOT(openConfig()));
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
    mode=2;

}

MainWindow::~MainWindow()
{
    thread->terminate();
    thread->wait();
    delete ui;
}

void MainWindow::displayresult()
{
    QMessageBox::information(this, "Results", instrument.getResults());
}

void MainWindow::simulate()
{
    thread = new QThread(this);
    instrument.moveToThread(thread);
    connect(thread, SIGNAL(finished()), &instrument, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), &instrument, SLOT(simulate()));
    progress = new QProgressBar;
    progress->setWindowTitle("Progression");
    progress->setFixedSize(400,50);
    progress->show();
    connect(&instrument, SIGNAL(getProgress(int)),progress, SLOT(setValue(int)));
    thread->start();
    connect(&instrument, SIGNAL(simulation_ended()), progress, SLOT(close()));
}

void MainWindow::setmode1()
{
    instrument.setMode(1);
    QMessageBox::information(this, "Mode", "Calibration mode selected");
}

void MainWindow::setmode2()
{
    instrument.setMode(2);
    QMessageBox::information(this, "Mode", "Resolution estimation mode selected");
}

void MainWindow::openConfig()
{
    config *conf = new config();
    conf->show();
}

