#ifndef TRUNCATION_H
#define TRUNCATION_H

#include <QDialog>

namespace Ui {
class Truncation;
}

class Truncation : public QDialog
{
    Q_OBJECT

public:
    explicit Truncation(QWidget *parent = 0);
    ~Truncation();

private:
    Ui::Truncation *ui;
};

#endif // TRUNCATION_H
