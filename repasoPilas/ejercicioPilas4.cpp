/*
    Ejercicio 4: Pila de acciones
        Cada acción (por ejemplo, “escribir”, “borrar”, “copiar”) se apila en una pila (LIFO).
        Cuando el usuario presiona “deshacer”, se elimina la última acción.
        Debe permitir:
            Agregar una acción
            Mostrar historial de acciones
            Deshacer última acción
            Vaciar pila
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Accion { 
    string descripcion; 
    Accion* siguiente; 
};

struct Pila {
    Accion* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarAccion(Pila&,string&);
void mostrarPila(Pila&);
void deshacerAccion(Pila&);
void vaciarPila(Pila&);

//Variables globales
Pila pila;

//Main
int main() {
    int opcion = 0;
    string descripcion;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar accion\n"
            << "2.- Mostrar pila\n"
            << "3.- Deshacer accion\n"
            << "4.- Vaciar pila\n"
            << "5.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite la descripcion: "; cin >> descripcion;
                agregarAccion(pila,descripcion);
                break;
            case 2:
                cout << "Mostrando pila:\n";
                mostrarPila(pila);
                break;
            case 3:
                deshacerAccion(pila);
                break;
            case 4:
                vaciarPila(pila);
                break;
            case 5:
                vaciarPila(pila);
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no disponible.\n";
                break;
        }
        system("pause");
        system("cls");
    } while (opcion != 5);
    return 0;
}

//Definiciones
void agregarAccion(Pila& pila,string& descripcion) {
    Accion* nueva = new Accion{descripcion,nullptr};
    nueva->siguiente = pila.cabeza;
    pila.cabeza = nueva;
    cout << descripcion << " agregada a la pila.\n";
    pila.cantidad++;
}

void mostrarPila(Pila& pila) {
    if(!pila.cabeza) {
        cout << "Pila vacia.\n";
        return;
    }
    Accion* aux = pila.cabeza;
    cout << "Acciones en pila: " << pila.cantidad << "\n";
    while(aux) {
        cout << aux->descripcion;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void deshacerAccion(Pila& pila) {
    if(!pila.cabeza) {
        cout << "Ingrese alguna accion primero.\n";
        return;
    }
    Accion* aux = pila.cabeza;
    pila.cabeza = pila.cabeza->siguiente;
    cout << aux->descripcion << " eliminada de pila.\n";
    delete aux;
    pila.cantidad--;
}

void vaciarPila(Pila& pila) {
    if(!pila.cabeza) {
        cout << "Pila vacia.\n";
        return;
    }
    while(pila.cabeza) {
        Accion* aux = pila.cabeza;
        pila.cabeza = pila.cabeza->siguiente;
        delete aux;
    }
    pila.cantidad = 0;
    cout << "Pila vaciada con exito.\n";
}
