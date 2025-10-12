/*
    Ejercicio 1: Hacer un programa para agregar números enteros a una pila, hasta que el 
    usuario lo decida, después mostrar todos los números introducidos en la pila
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct Nodo{
    int dato;
    Nodo *siguiente;
};

//Prototipo de función
void agregarElemento(Nodo *&, int);
void sacarElemento(Nodo *&, int &);

int main() {
    Nodo *pila = NULL;
    int dato;
    char rpt;

    do{
        cout << "Digite un numero para agregar a la pila: "; cin >> dato;
        agregarElemento(pila, dato);
        cout << "Desea agregar otro elemento a pila (s/n): ";
        cin >> rpt;
    } while ((rpt=='S')||(rpt=='s'));

    cout << "\nSacando los elementos en pila: ";
    while(pila != NULL) {
        sacarElemento(pila, dato);
        if(pila != NULL) cout << dato << " , ";
        else cout << dato << ".";
    }

    return 0;
}

//Definición de función
void agregarElemento(Nodo *&pila, int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->siguiente = pila;
    pila = nuevo_nodo;

    cout << "Elemento " << n << " agregado a la pila\n";
}

void sacarElemento(Nodo *&pila, int &n) {
    Nodo *aux = pila;
    n = aux->dato;
    pila = aux->siguiente;
    delete aux;
}