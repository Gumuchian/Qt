#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qstring>
#include "xifu.h"
#include "config.h"
#include <QThread>
#include "qcustomplot.h"
#include <math.h>
#include <fstream>
#include "importation.h"
#include "simulation.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(420,260);
    this->setWindowTitle("X-IFU Simulator");

    QLabel *imageLabel = new QLabel(this);
    imageLabel->setAlignment (Qt::AlignCenter);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QPixmap pix = QPixmap::fromImage(QImage("fenetre.jpg"));
    imageLabel->setPixmap(pix.scaled(90,80,Qt::KeepAspectRatio));
    imageLabel->setGeometry(265,190,100,80);

    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionConfig = new QAction("&Configuration", this);
    actionConfig->setShortcut(QKeySequence("Ctrl+U"));
    menuFichier->addAction(actionConfig);
    connect(actionConfig, SIGNAL(triggered()), this, SLOT(openConfig()));
    QAction *actionExport = new QAction("&Export", this);
    menuFichier->addAction(actionExport);
    connect(actionExport, SIGNAL(triggered()), this, SLOT(Export()));
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
    delete ui;
}

void MainWindow::displayresult()
{
    if (Energies.size()!=0)
    {
        double Em=0,max=0,var=0,integral=0;
        int Nbin;
        for (int i=0;i<(int)Energies.size();i++)
        {
            Em+=Energies[i];
        }
        Em/=((int)Energies.size());
        for (int i=0;i<(int)Energies.size();i++)
        {
            var+=pow(Energies[i]-Em,2);
        }
        var/=(int)Energies.size();
        var=std::sqrt(var);

        Nbin=(int)std::ceil((6*var)/binWidth);
        QVector<double> Data(Nbin);
        computeHist(Data, Energies, Nbin, binWidth, Em);
        for (int i=0;i<Data.size();i++)
        {
            if (max<Data[i])
            {
                max=Data[i];
            }
        }

        QCustomPlot  *customPlot = new QCustomPlot;
        customPlot->setMinimumSize(750,900);
        QLinearGradient gradient(0, 0, 0, 400);
        gradient.setColorAt(0, QColor(255, 0, 10));
        gradient.setColorAt(0.38, QColor(105, 105, 105));
        gradient.setColorAt(1, QColor(70, 70, 70));
        customPlot->setBackground(QBrush(gradient));

        // create empty bar chart objects:
        QCPBars *energy_distrib = new QCPBars(customPlot->xAxis, customPlot->yAxis);
        energy_distrib->setAntialiased(false);
        energy_distrib->setStackingGap(1);
        // set names and colors:
        energy_distrib->setPen(QPen(QColor(111, 9, 176).lighter(170)));
        energy_distrib->setBrush(QColor(111, 9, 176));

        // prepare x axis with country labels:
        QVector<double> ticks(Nbin);
        QVector<QString> labels(Nbin);
        for (int i=0;i<Nbin;i++)
        {
            ticks[i]=i;
            labels[i]=QString::number(Em-3*var+i*binWidth);
            integral+=std::exp(-pow(Em-3*var+i*binWidth-Em,2)/(2*pow(var,2)));
        }

        QVector<double> abs_gaussian(10*Nbin);
        QVector<double> gaussian(10*Nbin);
        for (int i=0;i<(int)gaussian.size();i++)
        {
            abs_gaussian[i]=i/10.0;
            gaussian[i]=(int)Energies.size()/integral*std::exp(-pow(Em-3*var+i*binWidth/10-Em,2)/(2*pow(var,2)));
        }

        QCPGraph *fit = customPlot->addGraph();
        fit->setData(abs_gaussian, gaussian);
        fit->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
        fit->setPen(QPen(QColor(120, 120, 120), 2));

        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        textTicker->addTicks(ticks, labels);
        customPlot->xAxis->setLabel("eV");
        customPlot->xAxis->setTicker(textTicker);
        customPlot->xAxis->setTickLabelRotation(60);
        customPlot->xAxis->setSubTicks(false);
        customPlot->xAxis->setTickLength(0, 4);
        customPlot->xAxis->setRange(0, Nbin);
        //customPlot->xAxis->setBasePen(QPen(Qt::white));
        //customPlot->xAxis->setTickPen(QPen(Qt::white));
        customPlot->xAxis->grid()->setVisible(true);
        //customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        //customPlot->xAxis->setTickLabelColor(Qt::white);
        //customPlot->xAxis->setLabelColor(Qt::white);


        // prepare y axis:
        customPlot->yAxis->setRange(0,max);
        customPlot->yAxis->setPadding(5);
        customPlot->yAxis->setLabel("Number of photons");
        //customPlot->yAxis->setBasePen(QPen(Qt::white));
        //customPlot->yAxis->setTickPen(QPen(Qt::white));
        //customPlot->yAxis->setSubTickPen(QPen(Qt::white));
        customPlot->yAxis->grid()->setSubGridVisible(true);
        //customPlot->yAxis->setTickLabelColor(Qt::white);
        //customPlot->yAxis->setLabelColor(Qt::white);
        //customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        //customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        // Add data:
        energy_distrib->setData(ticks, Data);

        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        customPlot->replot();
        customPlot->show();

        /*QCustomPlot  *customPlotspec = new QCustomPlot;
        customPlotspec->setMinimumSize(700,500);
        customPlotspec->setWindowTitle("OF Transfer function");
        customPlotspec->addGraph();
        customPlotspec->graph(0)->setPen(QPen(Qt::blue));
        customPlotspec->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
        QVector<double> x(Npat/2), y(Npat/2);
        for (int i=0; i<Npat/2; ++i)
        {
          x[i] = i*fs/(decimation*Npat);
        }
        instrument.getSpectrum(y);
        customPlotspec->xAxis->setLabel("Hz");
        customPlotspec->yAxis->setLabel("dB");
        customPlotspec->graph(0)->setData(x, y);
        customPlotspec->graph(0)->rescaleAxes();
        customPlotspec->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        customPlotspec->show();*/
    }
    /*QWidget *window = new QWidget();
    QLabel *label = new QLabel(instrument.getResults(), window);
    label->show();
    window->setWindowTitle("Results");
    window->setFixedSize(350,100);
    window->show();*/
}

