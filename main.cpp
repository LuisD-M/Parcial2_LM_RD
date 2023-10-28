#include <QCoreApplication>
#include "jugador.h"
#include "tablero.h"
#include "ficha.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


int menu();
void leerHistorial();


int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

//    jugador jugador1("Raul", '*');
//    jugador jugador2("Pepe", '-');
//    tablero tablero1(jugador1, jugador2);
//    tablero1.initablero();
//    ficha *casillas[filas][columnas];
//    tablero1.getCasillas(casillas);
//    casillas[0]['A'-'A'] = new ficha('*');
//    casillas[0]['B'-'A'] = new ficha('-');
//    casillas[0]['C'-'A'] = new ficha(' ');
//    casillas[0]['D'-'A'] = new ficha('*');
//    casillas[0]['E'-'A'] = new ficha('*');
//    casillas[0]['F'-'A'] = new ficha('*');
//    casillas[0]['G'-'A'] = new ficha('*');
//    casillas[0]['H'-'A'] = new ficha('*');

//    casillas[1]['A'-'A'] = new ficha('-');
//    casillas[1]['B'-'A'] = new ficha('*');
//    casillas[1]['C'-'A'] = new ficha(' ');
//    casillas[1]['D'-'A'] = new ficha(' ');
//    casillas[1]['E'-'A'] = new ficha('-');
//    casillas[1]['F'-'A'] = new ficha(' ');
//    casillas[1]['G'-'A'] = new ficha('*');
//    casillas[1]['H'-'A'] = new ficha(' ');

//    casillas[2]['A'-'A'] = new ficha(' ');
//    casillas[2]['B'-'A'] = new ficha('-');
//    casillas[2]['C'-'A'] = new ficha('*');
//    casillas[2]['D'-'A'] = new ficha(' ');
//    casillas[2]['E'-'A'] = new ficha('-');
//    casillas[2]['F'-'A'] = new ficha('*');
//    casillas[2]['G'-'A'] = new ficha('-');
//    casillas[2]['H'-'A'] = new ficha('-');

//    casillas[3]['A'-'A'] = new ficha(' ');
//    casillas[3]['B'-'A'] = new ficha(' ');
//    casillas[3]['C'-'A'] = new ficha('-');
//    casillas[3]['D'-'A'] = new ficha('*');
//    casillas[3]['E'-'A'] = new ficha('*');
//    casillas[3]['F'-'A'] = new ficha(' ');
//    casillas[3]['G'-'A'] = new ficha(' ');
//    casillas[3]['H'-'A'] = new ficha(' ');

//    casillas[4]['A'-'A'] = new ficha(' ');
//    casillas[4]['B'-'A'] = new ficha(' ');
//    casillas[4]['C'-'A'] = new ficha('-');
//    casillas[4]['D'-'A'] = new ficha('*');
//    casillas[4]['E'-'A'] = new ficha('*');
//    casillas[4]['F'-'A'] = new ficha(' ');
//    casillas[4]['G'-'A'] = new ficha(' ');
//    casillas[4]['H'-'A'] = new ficha(' ');

//    casillas[5]['A'-'A'] = new ficha(' ');
//    casillas[5]['B'-'A'] = new ficha(' ');
//    casillas[5]['C'-'A'] = new ficha('*');
//    casillas[5]['D'-'A'] = new ficha('-');
//    casillas[5]['E'-'A'] = new ficha(' ');
//    casillas[5]['F'-'A'] = new ficha(' ');
//    casillas[5]['G'-'A'] = new ficha(' ');
//    casillas[5]['H'-'A'] = new ficha(' ');

//    casillas[6]['A'-'A'] = new ficha(' ');
//    casillas[6]['B'-'A'] = new ficha('*');
//    casillas[6]['C'-'A'] = new ficha(' ');
//    casillas[6]['D'-'A'] = new ficha(' ');
//    casillas[6]['E'-'A'] = new ficha('-');
//    casillas[6]['F'-'A'] = new ficha(' ');
//    casillas[6]['G'-'A'] = new ficha(' ');
//    casillas[6]['H'-'A'] = new ficha(' ');

