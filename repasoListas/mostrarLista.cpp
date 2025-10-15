//Mostrar elementos en una lista
#include <iostream>
#include <stdlib.h>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;
};

void insertarElemento(Nodo *&, int);
void mostrarLista(Nodo *);
void menu();

Nodo *lista = NULL;

int main () {
    menu();

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

void mostrarLista (Nodo *lista) {
    Nodo *actual = new Nodo();
    actual = lista;
    while (actual != NULL) {
        cout << actual->dato;
        actual = actual->siguiente;
        (actual != NULL) ? cout << " , " : cout << ".\n";
    }
    delete actual;
}

void menu () {
    int n, opcion = 0;

    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar elemento\n2.- Mostrar lista\n3.- Salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite un numero: "; cin >> n;
            insertarElemento(lista, n);
            break;
        case 2:
            cout << "Imprimiendo lista: ";
            mostrarLista(lista);
            break;
        case 3:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion no disponible!\n";
            break;
        }

        system("pause");
        system("cls");

    } while (opcion != 3);
        
}