void MainWindow::simulate()
{    
    std::fstream file;
    file.open("Pattern.txt",std::ios::in);
    ublas::vector<double> IR(2048),energies(7);
    double offset;
    for (int i=0;i<2048;i++)
    {
        file >> IR(i);
    }
    file.close();
    simulation.push_back(new Simulation(N,0,decimation,fs,Lcrit,TR,Gb,ntherm,Tbath,Ctherm,Rl,R0,T0,I0,Npt,Npr,interpolation,1,delay,20,20,20,ADC_dsl,B_ADC,PE_ADC,ADC_bit,0,B_DAC,PE_DAC,DAC_bit,G_LNA,LNA_dsl,B_LNA,5.8*pow(10,-6),58*pow(10,-6),0.017,SQUID_dsl,B_SQUID,2048));
    offset = simulation[0]->EstimateOffset();
    energies = simulation[0]->EstimateEnergyCurve();
    if ((int)simulation.size() != 0)
    {
        simulation.erase(simulation.begin(),simulation.end());
    }
    if ((int)Energies.size() != 0)
    {
        Energies.erase(Energies.begin(),Energies.end());
    }
    QVector<QThread *> threads;
    for (int i=0;i<2;i++)
    {
        threads.push_back(new QThread);
        simulation.push_back(new Simulation(N,(unsigned long)(i*10),decimation,fs,Lcrit,TR,Gb,ntherm,Tbath,Ctherm,Rl,R0,T0,I0,Npt,Npr,interpolation,1,delay,20,20,20,ADC_dsl,B_ADC,PE_ADC,ADC_bit,0,B_DAC,PE_DAC,DAC_bit,G_LNA,LNA_dsl,B_LNA,5.8*pow(10,-6),58*pow(10,-6),0.017,SQUID_dsl,B_SQUID,2048));
        simulation[i]->setIR(IR);
        simulation[i]->setOffset(offset);
        simulation[i]->setCoefficientEnergyCurve(energies);
        simulation[i]->moveToThread(QApplication::instance()->thread());
        connect(threads[i], SIGNAL(finished()), simulation[i], SLOT(deleteLater()));
        if (mode == 2)
        {
            connect(threads[i], SIGNAL(started()), simulation[i], SLOT(simulate()));
            connect(simulation[i], SIGNAL(energies(QVector<double>)), this, SLOT(getEnergy(QVector<double>)));
        }
        else
        {
            connect(threads[i], SIGNAL(started()), simulation[i], SLOT(computeImpulseResponse()));
            connect(simulation[i], SIGNAL(pulses(QVector<double>)), this, SLOT(getPulse(QVector<double>)));
            connect(simulation[i], SIGNAL(noises(QVector<double>)), this, SLOT(getNoise(QVector<double>)));
            connect(simulation[i], SIGNAL(phase(QVector<double>)), this, SLOT(getNoise(QVector<double>)));
        }
    }
    for (int i=0;i<2;i++)
    {
        threads[i]->start();
    }
}

void MainWindow::getEnergy(QVector<double> energies)
{
    Energies.append(energies);
}

void MainWindow::getPulse(QVector<double> pulse_spectrum)
{
    Pulse_spectrum += pulse_spectrum;
}

void MainWindow::getNoise(QVector<double> noise_spectrum)
{
    Noise_spectrum += noise_spectrum;
}

void MainWindow::getPhase(QVector<double> pulse_phase)
{
    Pulse_phase = pulse_phase;
}

void MainWindow::setmode1()
{
    //instrument.setMode(1);
    QMessageBox::information(this, "Mode", "Calibration mode selected");
}

void MainWindow::setmode2()
{
    //instrument.setMode(2);
    QMessageBox::information(this, "Mode", "Resolution estimation mode selected");
}

void MainWindow::openConfig()
{
    config *conf = new config();
    conf->show();
}

void MainWindow::Export()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Save a file", QString(),"XML (*.xml)");
    Importation::saveConfig(fichier);
}

void MainWindow::computeHist(QVector<double> &hist, QVector<double> data, int Nbin, double binW, double MidBin)
{
    for (int i=0;i<(int)hist.size();i++)
    {
        hist[i]=0;
    }
    double h;
    for (int i=0;i<(int)data.size();i++)
    {
        h=data[i]-MidBin+Nbin/2*binW;

        if (h>0)
        {
            hist[(int)std::round(h/binW)]+=1;
        }
    }
}
