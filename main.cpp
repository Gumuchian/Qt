#include "mainwindow.h"
#include <QApplication>
#include "importation.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Importation::setGlobal();
    app.setWindowIcon(QIcon(":/images/icon.jpg"));
    MainWindow w;
    w.show();
    return app.exec();
}
