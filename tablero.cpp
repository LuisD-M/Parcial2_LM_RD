#include "tablero.h"
#include <QDateTime>
#include <iostream>
#include <QDebug>
#include <fstream>
#include <sstream>
#include <string>



using namespace std;

string int2str(unsigned short int a);

// construye cada casilla del tablero y guarda los jugadores
tablero::tablero(const jugador &jugador1, const jugador &jugador2)
{
    for(unsigned short int i=0; i<filas; i++){
        for(unsigned short int j=0; j<columnas; j++)
            casillas[i][j] = nullptr;                             //puntero nulo para casillas vacias
    }
    this->jugador1 = jugador1;
    this->jugador2 = jugador2;
}

// destruye la memoria dinamica usada para las las fichas
tablero::~tablero()
{
    for(unsigned short int i=0; i<filas; i++){
        for(unsigned short int j=0; j<columnas; j++)
            delete casillas[i][j];                             //libera memoria
    }
}

// inicializa el tablero con casillas vacias excepto las 4 casillas iniciales
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

// despliega en consola el tablero
void tablero::impritablero() const
{
    cout<<endl<<"Tablero de juego."<<endl<<endl<<"   ";
    for(unsigned short int i=0; i<filas;i++) cout<<" "<<char(i+65)<<"  ";

    cout<<endl<<"   _______________________________"<<endl;

    for(unsigned short int i=0; i<filas; i++){
        cout<<i<<" |";

        for(unsigned short int j=0; j<columnas; j++)
            cout<<" "<<casillas[i][j]->getidd()<<" |";                   //Crean las 64 fichas con espacio vacio                             //puntero nulo para casillas vacias

        cout<<endl<<"   -------------------------------"<<endl;
    }
}

// mode true: se encarga de verificar si existen encierros (un sandwich)
// mode false: encuentra los lugares donde ocurre un encierro y voltea las fichas
bool tablero::volteacasillas(short posfila, short poscolumna, unsigned short numerojugador, bool mode)
{
    unsigned short pos[8][2]; // matriz que guarda las posiciones de los encierros
    for (int i = 0; i < 8; i++) for (int j = 0; j < 2; j++) pos[i][j] = filas*columnas;
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
    // verifica/obtiene las posiciones de los encierros
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
    for (int i = poscolumna+1; i < filas-1; i++)
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
    for (int i = posfila+1; i < filas-1; i++)
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
    while(-1 - i + poscolumna >= 0 && 1 + i + posfila <= filas-1)
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
    while(1 + i + poscolumna <= columnas-1 && -1 - i + posfila >= 0)
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
    // encierro de diagonal derecha abajo
    i = 1;
    while(1 + i + poscolumna <= columnas-1 && 1 + i + posfila <= filas-1)
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
    // voltea las fichas donde hay encierros
    // fila izquierda
    for (int i = pos[0][1]+1; i <= poscolumna; i++)
    {
        if (pos[0][1] == filas*columnas) break;
        delete casillas[posfila][i];
        casillas[posfila][i] = new ficha(idpropio);
    }
    // fila derecha
    for (int i = poscolumna; i < pos[1][1]; i++)
    {
        if (pos[1][1] == filas*columnas) break;
        delete casillas[posfila][i];
        casillas[posfila][i] = new ficha(idpropio);
    }
    // columna arriba
    for (int i = pos[2][0]+1; i <= posfila; i++)
    {
        if (pos[2][0] == filas*columnas) break;
        delete casillas[i][poscolumna];
        casillas[i][poscolumna] = new ficha(idpropio);
    }
    // columna abajo
    for (int i = posfila; i < pos[3][0]; i++)
    {
        if (pos[3][0] == filas*columnas) break;
        delete casillas[i][poscolumna];
        casillas[i][poscolumna] = new ficha(idpropio);
    }
    // diagonal izquierda arriba
    for (int i = 0; poscolumna-i > pos[4][1]; i++)
    {
        if (pos[4][1] == filas*columnas) break;
        delete casillas[posfila-i][poscolumna-i];
        casillas[posfila-i][poscolumna-i] = new ficha(idpropio);
    }
    // diagonal izquierda abajo
    for (int i = 0; poscolumna-i > pos[5][1]; i++)
    {
        if (pos[5][1] == filas*columnas) break;
        delete casillas[posfila+i][poscolumna-i];
        casillas[posfila+i][poscolumna-i] = new ficha(idpropio);
    }
    // diagonal derecha arriba
    for (int i = 0; poscolumna+i < pos[6][1]; i++)
    {
        if (pos[6][1] == filas*columnas) break;
        delete casillas[posfila-i][poscolumna+i];
        casillas[posfila-i][poscolumna+i] = new ficha(idpropio);
    }
    // diagonal derecha abajo
    for (int i = 0; poscolumna+i < pos[7][1]; i++)
    {
        if (pos[7][1] == filas*columnas) break;
        delete casillas[posfila+i][poscolumna+i];
        casillas[posfila+i][poscolumna+i] = new ficha(idpropio);
    }
    return true;
}

