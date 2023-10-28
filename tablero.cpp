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

bool tablero::volteacasillas(short posfila, short poscolumna, unsigned short numerojugador, bool mode)
{
    unsigned short pos[filas][2];
    for (int i = 0; i < filas; i++) for (int j = 0; j < 2; j++) pos[i][j] = 9;
    char idenemigo;
    char idpropio;
    if (numerojugador == 1)
    {
        idpropio = jugador1.getidd();
        idenemigo = jugador2.getidd();
    }else
    {
        idpropio = jugador2.getidd();
        idenemigo = jugador1.getidd();
    }

    // encierro de fila izquierda
    for (int i = poscolumna-1; i >= 1; i--)
    {
        if ((casillas[posfila][i]->getidd() == idenemigo) && (casillas[posfila][i-1]->getidd() == idenemigo || casillas[posfila][i-1]->getidd() == idpropio))
        {
            if((casillas[posfila][i]->getidd() == idenemigo) && (casillas[posfila][i-1]->getidd() == idpropio))
            {
                if (mode) return true;
                pos[0][0] = posfila;
                pos[0][1] = i-1;
                break;
            }
        }else
        {
            break;
        }
    }
    // encierro de fila derecha
    for (int i = poscolumna+1; i <= filas-1; i++)
    {
        if ((casillas[posfila][i]->getidd() == idenemigo) && (casillas[posfila][i+1]->getidd() == idenemigo || casillas[posfila][i+1]->getidd() == idpropio))
        {
            if((casillas[posfila][i]->getidd() == idenemigo) && (casillas[posfila][i+1]->getidd() == idpropio))
            {
                if (mode) return true;
                pos[1][0] = posfila;
                pos[1][1] = i+1;
                break;
            }
        }else
        {
            break;
        }
    }

    // encierro de columna arriba
    for (int i = posfila-1; i >= 1; i--)
    {
        if ((casillas[i][poscolumna]->getidd() == idenemigo) && (casillas[i-1][poscolumna]->getidd() == idenemigo || casillas[i-1][poscolumna]->getidd() == idpropio))
        {
            if((casillas[i][poscolumna]->getidd() == idenemigo) && (casillas[i-1][poscolumna]->getidd() == idpropio))
            {
                if (mode) return true;
                pos[2][0] = i-1;
                pos[2][1] = poscolumna;
                break;
            }
        }else
        {
            break;
        }
    }
    // encierro de columna abajo
    for (int i = posfila+1; i <= filas-1; i++)
    {
        if ((casillas[i][poscolumna]->getidd() == idenemigo) && (casillas[i+1][poscolumna]->getidd() == idenemigo || casillas[i+1][poscolumna]->getidd() == idpropio))
        {
            if((casillas[i][poscolumna]->getidd() == idenemigo) && (casillas[i+1][poscolumna]->getidd() == idpropio))
            {
                if (mode) return true;
                pos[3][0] = i+1;
                pos[3][1] = poscolumna;
                break;
            }
        }else
        {
            break;
        }
    }

    // encierro de diagonal izquierda arriba
    int i = 1;
    while(-1 - i + poscolumna >= 0 && -1 - i + posfila >= 0)
    {
        if ((casillas[posfila-i][poscolumna-i]->getidd() == idenemigo) && (casillas[posfila-i-1][poscolumna-i-1]->getidd() == idenemigo || casillas[posfila-i-1][poscolumna-i-1]->getidd() == idpropio))
        {
            if((casillas[posfila-i][poscolumna-i]->getidd() == idenemigo) && (casillas[posfila-i-1][poscolumna-i-1]->getidd() == idpropio))
            {
                if (mode) return true;
                pos[4][0] = posfila-i-1;
                pos[4][1] = poscolumna-i-1;
                break;
            }
        }else
        {
            break;
        }
        i++;
    }
    // encierro de diagonal izquierda abajo
    i = 1;
    while(-1 - i + poscolumna >= 0 && 1 + i + posfila <= 7)
    {
        if ((casillas[posfila+i][poscolumna-i]->getidd() == idenemigo) && (casillas[posfila+i+1][poscolumna-i-1]->getidd() == idenemigo || casillas[posfila+i+1][poscolumna-i-1]->getidd() == idpropio))
        {
            if((casillas[posfila+i][poscolumna-i]->getidd() == idenemigo) && (casillas[posfila+i+1][poscolumna-i-1]->getidd() == idpropio))
            {
                if (mode) return true;
                pos[5][0] = posfila+i+1;
                pos[5][1] = poscolumna-i-1;
                break;
            }
        }else
        {
            break;
        }
        i++;
    }

    // encierro de diagonal derecha arriba
    i = 1;
    while(1 + i + poscolumna <= 7 && -1 - i + posfila >= 0)
    {
        if ((casillas[posfila-i][poscolumna+i]->getidd() == idenemigo) && (casillas[posfila-i-1][poscolumna+i+1]->getidd() == idenemigo || casillas[posfila-i-1][poscolumna+i+1]->getidd() == idpropio))
        {
            if((casillas[posfila-i][poscolumna+i]->getidd() == idenemigo) && (casillas[posfila-i-1][poscolumna+i+1]->getidd() == idpropio))
            {
                if (mode) return true;
                pos[6][0] = posfila-i-1;
                pos[6][1] = poscolumna+i+1;
                break;
            }
        }else
        {
            break;
        }
        i++;
    }
    // encierro de diagonal izquierda abajo
    i = 1;
    while(1 + i + poscolumna <= 7 && 1 + i + posfila <= 7)
    {
        if ((casillas[posfila+i][poscolumna+i]->getidd() == idenemigo) && (casillas[posfila+i+1][poscolumna+i+1]->getidd() == idenemigo || casillas[posfila+i+1][poscolumna+i+1]->getidd() == idpropio))
        {
            if((casillas[posfila+i][poscolumna+i]->getidd() == idenemigo) && (casillas[posfila+i+1][poscolumna+i+1]->getidd() == idpropio))
            {
                if (mode) return true;
                pos[7][0] = posfila+i+1;
                pos[7][1] = poscolumna+i+1;
                break;
            }
        }else
        {
            break;
        }
        i++;
    }
    if (mode) return false;
    // fila
    for (int i = pos[0][1]+1; i <= poscolumna; i++)
    {
        if (pos[0][1] == 9) break;
        delete casillas[posfila][i];
        casillas[posfila][i] = new ficha(idpropio);
    }
    for (int i = poscolumna; i < pos[1][1]; i++)
    {
        if (pos[1][1] == 9) break;
        delete casillas[posfila][i];
        casillas[posfila][i] = new ficha(idpropio);
    }
    // columna
    for (int i = pos[2][0]+1; i <= posfila; i++)
    {
        if (pos[2][0] == 9) break;
        delete casillas[i][poscolumna];
        casillas[i][poscolumna] = new ficha(idpropio);
    }
    for (int i = posfila; i < pos[3][0]; i++)
    {
        if (pos[3][0] == 9) break;
        delete casillas[i][poscolumna];
        casillas[i][poscolumna] = new ficha(idpropio);
    }
    // diagonal izquierda
    for (int i = 0; poscolumna-i > pos[4][1]; i++)
    {
        if (pos[4][1] == 9) break;
        delete casillas[posfila-i][poscolumna-i];
        casillas[posfila-i][poscolumna-i] = new ficha(idpropio);
    }
    for (int i = 0; poscolumna-i > pos[5][1]; i++)
    {
        if (pos[5][1] == 9) break;
        delete casillas[posfila+i][poscolumna-i];
        casillas[posfila+i][poscolumna-i] = new ficha(idpropio);
    }
    // diagonal derecha
    for (int i = 0; poscolumna+i < pos[6][1]; i++)
    {
        if (pos[6][1] == 9) break;
        delete casillas[posfila-i][poscolumna+i];
        casillas[posfila-i][poscolumna+i] = new ficha(idpropio);
    }
    for (int i = 0; poscolumna+i < pos[7][1]; i++)
    {
        if (pos[7][1] == 9) break;
        delete casillas[posfila+1][poscolumna+i];
        casillas[posfila+1][poscolumna+i] = new ficha(idpropio);
    }
    return true;
//    for (int i = 0; i < 8; i++){
//        for (int j = 0; j < 2; j++)
//        {
//            cout << pos[i][j] << ',';
//        }
//        cout << endl;
//    }
//    cout << endl;
}

bool tablero::casillasjugables(unsigned short jugador)
{
    bool jugable = false;
    for (int i = 0; i < filas; i++)
    {
        for(int j = 0; j < filas; j++)
        {
            if (casillas[i][j]->getidd() == ' ')
            {
                if (volteacasillas(i,j,jugador,true))
                {
                    casillas[i][j]->setidd('O');
                    jugable = true;
                }
            }
        }
    }
    return jugable;
}

void tablero::limpiarcasillas()
{
    for (int i = 0; i < filas; i++)
    {
        for(int j = 0; j < filas; j++)
        {
            if (casillas[i][j]->getidd() == 'O')
            {
                casillas[i][j]->setidd(' ');
            }
        }
    }
}
