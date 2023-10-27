#ifndef TABLERO_H
#define TABLERO_H
#include <QObject>

#include "ficha.h"
#include "jugador.h"

const short int filas=8;
const short int columnas=8;

class tablero
{
private:
    ficha* casillas[filas][columnas];

public:
    tablero();                             //constructor
    ~tablero();                            //destructor
    void initablero(const jugador& jugador1, const jugador& jugador2);                   //iniciar el tablero con los jugadores
    void impritablero() const;             //imprimir tablero

};

#endif // TABLERO_H
