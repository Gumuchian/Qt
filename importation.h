#ifndef IMPORTATION_H
#define IMPORTATION_H
#include <QString>

class Importation
{
public:
    Importation();
    ~Importation();
    static void setGlobal(QString path);
    static void saveConfig(QString path);
    static void setInitial();
};

#endif // IMPORTATION_H
