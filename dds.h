#ifndef DDS_H
#define DDS_H

class DDS
{
    public:
        DDS();
        virtual ~DDS();
        DDS(int taille, int precision, int interp);
        int getvalue(int indice);
    protected:

    private:
        int taille;
        int precision;
        int interp;
        int *table;
};

#endif // DDS_H
