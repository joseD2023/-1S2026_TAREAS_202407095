/*Vamos a Trabajar con Clase Coches */

#ifndef TAREAS_COCHES_H
#define TAREAS_COCHES_H

#include <iostream>
#include "string"
using namespace std;

class Coches {
private:
    //vamos a declarar los atributos privados para que otras clases no puedan acceder a ellos
    int velocidad;
    string marca;
    string color;

public:
    //definimos Nuestros metodos que seran las acciones de la clase Coche

    Coches(int velocidad, string marca, string color); //definimos nuestro constructor

    void arrancar();
    void acelerar();
    void frenar();
    string getMarca();
    string getColor();


};


#endif //TAREAS_COCHES_H