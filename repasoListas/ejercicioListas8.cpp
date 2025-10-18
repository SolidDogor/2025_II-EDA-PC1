/*
    Ejercicio 8: Liberar memoria correctamente en un sistema que reinicia los datos al final del día
    Se deben insertar varios nodos, eliminar todos con una sola función y liberarlos con delete
    Mostrar un mensaje de éxito
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Nodo {
    int dato;
    Nodo *siguiente;
};

struct Lista {
    Nodo *cabeza = nullptr;
    int cantidad = 0;
};

//Prototipado de funciones
void agregarNodo(Lista &, int);
void mostrarLista(Lista &);
void eliminarLista(Lista &);
void menu();

//Variables globales
Lista lista;

int main () {
    menu();
    return 0;
}

//Definicion de funciones
void agregarNodo(Lista &lista, int dato) {
    Nodo *nuevo_nodo = new Nodo{dato, nullptr};
    if(lista.cabeza == nullptr || lista.cabeza->dato < dato) {
        nuevo_nodo->siguiente = lista.cabeza;
        lista.cabeza = nuevo_nodo;
    } else {
        Nodo *aux = lista.cabeza;
        while (aux->siguiente && aux->siguiente->dato >= dato) {
            aux = aux->siguiente;
        }
        nuevo_nodo->siguiente = aux->siguiente;
        aux->siguiente = nuevo_nodo;
    }
    cout << "Nodo: " << dato << " agregado con exito al inventario.\n";
    lista.cantidad++;
}

void mostrarLista(Lista &lista) {
    if (lista.cabeza == nullptr) {
        cout << "Lista vacia! Ingrese un valor primero.\n";
        return;
    }
    Nodo *p = lista.cabeza;
    while (p) {
        cout << "Dato: " << p->dato << "\n";
        p = p->siguiente;
    }
}

void eliminarLista(Lista &lista) {
    if (!lista.cabeza) {
        cout << "Lista vacia! Ingrese un valor primero.\n";
        return;
    }

    while (lista.cabeza) {
        Nodo *temp = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        cout << "Eliminando: " << temp->dato << "\n";
        delete temp;
        lista.cantidad--;
    }

    lista.cabeza = nullptr;
    lista.cantidad = 0;

    cout << "Lista eliminada correctamente.\n";
}


void menu() {
    int dato, opcion = 0;

    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar nodo\n2.- Mostrar lista\n3.- Eliminar lista\n4.- Salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite el dato: "; cin >> dato;
            agregarNodo(lista, dato);
            cout << "Lista hasta el momento:\n";
            mostrarLista(lista);
            break;
        case 2:
            cout << "Imprimiendo lista:\n";
            mostrarLista(lista);
            break;
        case 3:
            cout << "Eliminando la lista completa...\n";
            eliminarLista(lista);
            cout << "Lista restante:\n";
            mostrarLista(lista);
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