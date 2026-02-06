//
// Created by josev on 5/02/2026.
//

#include "Coches.h" //aqui se anncia que existe una Clase llamada Coche
#include <iostream>
#include "string"
using namespace std;

//aqui vamos a colocar los metodos que haran funcionar a nuestra clase

Coches::Coches(int v, string m, string c) {
    velocidad = v;
    marca = m;
    color = c;
}

string Coches::getMarca() {
    return marca;
}

string Coches::getColor() {
    return color;
}

void Coches::arrancar() {
    cout << "Arrancando Carro " << marca <<  "....Run Run Run Run" << endl;
}

void Coches::acelerar() {
    velocidad += 2;
    cout << "Coche Acelerando a " <<  velocidad << "km/h" << endl;
}

void Coches::frenar() {
    for (int i=velocidad; i >= 0 ; i--) {

        if (i == 0) {
            cout << "Coche ha Frenado" << endl;
            break;
        }

        cout << "Desacelerando... " << "-" <<  i <<   endl;

    }
}



