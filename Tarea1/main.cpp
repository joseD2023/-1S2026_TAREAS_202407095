#include <iostream>
using namespace std;

//llamamos a la cabecera de nuestra clase

#include "Coches.h"


int main() {

    //creamos nuestra instancia
    Coches miCarro(8,"Toyota","Azul");
    Coches tuCarro(5, "BMW", "Rojo");

    //CARRO MIO (1 instancia)
    cout << "INSTANCIA No 1 Nombre(miCarro)" << endl;
    cout << "Mi Carro Hace estas Acciones: " << miCarro.getMarca() << " Color " <<  miCarro.getColor()<<  endl;
    miCarro.arrancar();
    cout << "Una pista recta Dale aceleraaaaa !!! " << endl;
    miCarro.acelerar();
    cout << "Cuidado Una Personaaaa !!" << endl;
    miCarro.frenar();

    //TU CARRO (2 instancia)
    cout << "INSTANCIA No 2 Nombre(tuCarro)" << endl;
    cout << "Tu Carro Hace estas Acciones: " << tuCarro.getMarca() << " Color " << tuCarro.getColor() << endl;
    tuCarro.arrancar();
    cout <<  "Un pista Recta Dale Acelera wey!!" <<  endl;
    tuCarro.acelerar();
    tuCarro.acelerar();
    tuCarro.acelerar();
    cout << "Cuidado ahi estan Dos personas Paradas!!!"<< endl;
    tuCarro.frenar();


    return 0;
}