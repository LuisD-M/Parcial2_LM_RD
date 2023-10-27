#ifndef JUGADOR_H
#define JUGADOR_H
#include <iostream>
#include <string>
#include <QObject>

using namespace std;

class jugador
{
private:
    char idd;                                  //idd de la ficha
    string nombre;                             //nombre del jugador

public:
    jugador();
    jugador(const string& nombre, char idd);
    char getidd() const;
    string getnombre() const;

};

#endif // JUGADOR_H
