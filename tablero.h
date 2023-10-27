#ifndef TABLERO_H
#define TABLERO_H
#include <QObject>

#include "ficha.h"
#include "jugador.h"

const unsigned short int filas=8;
const unsigned short int columnas=8;

class tablero
{
private:

    ficha* casillas[filas][columnas];
    jugador jugador1;
    jugador jugador2;

public:
    tablero();                             //constructor
    tablero(const jugador &jugador1, const jugador &jugador2);
    ~tablero();                            //destructor
    void initablero();                   //iniciar el tablero con los jugadores
    void impritablero() const;             //imprimir tablero
    bool movimientovalido(unsigned short int posfila, unsigned short int poscolumna) const;
};

#endif // TABLERO_H
