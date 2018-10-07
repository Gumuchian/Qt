#include "truncation.h"
#include "ui_truncation.h"

Truncation::Truncation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Truncation)
{
    ui->setupUi(this);
}

Truncation::~Truncation()
{
    delete ui;
}
