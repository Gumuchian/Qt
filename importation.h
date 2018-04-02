#ifndef IMPORTATION_H
#define IMPORTATION_H
#include <QString>

class Importation
{
public:
    Importation();
    static void setGlobal(QString path);
    static void saveConfig(QString path);
};

#endif // IMPORTATION_H