//    casillas[7]['A'-'A'] = new ficha(' ');
//    casillas[7]['B'-'A'] = new ficha(' ');
//    casillas[7]['C'-'A'] = new ficha(' ');
//    casillas[7]['D'-'A'] = new ficha(' ');
//    casillas[7]['E'-'A'] = new ficha(' ');
//    casillas[7]['F'-'A'] = new ficha(' ');
//    casillas[7]['G'-'A'] = new ficha(' ');
//    casillas[7]['H'-'A'] = new ficha(' ');

//    tablero1.setCasillas(casillas);
//    tablero1.impritablero();
//    tablero1.casillasjugables(2);
//    tablero1.impritablero();

    bool run;
    unsigned short opcion;

    do{
        opcion= menu();
        switch (opcion) {
        case 0:
            run = false;
            break;
        case 1:
        {
            string nombre1, nombre2;
            bool jugable[2] = {true,true};
            cout<<"Ingrese el nombre del jugador 1:"; cin>>nombre1;
            cout<<"Ingrese el nombre del jugador 2:"; cin>>nombre2;
            jugador jugador1(nombre1, '*');
            jugador jugador2(nombre2, '-');
            jugador jugadores[2] = {jugador1, jugador2};
            tablero tablero1(jugador1,jugador2);
            tablero1.initablero();
            unsigned int jugador = 1;
            while(true)
            {
                char fil,col;
                if (!tablero1.casillasjugables(jugador))
                {
                    cout << "!!!" << jugadores[jugador-1].getnombre() << " no tiene movimientos, se pasa al turno del rival!!!"<<endl;
                    jugable[jugador-1] = false;
                    if (!jugable[0] && !jugable[1]) break;
                    continue;
                }
                tablero1.impritablero();
                cout << "jugador " << jugadores[jugador-1].getnombre() << '(' << jugadores[jugador-1].getidd() << ')' <<endl;
                cout << "ingrese la fila:";
                cin >> fil;
                cout << "ingrese la columna:";
                cin >> col;
                if (!tablero1.casillavalida(fil-'0',col-'A'))
                {
                    cout << "!!!casilla invalida!!!" << endl;
                    tablero1.limpiarcasillas();
                    continue;
                }
                tablero1.limpiarcasillas();
                tablero1.volteacasillas(fil-'0',col-'A',jugador);
                for (int i = 0; i < 2; i++) jugable[i] = true;
                if (jugador == 1) jugador = 2;
                else jugador = 1;
            }
          tablero1.EscArchivo();
        }
        case 2:
        {
            cout<<endl<<" -----Historial de partidas -----"<<endl;
            leerHistorial();
            cout<<endl;
            break;
        }
        default:
        {
            cout << "opcion invalida" << endl;
            break;
        }
        }

        cout<<"Partida finalizada."<<endl<<endl;
    }while(run);

    return a.exec();
}

int menu(){
    unsigned short int x=5;
    cout<<"---------- Menu de juego ----------"<<endl;
    cout<<"1. Iniciar nueva partida."<<endl;
    cout<<"2. Ver historial de partidas."<<endl;
    cout<<"0. Finalizar."<<endl;


    cout<<"Ingrese la opcion deseada: "; cin>>x;


    return x;
}

void leerHistorial(){
    string nom1,pun1,nom2,pun2,fecha,linea;

    ifstream archivo("HistorialPartidas.txt");

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string valor;

        if (getline(ss, valor, ',')) nom1 = (valor);
        if (getline(ss, valor, ',')) pun1 = (valor);
        if (getline(ss, valor, ',')) nom2 = (valor);
        if (getline(ss, valor, ',')) pun2 = (valor);
        if (getline(ss, valor, ',')) fecha = (valor);

        cout<<nom1<<":"<<pun1<<" VS "<<nom2<<":"<<pun2<<"  Fecha: "<<fecha<<endl;
    }
    archivo.close();

}
