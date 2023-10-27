#include "historial.h"

historial::historial(){}

void historial::VerResultados()
{
    string nom1,pun1,nom2,pun2,linea;

    ifstream archivo("HistorialPartidas.txt");

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string valor;

        if (getline(ss, valor, ',')) nom1 = (valor);
        if (getline(ss, valor, ',')) pun1 = (valor);
        if (getline(ss, valor, ',')) nom2 = (valor);
        if (getline(ss, valor, ',')) pun2 = (valor);

        cout<<nom1<<":"<<pun1<<" ; "<<nom2<<":"<<pun2<<endl;
    }
    archivo.close();

}
