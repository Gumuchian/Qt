#include "mainwindow.h"
#include <QApplication>
#include "importation.h"
#include <QString>

int main(int argc, char *argv[])
{
    saveItes=false;
    saveError=false;
    saveIQ=false;
    saveFeedback=false;
    QApplication app(argc, argv);
    QString str="C://Users/Paul/Documents/build-X-IFU_simulator-Desktop_Qt_5_8_0_MinGW_32bit-Release/global.xml";
    Importation::setGlobal(str);
    app.setWindowIcon(QIcon(":/images/icon.jpg"));
    MainWindow w;
    w.show();
    return app.exec();
}
