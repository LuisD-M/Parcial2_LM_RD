#include <QCoreApplication>
#include "tablero.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    tablero tablero1;
    tablero1.initablero();
    tablero1.impritablero();



    return a.exec();
}
