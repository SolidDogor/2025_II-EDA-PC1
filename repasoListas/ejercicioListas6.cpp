/*
    Ejercicio 6: Hacer un sistema de tareas pendientes (To-Do List). Cada tarea tiene descripción
                    y prioridad (1 = urgente, 2 = media, 3 = baja). Insertar tareas y mostrarlas
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
enum Prioridad {
    URGENTE = 1,
    MEDIA = 2,
    BAJA = 3
};

struct Tarea {
    string descripcion;
    Prioridad prioridad;
    Tarea *siguiente;
};

struct Lista {
    Tarea *encabezado = nullptr;
    int cantidad = 0;
};

//Prototipos de funciones
void insertarTarea(Lista &, string, Prioridad);
string prioridadToString(Prioridad);
void mostrarTareas(const Lista &);


int main () {
    Lista lista;
    string descripcion;
    int prioridad, q = 3;
    
    while (q--) {
        cout << "Descripcion: "; cin >> descripcion;
        cout << "Prioridad: "; cin >> prioridad;
        insertarTarea(lista, descripcion, (Prioridad)prioridad);
    }
    
    mostrarTareas(lista);

    return 0;
}

//Declaraciones de funciones
void insertarTarea(Lista &lista, string descripcion, Prioridad prioridad) {
    Tarea *nueva_tarea = new Tarea{descripcion, prioridad, nullptr};

    if(lista.encabezado == NULL || lista.encabezado->prioridad > prioridad) {
        nueva_tarea->siguiente = lista.encabezado;
        lista.encabezado = nueva_tarea;
    } else {
        Tarea *aux = lista.encabezado;
        while(aux->siguiente && aux->siguiente->prioridad <= prioridad) {
            aux = aux->siguiente;
        }
        nueva_tarea->siguiente = aux->siguiente;
        aux->siguiente = nueva_tarea;
    }

    cout << "Tarea " << descripcion <<" agregada con exito a la lista.\n";
    lista.cantidad++;
}

string prioridadToString(Prioridad p) {
    switch (p) {
        case URGENTE: return "URGENTE";
        case MEDIA: return "MEDIA";
        case BAJA: return "BAJA";
        default: return "Desconocido";
    }
}

void mostrarTareas(const Lista &lista) {
    Tarea *p = lista.encabezado;
    while (p) {
        cout << p->descripcion << " : " << prioridadToString(p->prioridad) << "\n";
        p = p->siguiente;
    }
}
