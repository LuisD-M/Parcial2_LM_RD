#include <QCoreApplication>
#include "jugador.h"
#include "tablero.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


int menu();
void leerHistorial();


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
            string nombre1, nombre2;
            cout<<"Ingrese el nombre del jugador 1:"; cin>>nombre1;
            cout<<"Ingrese el nombre del jugador 2:"; cin>>nombre2;
            jugador jugador1(nombre1, '*');
            jugador jugador2(nombre2, '-');
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
                tablero1.volteacasillas(fil-'0',col-'A',jugador);
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
