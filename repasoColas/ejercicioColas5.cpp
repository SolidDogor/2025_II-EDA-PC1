/*
        Ejercicio 5: Historial de tareas diarias
                Queremos guardar las tareas hechas hoy en una cola, y al final del día poder:
                        Agregar nuevas tareas al final (orden cronológico).
                        Mostrar todas las tareas.
                        Eliminar la primera (la más antigua).
                        Vaciar el historial.
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Tarea {
        string descripcion;
        Tarea *siguiente;
};

struct Cola {
        Tarea *cabeza = nullptr;
        Tarea *final = nullptr;
        int cantidad = 0;
};

//Prototipado de funciones
void agregarTarea (Cola &, string);
void mostrarCola (Cola &);
void eliminarTarea (Cola &);
void eliminarCola (Cola &);
void menu ();

//variables globales
Cola cola;

int main () {
        menu();
        return 0;
}

//Definicion de funciones
void agregarTarea (Cola &cola, string descripcion) {
        Tarea *nuevaTarea = new Tarea{descripcion, nullptr};

        if (!cola.cabeza) {
                cola.cabeza = cola.final = nuevaTarea;
        } else {
                cola.final->siguiente = nuevaTarea;
                cola.final = nuevaTarea;
        }

        cout << "Tarea " << descripcion << " agregada con exito a la cola.\n";
        cola.cantidad++;
}

void mostrarCola (Cola &cola) {
        Tarea *aux = cola.cabeza;
        if (!aux) {
                cout << "Ingrese alguna tarea!\n";
                return;
        }
        cout << "Tareas pendientes (" << cola.cantidad << "):\n";
        while (aux) {
                cout << "\t-" << aux->descripcion << "\n";
                aux = aux->siguiente;
        }
}

void eliminarTarea (Cola &cola) {
        Tarea *aux = cola.cabeza;
        if (!aux) {
                cout << "Ingrese alguna tarea!\n";
                return;
        }
        cola.cabeza = cola.cabeza->siguiente;
        if (!cola.cabeza) cola.final = nullptr;
        cout << "Eliminando " << aux->descripcion << "...\n";
        delete aux;
        cola.cantidad--;
        cout << "Tarea eliminada!\n";
}

void eliminarCola (Cola &cola) {
        if (!cola.cabeza) {
                cout << "Ingrese alguna tarea!\n";
                return;
        }
        cout << "Eliminando cola...\n";
        while (cola.cabeza) {
                Tarea *aux = cola.cabeza;
                cola.cabeza = cola.cabeza->siguiente;
                delete aux;
        }
        cola.final = nullptr;
        cola.cantidad = 0;
        cout << "Cola eliminada!\n";
}

void menu() {
        int opcion = 0;
        string descripcion;

        do {
                cout << "\t---Menu---\n";
                cout << "1.- Agregar tarea\n";
                cout << "2.- Mostrar tareas\n";
                cout << "3.- Eliminar tarea\n";
                cout << "4.- Eliminar tareas\n";
                cout << "5.- Salir\n>";
                cin >> opcion;

                switch (opcion) {
                case 1:
                        cout << "Descripcion de tarea: "; cin >> descripcion;
                        agregarTarea(cola, descripcion);
                        break;
                case 2:
                        cout << "Imprimiendo cola:\n";
                        mostrarCola(cola);
                        break;
                case 3:
                        eliminarTarea(cola);
                        break;
                case 4:
                        eliminarCola(cola);
                        break;
                case 5:
                        cout << "Saliendo del programa...\n";
                        break;
                default:
                        cout << "Opcion no disponible!\n";
                        break;
                }
                system("pause");
                system("cls");
        } while (opcion != 5);
}