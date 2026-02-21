#include <iostream>
#include <vector>

#include "string"
#include "fstream"
#include "vector"
using namespace std;



/*Definimos una Estructura para almacenar distintos tipos de datos*/
struct Bodega {
    string fruta;
    int cantidad;
    double precio;
    string ubicacion;
};

/*Funcionamiento para Leer nuestra Estructura y Mostrar los Datos*/
void imprimirArchivo(vector<Bodega> vec) {
    for (int i=0; i<vec.size(); i++) {
        cout << "-> " << vec.at(i).fruta << endl;
        cout << "-> " << vec.at(i).cantidad << endl;
        cout << "-> " << vec.at(i).precio << endl;
        cout << "-> " << vec.at(i).ubicacion << endl;
        cout << "-----------------------------------" << endl;}
}


/*Funcionamiento de un entorno de validacion de estructura*/

bool esDigito(string digito) {
    if (digito.empty()){return false; }
    for (char d : digito) {
        if (!isdigit(d)) {
            return false;
        }}return true;}



bool esString(string texto) {
    if (texto.empty()){return false;}
    for (char t : texto) {
        if (!isalpha(t)) {
            return false; }}return true; }


bool esDecimal(string decimal) {
    if (decimal.empty()){return false;}
    bool punto = false; //si ya punto se vuelve true
    for (char dc : decimal) {
        if (isdigit(dc)){continue;}
        if (dc == '.' && !punto) { //si el punto es true es porque ya antes aparecio uno
            punto = true;
            continue; }
        return false;
    }
    if (decimal == "."){return false;} //porque no puede venir un punto por si solo
    return true;
}


/*La Lectura y Comprobacion del que el programa Funcione*/
void lecturaArchivoVisualizacion(string arch) {
    ifstream archivo(arch); //archivo
    vector<Bodega> listaProductos;
    Bodega b;
    bool  sinFallas = false;


    if (!archivo.is_open()) {
        cout << "No se puede abrir el Archivo" << endl;
        return;
    }

    string fruta, ubicacion, cantidad, precio;


    while (getline(archivo, fruta, ' ')) {
        /*Asignacion de valores provenientes del archivo */

        getline(archivo, cantidad, ' ');
        getline(archivo, precio, ' ');
        getline(archivo, ubicacion);



        if (!esString(fruta) || !esDigito(cantidad) || !esDecimal(precio) || !esString(ubicacion) ) {
            cout << "Linea Invalida: " << fruta << " " << cantidad << " " << precio << " " << ubicacion << endl;; sinFallas = true;
        }

        if (!sinFallas) {
            b.fruta = fruta;
            b.cantidad = stoi(cantidad);
            b.precio = stod(precio);
            b.ubicacion = ubicacion;
            listaProductos.push_back(b);
        }

        sinFallas = false; //se reinicia cada vez que pasa por una validacion
    }

    imprimirArchivo(listaProductos);
}


/*Creamos lo que es Nuestro Menus Principal para el Usuario*/
void menuPrincial() {
    int opc;
    while (true) {
        cout << "+--- Bienvennidos al Menu Principal Usac ---+ " << endl;
        cout << "+--- 1. Leer Archivo.inv e imprimir Contenido ---+" << endl;
        cout << "+--- 2. Salir                                 ---+" << endl;
        /*Como no vamos a Ingresar Datos usamos cin de manera sencilla*/
        cin >> opc;

        if (cin.fail()) { //si no colocamos esto y cometemos un error en la opcion esto se vuelve un bucle infinito
            cout << "Opcion Invalida del Usuario " << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        if (opc == 1) {
            cout << " Lectura de Archivo y Visualizacion "<< endl;
            string valido = "../inventario.inv";
            string noValido = "../inventario_invalido.inv";
            lecturaArchivoVisualizacion(noValido);

        }else if (opc == 2) {
            cout << " Gracias por Acompañarnos y Utilizar nuestro Programa " << endl;
            break;
        }}}


int main() {
    menuPrincial();
    return 0;
}