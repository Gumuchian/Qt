#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qstring>
#include "xifu.h"
#include "config.h"
#include <QThread>
#include "qcustomplot.h"
#include <math.h>
#include <fstream>

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
    delete ui;
}

void MainWindow::displayresult()
{
    std::vector<double> E = instrument.getE();
    if (E.size()!=0)
    {
        E.erase(E.begin(),E.begin()+2);
        double Em=0,max=0,Emax=0,Emin=energy,var=0;
        int Nbin;
        for (int i=0;i<(int)E.size();i++)
        {
            Em+=E[i];
            if (Emax<E[i])
            {
                Emax=E[i];
            }
            if (Emin>E[i])
            {
                Emin=E[i];
            }
        }
        Em/=((int)E.size());
        for (int i=0;i<(int)E.size();i++)
        {
            var+=pow(E[i]-Em,2);
        }
        var/=(int)E.size();
        var=std::sqrt(var);
        Nbin=(int)std::ceil((Emax-Emin)/binWidth);
        QVector<double> Data(Nbin);
        computeHist(Data, E, Nbin, binWidth, Em);
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
        gradient.setColorAt(0, QColor(90, 90, 90));
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
            labels[i]=QString::number(Emin+i*binWidth);
        }

        QVector<double> gaussian(Nbin);
        for (int i=0;i<(int)gaussian.size();i++)
        {
            gaussian[i]=100/(std::sqrt(2*PI)*var)*std::exp(-pow(Emin+i*binWidth-Em,2)/(2*pow(var,2)));
        }

        QCPGraph *fit = customPlot->addGraph();
        fit->setData(ticks, gaussian);
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
        customPlot->xAxis->setBasePen(QPen(Qt::white));
        customPlot->xAxis->setTickPen(QPen(Qt::white));
        customPlot->xAxis->grid()->setVisible(true);
        customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        customPlot->xAxis->setTickLabelColor(Qt::white);
        customPlot->xAxis->setLabelColor(Qt::white);


        // prepare y axis:
        customPlot->yAxis->setRange(0,max);
        customPlot->yAxis->setPadding(5); // a bit more space to the left border
        customPlot->yAxis->setLabel("Percentage of Particules");
        customPlot->yAxis->setBasePen(QPen(Qt::white));
        customPlot->yAxis->setTickPen(QPen(Qt::white));
        customPlot->yAxis->setSubTickPen(QPen(Qt::white));
        customPlot->yAxis->grid()->setSubGridVisible(true);
        customPlot->yAxis->setTickLabelColor(Qt::white);
        customPlot->yAxis->setLabelColor(Qt::white);
        customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        // Add data:
        energy_distrib->setData(ticks, Data);

        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        customPlot->replot();
        customPlot->show();

        QCustomPlot  *customPlotspec = new QCustomPlot;
        customPlotspec->setMinimumSize(750,900);
        customPlotspec->setWindowTitle("OF Transfer function");
        customPlotspec->addGraph();
        customPlotspec->graph(0)->setPen(QPen(Qt::blue));
        customPlotspec->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
        QVector<double> x(Npat/2), y(Npat/2);
        for (int i=0; i<Npat/2; ++i)
        {
          x[i] = i*fs/(decimation*Npat);
        }
        y = instrument.getSpectrum();
        customPlotspec->xAxis->setLabel("Hz");
        customPlotspec->yAxis->setLabel("dB");
        customPlotspec->graph(0)->setData(x, y);
        customPlotspec->graph(0)->rescaleAxes();
        customPlotspec->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        customPlotspec->show();
    }

    QWidget *window = new QWidget();
    QLabel *label = new QLabel(instrument.getResults(), window);
    label->show();
    window->setWindowTitle("Results");
    window->setFixedSize(350,100);
    window->show();
}

void MainWindow::simulate()
{
    QThread *thread = new QThread();
    instrument.moveToThread(QApplication::instance()->thread());
    connect(thread, SIGNAL(finished()), &instrument, SLOT(deleteLater()));
    connect(thread, SIGNAL(started()), &instrument, SLOT(simulate()));
    progress = new QProgressBar;
    progress->setWindowTitle("Progression");
    progress->setFixedSize(400,50);
    progress->show();
    connect(&instrument, SIGNAL(getProgress(int)),progress, SLOT(setValue(int)));
    connect(&instrument, SIGNAL(simulation_ended()), progress, SLOT(close()));
    thread->start();
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

void MainWindow::computeHist(QVector<double> &hist, std::vector<double> data, int Nbin, double binW, double MidBin)
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
    for (int i=0;i<(int)hist.size();i++)
    {
        hist[i]*=100.0/(int)data.size();
    }
}
