#include "jugador.h"
#include "tablero.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


int menu();
void leerHistorial();
int str2intN(string a);
int str2intC(string a);


int main(){

    bool run = true; // define si el programa sigue activo o no
    unsigned short opcion; // opcion que escoge el usuario

    do{
        opcion= menu(); // despliega el menu y devuelve la opcion ingresada por el usuario
        switch (opcion) {
        case 0: // caso en el que finaliza el programa
        {
            run = false;
            cout<<endl<<"Programa finalizado."<<endl<<endl;
            break;
        }
        case 1: // caso del juego
        {
            string nombre1, nombre2;
            bool jugable[2] = {true,true}; // si el jugador puede jugar o no
            cout<<"Ingrese el nombre del jugador 1:"; cin>>nombre1;
            cout<<"Ingrese el nombre del jugador 2:"; cin>>nombre2;
            jugador jugador1(nombre1, '*'); // se crea jugador 1
            jugador jugador2(nombre2, '-'); // se crea jugador 2
            jugador jugadores[2] = {jugador1, jugador2}; // se guardan en un arreglo
            tablero tablero1(jugador1,jugador2); // se crea el tablero
            tablero1.initablero(); // se inicializa el tablero
            unsigned int jugador = 1; // inicia jugando el jugador 1
            bool cond=true; // define si la partida continua o no

            while(cond)
            {
                int fil,col, contador=0;
                string f, c;
                // verifica que el jugador que tiene el turno tenga casillas en las que pueda jugar
                if (!tablero1.casillasjugables(jugador)) // cuando no tiene casillas disponibles para jugar
                {
                    contador = tablero1.totalfichas(); // cuenta el total de fichas
                    if(contador == filas*columnas){ // verifica si el tablero esta lleni
                        cout<<endl<<"Tablero lleno"<<endl;
                        cond=false;
                    }else{ // si no esta lleno y el jugador no puede jugar es porque simplemente no tiene movimientos disponibles
                        cout << "!!!" << jugadores[jugador-1].getnombre() << " no tiene movimientos, se pasa al turno del rival!!!"<<endl;
                        jugable[jugador-1] = false;

                        if (!jugable[0] && !jugable[1]) cond=false; // si ambos jugadores no tienen movimientos disponibles la partida acaba
                    }
                }else
                {
                    tablero1.impritablero(); // muestra el tablero en consola
                    cout <<endl<< "jugador " << jugadores[jugador-1].getnombre() << '(' << jugadores[jugador-1].getidd() << ')' <<endl;

                    cout << "ingrese la fila:"; cin >> f;
                    fil = str2intN(f);
                    // verifica si la fila ingresada esta dentro o fuera del rango del tablero
                    while (fil<0 || fil>(filas-1)){
                        cout<<"Fila invalida"<<endl;
                        cout << "ingrese la fila:"; cin >> f;
                        fil = str2intN(f);
                    }

                    cout << "ingrese la columna:"; cin >> c;
                    col = str2intC(c);
                    // verifica si la columna esta dentro o fuera del rango del tablero
                    while (col<0 || col>(columnas-1)){
                        cout<<"Columna invalida"<<endl;
                        cout << "ingrese la Columna:"; cin >> c;
                        col = str2intC(c);
                    }
                    // verifica si la casilla ingresada es valida para realizar un movimiento
                    if (!tablero1.casillavalida(fil,col))
                    {
                        cout <<"["<<fil<<"]-"<<"["<<char(col+65)<<"] es "<< "!!!casilla invalida!!!" << endl;
                        tablero1.limpiarcasillas();
                        continue;
                    }
                    tablero1.limpiarcasillas(); // borra las 'O' que marcaban las casillas donde habian movimientos validos
                    tablero1.volteacasillas(fil,col,jugador); // voltea las casillas donde haya encierros
                    for (int i = 0; i < 2; i++) jugable[i] = true; // ya que un jugador pudo jugar se asume que ambos pueden seguir jugando
                }
                // cambia al siguiente jugador
                if (jugador == 1) jugador = 2;
                else jugador = 1;
            }
            tablero1.impritablero(); // muestra el tablero en consola
            tablero1.win(); // despliega la informacion de la partida
            tablero1.EscArchivo(); // guarda la informacion en un archivo
            break;

        }
        case 2: // caso que muestra el historial de partidas
        {
            cout<<endl<<" -----Historial de partidas -----"<<endl;
            leerHistorial(); // lee el justoria de partidas y lo despliega en consola
            cout<<endl;
            break;
        }
        default:
        {
            cout <<endl<< "opcion invalida" << endl<<endl;
            break;
        }
        }
    }while(run);

    return 0;
}

int menu(){
    unsigned short int x=5;
    string a="";
    cout<<"---------- Menu de juego ----------"<<endl;
    cout<<"1. Iniciar nueva partida."<<endl;
    cout<<"2. Ver historial de partidas."<<endl;
    cout<<"0. Finalizar."<<endl;

    cout<<"Ingrese la opcion deseada: "; cin>>a;
    x = str2intN(a);

    return x;
}

void leerHistorial(){
    string nom1,pun1,nom2,pun2,fecha,linea;

    try{

        ifstream archivo("HistorialPartidas.txt");

        if(archivo.is_open()){

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
        else throw '1';
    }
    catch (char c){
        if(c=='1')
            cout<<"Error con el archivo de lectura"<<endl<<endl;
        else
            cout<<"Erros inesperado"<<endl;
    }
}

int str2intN(string a){
    int l,c=0;
    l=a.length();

    if(l<0 || l>(1))
        c=1000;
    else
        c=a[0]-48;

    return c;
}

int str2intC(string a){
    int l,c=0;
    l=a.length();

    if(l<0 || l>(1))
        c=1;
    else
        c=(int)a[0]-65;

    return c;
}


