#include "truncation.h"
#include "ui_truncation.h"
#include "global.h"

Truncation::Truncation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Truncation)
{
    ui->setupUi(this);
    setFixedSize(750,150);
    connect(ui->pushButton, SIGNAL(clicked()), this , SLOT(setValue()));
    connect(ui->pushButton, SIGNAL(clicked()), this , SLOT(close()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this , SLOT(close()));

    ui->spinBox->setValue(ND);
    ui->spinBox_2->setValue(NI);
    ui->spinBox_3->setValue(NR);
}

Truncation::~Truncation()
{
    delete ui;
}

void Truncation::setValue()
{
    ND=ui->spinBox->value();
    NI=ui->spinBox_2->value();
    NR=ui->spinBox_3->value();
}