// ingresa en la matriz las casillas jugables por el jugador de turno
bool tablero::casillasjugables(unsigned short jugador)
{
    bool jugable = false;
    for (int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
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

// eliminar las 'O' que fueron colocadas en las casillas jugables
void tablero::limpiarcasillas()
{
    for (int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            if (casillas[i][j]->getidd() == 'O')
            {
                casillas[i][j]->setidd(' ');
            }
        }
    }
}

// guarda en el archivo la informacion de la partida
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

    try{

        ofstream in("HistorialPartidas.txt",ios::app);

        if (in.is_open()){
            in<<lineaTexto<<endl;
            in.close();
        }
        else
            throw '5';
    }
    catch (char c){
        if(c==5)
            cout<<"Error con el archivo de escritura"<<endl<<endl;
        else
            cout<<"Error inesperado"<<endl<<endl;
    }
}

// verifica si el movimiento se hizo en una casilla valida
bool tablero::casillavalida( int posfila, int poscolumna)
{
    return casillas[posfila][poscolumna]->getidd() == 'O';
}

// setter para casillas
void tablero::setCasillas(ficha* casillas[filas][columnas])
{
    for (int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            this->casillas[i][j] = casillas[i][j];
        }
    }
}

// getter para casillas
void tablero::getCasillas(ficha* casillas[filas][columnas])
{
    for (int i = 0; i < filas; i++)
    {
        for(int j = 0; j < columnas; j++)
        {
            casillas[i][j] = this->casillas[i][j];
        }
    }
}

// cuenta la cantidad total de fichas de los jugadores en el tablero
int tablero::totalfichas()
{
    unsigned short int cont=0;
    for(unsigned short int i=0; i<filas; i++){
        for(unsigned short int j=0; j<columnas; j++){
            if(casillas[i][j]->getidd() != ' ')
                cont++;
        }
    }

    return cont;
}

// cuenta las fichas de cada jugador y dice quien gano
void tablero::win()
{
    unsigned short int c1=0, c2=0;
    for(unsigned short int i=0; i<filas; i++){
        for(unsigned short int j=0; j<columnas; j++){
            if(casillas[i][j]->getidd() == jugador1.getidd())
                c1++;

            else if(casillas[i][j]->getidd() == jugador2.getidd())
                c2++;
        }
    }

    cout<<"Puntaje de "<<jugador1.getnombre()<<": "<<c1<<endl;
    cout<<"Puntaje de "<<jugador2.getnombre()<<": "<<c2<<endl;

    if(c1>c2) cout<<"El ganador es: "<<jugador1.getnombre()<<endl;

    else if(c2>c1) cout<<"El ganador es: "<<jugador2.getnombre()<<endl;

    else cout<<"La partida quedo empatada."<<endl;

    cout<<"Partida finalizada."<<endl<<endl;;


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

