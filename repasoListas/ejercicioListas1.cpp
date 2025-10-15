/*
    Ejercicio 1: Crear una lista que almanece 'n' numeros enteros
                    Calcular el menor y mayor elemento de la lista
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;
};

//Prototipo de funciones
void insertarElemento(Nodo *&, int);
void mostrarLista(Nodo *);
int mayor(Nodo *);
int menor(Nodo *);
void menu();

Nodo *lista = NULL;

int main () {
    menu();
    return 0;
}

//Definicion de funciones
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

void mostrarLista(Nodo *lista) {
    while (lista != NULL) {
        (lista->siguiente == NULL) ? cout << lista->dato << ".\n" : cout << lista->dato << " , ";
        lista = lista->siguiente;
    }
}

int mayor(Nodo *lista) {
    int mayor = lista->dato;
    while (lista != NULL) {        
        if(lista->dato > mayor) mayor = lista->dato;
        lista = lista->siguiente;
    }
    return mayor;
}

int menor(Nodo *lista) {
    int menor = lista->dato;
    while (lista != NULL) {        
        if(lista->dato < menor) menor = lista->dato;
        lista = lista->siguiente;
    }
    return menor;
}

void menu () {
    int n, opcion = 0;

    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar elemento\n2.- Encontrar mayor\n3.- Encontrar menor\n4.- Salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite un numero: "; cin >> n;
            insertarElemento(lista, n);
            cout << "Lista hasta el momento: ";
            mostrarLista(lista);
            break;
        case 2:
            cout << "Mayor numero en lista: " << mayor(lista) << "\n";
            break;
        case 3:
            cout << "Menor numero en lista: " << menor(lista) << "\n";
            break;
        case 4:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion no disponible!\n";
            break;
        }

        system("pause");
        system("cls");

    } while (opcion != 4);
    
}