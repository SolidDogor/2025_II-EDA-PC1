//Quitar elementos en la pila
#include <iostream>
#include <stdlib.h>
using namespace std;

struct Nodo{
    int dato;
    Nodo *siguiente;
};

void agregarPila(Nodo *&, int);
void quitarPila(Nodo *&, int &);

int main() {
    Nodo *pila = NULL;
    int dato;
    cout << "Digite un numero: "; cin >> dato;
    agregarPila(pila, dato);
    cout << "Digite otro numero: "; cin >> dato;
    agregarPila(pila, dato);

    cout << "\nSacando elementos de la pila: ";
    while(pila!=NULL) {     //Mientras no sea el final de la pila...
        quitarPila(pila,dato);
        if(pila != NULL) cout << dato << " , ";
        else cout << dato << ".";
    }

    return 0;
}

//Definición de función
void agregarPila(Nodo *&pila, int n){
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->siguiente = pila;
    pila = nuevo_nodo;

    cout << "Elemento " << n << " agregado a pila correctamente\n";
}

void quitarPila(Nodo *&pila, int &n){
    Nodo *aux = pila;
    n = aux->dato;
    pila = aux->siguiente;
    delete aux;
}