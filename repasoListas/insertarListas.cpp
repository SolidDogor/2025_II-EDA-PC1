//Insetar elementos en una lista
#include <iostream>
#include <stdlib.h>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;
};

void insertarElemento(Nodo *&, int);

int main () {
    int n;
    Nodo *lista;
    
    cout << "Digite un numero: "; cin >> n;
    insertarElemento(lista, n);

    cout << "Digite un numero: "; cin >> n;
    insertarElemento(lista, n);

    cout << "Digite un numero: "; cin >> n;
    insertarElemento(lista, n);

    cout << "Digite un numero: "; cin >> n;
    insertarElemento(lista, n);

    cout << "Digite un numero: "; cin >> n;
    insertarElemento(lista, n);

    return 0;
}

void insertarElemento(Nodo *&lista, int dato) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = dato;

    Nodo *aux1 = lista;
    Nodo *aux2;

    while ((aux1 != NULL) && (aux1->dato < dato)) {
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }

    (lista == aux1) ? lista = nuevo_nodo :aux2->siguiente = nuevo_nodo;

    nuevo_nodo->siguiente = aux1;

    cout << "Elemento " << dato << " insertado con exito.\n";
}