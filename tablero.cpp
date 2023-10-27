#include "tablero.h"

#include <iostream>
using namespace std;

tablero::tablero()
{
    for(unsigned short int i=0; i<filas; i++){
        for(unsigned short int j=0; j<columnas; j++)
            casillas[i][j] = nullptr;                             //puntero nulo para casillas vacias
    }
}

tablero::tablero(const jugador &jugador1, const jugador &jugador2)
{
    for(unsigned short int i=0; i<filas; i++){
        for(unsigned short int j=0; j<columnas; j++)
            casillas[i][j] = nullptr;                             //puntero nulo para casillas vacias
    }
    this->jugador1 = jugador1;
    this->jugador2 = jugador2;
}

tablero::~tablero()
{
    for(unsigned short int i=0; i<filas; i++){
        for(unsigned short int j=0; j<columnas; j++)
            delete casillas[i][j];                             //libera memoria
    }
}

void tablero::initablero()
{
    for(unsigned short int i=0; i<filas; i++){
        for(unsigned short int j=0; j<columnas; j++)
            casillas[i][j] = new ficha(' ');                   //Crean las 64 fichas con espacio vacio                             //puntero nulo para casillas vacias
    }

    casillas[3][3]->setidd(jugador1.getidd());                              //asignan las 4 fichas iniciales
    casillas[4][4]->setidd(jugador1.getidd());
    casillas[3][4]->setidd(jugador2.getidd());
    casillas[4][3]->setidd(jugador2.getidd());
}

void tablero::impritablero() const
{
    cout<<"Tablero de juego."<<endl<<endl<<"   ";
    for(unsigned short int i=0; i<filas;i++) cout<<" "<<char(i+65)<<"  ";

    cout<<endl<<"   _______________________________"<<endl;

    for(unsigned short int i=0; i<filas; i++){
        cout<<i<<" |";

        for(unsigned short int j=0; j<columnas; j++)
            cout<<" "<<casillas[i][j]->getidd()<<" |";                   //Crean las 64 fichas con espacio vacio                             //puntero nulo para casillas vacias

        cout<<endl<<"   -------------------------------"<<endl;
    }
}

bool tablero::movimientovalido(unsigned short int posfila, unsigned short int poscolumna) const
{
    char idenemigo;
    char idpropio;
    bool enemiga = false;
    bool encierro = false;
    // encierro de fila
    for (int i = 0; i <= columnas; i++)
    {
        casillas[posfila][i]->getidd();
    }

}
