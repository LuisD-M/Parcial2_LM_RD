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
    tablero(const jugador &jugador1, const jugador &jugador2);
    ~tablero();                            //destructor
    void initablero();                   //iniciar el tablero con los jugadores
    void impritablero() const;             //imprimir tablero
    bool volteacasillas(short posfila, short poscolumna, unsigned short numerojugador, bool mode = false);
    bool casillasjugables(unsigned short jugador);
    void limpiarcasillas();
    void EscArchivo();
    bool casillavalida(unsigned short posfila, unsigned short poscolumna);
    void setCasillas(ficha* casillas[filas][columnas]);
    void getCasillas(ficha* casillas[filas][columnas]);
};

#endif // TABLERO_H
