/*
    Ejercicio 2: Hacer un programa que guarde datos de clientes de un banco,
    los almacene en cola y por último muestre los clientes en el orden correcto
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

struct Cliente {
    string nombre;
    int dinero;
};

struct Nodo {
    Cliente cliente;
    Nodo *siguiente;
};

//Prototipo de función
void agregarElemento(Nodo *&, Nodo *&, string, int);
void imprimirCola(Nodo *&);

int main () {
    Nodo *frente = NULL;
    Nodo *fin = NULL;

    string nombre;
    int dinero, opcion = 0;

    while (opcion != 3) {
        cout << "---Menu---\n1.- Agregar cliente a la cola\n2.-Mostrar cola";
        cout << "\n3.-Salir del programa\n";
        cout << "Digite una opcion:"; cin >> opcion;
        fflush(stdin);
        switch (opcion) {
            case 1: cout << "Digite nombre del cliente: "; cin >> nombre;
                    cout << "Digite el dinero del cliente: "; cin >> dinero;
                    agregarElemento(frente, fin, nombre, dinero);
                    break;
            case 2: imprimirCola(frente);
                    break;
            case 3: cout << "Saliendo del programa...\n";
                    break;
            default: cout << "Opcion invalida, intente nuevamente.\n";
        }
        system("pause");
        system("cls");
    }

    return 0;
}

//Definición de funciones
void agregarElemento(Nodo *&frente, Nodo *&fin, string nombre, int dinero) {
    Nodo *nuevo_nodo = new Nodo();
    
    nuevo_nodo->cliente.nombre = nombre;
    nuevo_nodo->cliente.dinero = dinero;
    nuevo_nodo->siguiente = NULL;

    (frente == NULL)? frente = nuevo_nodo : fin->siguiente = nuevo_nodo;

    fin = nuevo_nodo;
    cout << "Cliente " << nuevo_nodo->cliente.nombre << " agregado con exito a la cola\n";
}

void imprimirCola(Nodo *&frente) {
    Nodo *actual = frente;
    while (actual != NULL) {
        cout << "Cliente: ";
        cout << actual -> cliente.nombre << ", Dinero: ";
        cout << actual -> cliente.dinero << "\n";
        actual = actual -> siguiente;
    }
    cout << ".\n";
    delete actual;
}