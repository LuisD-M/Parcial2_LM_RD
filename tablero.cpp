#include "tablero.h"
#include <QDateTime>
#include <iostream>
#include <QDebug>
#include <fstream>
#include <sstream>
#include <string>



using namespace std;

string int2str(unsigned short int a);

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

void tablero::EscArchivo()
{
    int cont1=0, cont2=0;
    string lineaTexto, co1, co2, fechaYHora;

    for(unsigned short int i=0; i<filas; i++){
        for(unsigned short int j=0; j<columnas; j++){
            if(casillas[i][j]->getidd() == jugador1.getidd())
                cont1++;

            else if(casillas[i][j]->getidd() == jugador2.getidd())
                cont2++;
        }
    }

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString dateTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");


    fechaYHora = dateTimeString.toStdString();

    co1 = int2str(cont1);
    co2 = int2str(cont2);

    lineaTexto = jugador1.getnombre() + "," + co1 + "," + jugador2.getnombre() + "," + co2 + "," + fechaYHora;

    ofstream in("HistorialPartidas.txt",ios::app);

    if (in.is_open()){
        in<<lineaTexto<<endl;
        in.close();
    }
    else
        cout<<"El archivo de hitorial no ce pudo abrir."<<endl;
}

string int2str(unsigned short int a){
    int c=0,i=1;
    char e;
    string b;
    for(;(a/i);i=i*10)
        c++;
    for(int j=0;j<c;j++){
        i/=10;
        e=(a/i)+48;
        b.push_back(e);
        a-=(a/i)*i;
    }
    return b;
}
