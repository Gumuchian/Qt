#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Qstring>
#include "xifu.h"
#include "config.h"
#include <QThread>
#include "qcustomplot.h"

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
    //thread->terminate();
    //thread->wait();
    delete ui;
}

void MainWindow::displayresult()
{
    QCustomPlot  *customPlot = new QCustomPlot;
    //customPlot->setFixedSize(500,300);
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
    QVector<double> ticks;
    QVector<QString> labels;
    for (int i=0;i<100;i++)
    {
        ticks.push_back(i);
        labels.push_back(QString::number(i));
    }
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(60);
    customPlot->xAxis->setSubTicks(false);
    customPlot->xAxis->setTickLength(0, 4);
    customPlot->xAxis->setRange(0, 100);
    customPlot->xAxis->setBasePen(QPen(Qt::white));
    customPlot->xAxis->setTickPen(QPen(Qt::white));
    customPlot->xAxis->grid()->setVisible(true);
    customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    customPlot->xAxis->setTickLabelColor(Qt::white);
    customPlot->xAxis->setLabelColor(Qt::white);

    // Add data:
    std::vector<double> E = instrument.getE();
    E.erase(E.begin(),E.begin()+2);
    double Em=0,max=0;
    for (int i=0;i<(int)E.size();i++)
    {
        Em+=E[i];
    }
    Em/=((int)E.size());
    QVector<double> Data(100);
    energy_distrib->setData(ticks, computeHist(Data, E, (int)Data.size(), binWidth, Em));

    for (int i=0;i<Data.size();i++)
    {
        if (max<Data[i])
        {
            max=Data[i];
        }
    }

    // prepare y axis:
    customPlot->yAxis->setRange(0,max);
    customPlot->yAxis->setPadding(5); // a bit more space to the left border
    customPlot->yAxis->setLabel("Number of Particules");
    customPlot->yAxis->setBasePen(QPen(Qt::white));
    customPlot->yAxis->setTickPen(QPen(Qt::white));
    customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    customPlot->yAxis->grid()->setSubGridVisible(true);
    customPlot->yAxis->setTickLabelColor(Qt::white);
    customPlot->yAxis->setLabelColor(Qt::white);
    customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->replot();
    customPlot->show();

    QMessageBox::information(this, "Results", instrument.getResults());
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

QVector<double> MainWindow::computeHist(QVector<double> hist, std::vector<double> data, int Nbin, double binW, double MidBin)
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
            hist[(int)std::floor(h/binW)]+=1;
        }
    }
    for (int i=0;i<(int)hist.size();i++)
    {
        hist[i]=hist[i]*100/(int)data.size();
    }
    return hist;
}
