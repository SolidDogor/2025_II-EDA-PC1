/*
    Ejercicio 1: Hacer un programa en C++, utilizando Colas que contenga el siguiente menu:
    1. Insertar un caracter a una cola
    2. Mostrar todos los elementos de la cola
    3. Salir
*/

#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;
};

//Prototipo de función
void agregarElemento(Nodo *&, Nodo *&, int);
void imprimirCola(Nodo *&);

int main () {
    Nodo *frente = NULL;
    Nodo *fin = NULL;

    int n, opcion = 0;

    while (opcion != 3) {
        cout << "---Menu---\n1.- Agregar elemento a la cola\n2.-Mostrar cola";
        cout << "\n3.-Salir del programa\n";
        cout << "Digite una opcion:"; cin >> opcion;
        switch (opcion) {
            case 1: cout << "Digite un dato: "; cin >> n;
                    agregarElemento(frente, fin, n);
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
void agregarElemento(Nodo *&frente, Nodo *&fin, int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->siguiente = NULL;

    (frente == NULL)? frente = nuevo_nodo : fin->siguiente = nuevo_nodo;

    fin = nuevo_nodo;
    cout << "Elemento " << n << " agregado con exito a la cola\n";
}

void imprimirCola(Nodo *&frente) {
    Nodo *actual = frente;
    while (actual != NULL) {
        cout << actual -> dato << " ";
        actual = actual -> siguiente;
    }
    cout << ".\n";
    delete actual;
}