#include <QCoreApplication>
#include "tablero.h"
#include "jugador.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


int menu();
void leerHistorial();


int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);

    string nombre1, nombre2;
    short int opcion=1;

    opcion=menu();

    while(opcion!=0){

        if(opcion==1){

            cout<<"Ingrese el nombre del jugador 1:"; cin>>nombre1;
            cout<<"Ingrese el nombre del jugador 2:"; cin>>nombre2;
            jugador jugador1(nombre1, '*');
            jugador jugador2(nombre2, '-');

            tablero tablero1(jugador1,jugador2);
            tablero1.initablero();
            tablero1.impritablero();

            tablero1.EscArchivo();

        }

        else if(opcion==2){
            cout<<endl<<" -----Historial de partidas -----"<<endl;
            leerHistorial();
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
