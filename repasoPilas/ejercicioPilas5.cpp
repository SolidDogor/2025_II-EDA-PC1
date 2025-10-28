/*
    Ejercicio 5: Pila de tareas recientes
        Queremos almacenar las tareas ejecutadas más recientemente.
        Cada tarea nueva se apila al inicio y al mostrar, la última aparece primero.
        Debe permitir:
            - Agregar tarea
            - Mostrar pila
            - Eliminar
            - Vaciar pila
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Tarea {
    string descripcion;
    Tarea* siguiente;
};

struct Pila {
    Tarea* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarTarea(Pila&, string&);
void mostrarPila(Pila&);
void eliminarTarea(Pila&);
void vaciarPila(Pila&);

//Main
int main() {
    Pila pila;
    int opcion = 0;
    string descripcion;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar tarea\n"
            << "2.- Mostrar pila de tareas\n"
            << "3.- Eliminar tarea\n"
            << "4.- Vaciar pila\n"
            << "5.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite la descripcion: "; cin >> descripcion;
                agregarTarea(pila,descripcion);
                break;
            case 2:
                mostrarPila(pila);
                break;
            case 3:
                eliminarTarea(pila);
                break;
            case 4:
                vaciarPila(pila);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                vaciarPila(pila);
                break;
            default:
                cout << "Opcion no implementada.\n";
        }
        system("pause");
        system("cls");
    } while (opcion !=5);
    return 0;
}

//Definiciones
void agregarTarea(Pila& pila, string& descripcion) {
    Tarea* nueva = new Tarea{descripcion,nullptr};
    nueva->siguiente = pila.cabeza;
    pila.cabeza = nueva;
    pila.cantidad++;
    cout << descripcion << " agregada con exito a la pila.\n";
}

void mostrarPila(Pila& pila) {
    if(!pila.cabeza) {
        cout << "Pila vacia.\n";
        return;
    }
    Tarea* aux = pila.cabeza;
    cout << "Cantidad de tareas en pila: " << pila.cantidad << "\n";
    while(aux) {
        cout << aux->descripcion;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarTarea(Pila& pila) {
    if(!pila.cabeza) {
        cout << "Ingrese alguna tarea primero.\n";
        return;
    }
    Tarea* temp = pila.cabeza;
    pila.cabeza = pila.cabeza->siguiente;
    cout << temp->descripcion << " eliminado de pila.\n";
    pila.cantidad--;
    delete temp;
}

void vaciarPila(Pila& pila) {
    if(!pila.cabeza) {
        cout << "Pila vacia.\n";
        return;
    }
    while(pila.cabeza) {
        Tarea* temp = pila.cabeza;
        pila.cabeza = pila.cabeza->siguiente;
        delete temp;
    }
    cout << "Pila vaciada con exito.\n";
    pila.cantidad = 0;
}

