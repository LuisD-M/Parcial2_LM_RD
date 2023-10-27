#include "jugador.h"

jugador::jugador()
{
}

jugador::jugador(const string& nombre, char idd)
{
    this->nombre=nombre;
    this->idd = idd;
}

char jugador::getidd() const
{
    return idd;
}

string jugador::getnombre() const
{
    return nombre;
}
