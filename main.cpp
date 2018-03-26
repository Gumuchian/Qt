#include "mainwindow.h"
#include <QApplication>
#include "global.h"
#include <iostream>
#include "importation.h"

int main(int argc, char *argv[])
{

    Importation::setGlobal();
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/icon.jpg"));
    MainWindow w;
    w.show();
    return app.exec();
}
