#ifndef TABLERO_H
#define TABLERO_H
#include <QObject>

#include "ficha.h"

const short int filas=8;
const short int columnas=8;

class tablero
{
private:
    ficha* casillas[filas][columnas];

public:
    tablero();                             //constructor
    ~tablero();                            //destructor
    void initablero();                     //iniciar el tablero
    void impritablero() const;             //imprimir tablero

};

#endif // TABLERO_H
