#include <QCoreApplication>
#include "tablero.h"
#include "jugador.h"
#include "historial.h"
#include <iostream>
using namespace std;


int menu();


int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    short int opcion=1;

    opcion=menu();

    historial Historial1;

    while(opcion!=0){

        if(opcion==1){

            jugador jugador1("Sara", '*');
            jugador jugador2("Luis", '-');

            tablero tablero1(jugador1,jugador2);
            tablero1.initablero();
            tablero1.impritablero();

        }

        else if(opcion==2){
            cout<<endl<<" -----Historial de partidas -----"<<endl;
            Historial1.VerResultados();
            cout<<endl;
        }

        else{
            cout<<"Juego finalizado."<<endl<<endl;
            break;
        }

        opcion=menu();

    }

    cout<<"El juego a finalizado."<<endl;
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
