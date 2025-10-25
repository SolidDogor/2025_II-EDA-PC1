/*
    Ejercicio 14: Insertar nodos en orden ascendente sin duplicados y mostrarlos
*/
#include <iostream>
using namespace std;

//--Estructuras--
struct Nodo {
    int dato;
    Nodo* siguiente;
};

struct Lista { Nodo* cabeza = nullptr; };

//--Prototipos--
void agregarNodo(Lista&,int);
bool datoExistente(Lista&,int);
void mostrarLista(Lista&);

//--Variables globales--
Lista lista;

//--Main--
int main() {
    int opcion = 0, dato;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar dato\n"
            << "2.- Mostrar lista\n"
            << "3.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1: 
                cout << "Digite el dato: "; cin >> dato;
                if (datoExistente(lista,dato)) {
                    cout << "Debe digitar un dato no existente!\n";
                } else {                        
                    agregarNodo(lista,dato);
                }
                break;
            case 2: 
                cout << "Imprimiendo lista:\n";
                mostrarLista(lista);
                break;
            case 3: 
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no disponible.\n";
                break;
        }
        system("pause");
        system("cls");
    } while (opcion != 3);

    return 0;
}

//--Definiciones--
void agregarNodo(Lista& lista,int dato) {
    Nodo* nuevo = new Nodo{dato, nullptr};
    if(!lista.cabeza || lista.cabeza->dato > dato) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
    } else {
        Nodo* previo = nullptr;
        Nodo* actual = lista.cabeza;
        while(actual != nullptr && actual->dato < dato) {
            previo = actual;
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual;
        previo->siguiente = nuevo;
    }
    cout << dato << " agregado a la lista\n";
}

bool datoExistente(Lista& lista,int dato) {
    Nodo* aux = lista.cabeza;
    while (aux && aux->dato != dato) {
        aux = aux->siguiente;
    }
    return (aux) ? true : false;
}

void mostrarLista(Lista& lista) {
    Nodo* aux = lista.cabeza;
    if(!aux) {
        cout << "(Lista vacia)\n";
        return;
    }
    while (aux) {
        cout << aux->dato;
        (aux->siguiente) ? cout << " " : cout << ".";
        aux = aux->siguiente;
    }
    cout << "\n";
}