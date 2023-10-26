#ifndef FICHA_H
#define FICHA_H
#include <QObject>

class ficha
{
private:
    char idd;                         //identificador de las fichas (*) (-)

public:
    ficha(char idd);                       //constructor
    char getidd() const;                   //Obtener idd
    void setidd(char idd);                 //asignar idd
};

#endif // FICHA_H
