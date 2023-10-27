#include <QCoreApplication>
#include "tablero.h"
#include "jugador.h"
#include <iostream>
using namespace std;


int menu();


int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

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
            jugador jugador1("Sara", '*');
            jugador jugador2("Luis", '-');
            tablero tablero1(jugador1,jugador2);
            tablero1.initablero();
            unsigned int jugador = 1;
            while(true)
            {
                char fil,col;
                tablero1.impritablero();
                cout << "jugador " << jugador << endl;
                cout << "ingrese la fila:";
                cin >> fil;
                cout << "ingrese la columna:";
                cin >> col;
                tablero1.movimientovalido(fil-'0',col-'A',jugador);
                if (jugador == 1) jugador = 2;
                else jugador = 1;
            }
        }
        case 2:
        {
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
