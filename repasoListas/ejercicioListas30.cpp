/*
    Ejercicio 30 – Lista de tareas pendientes (ordenada + eliminación múltiple)
    Crea una lista simple de tareas, donde cada tarea tiene:
        - descripcion (string)
        - prioridad (int: 1 = alta, 2 = media, 3 = baja)
    Debe permitir:
        - Agregar tarea (insertada ordenada por prioridad ascendente → 1 antes que 2, etc.)
        - Mostrar todas las tareas
        - Eliminar todas las tareas de una prioridad específica
        - Vaciar lista
        - Salir
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Tarea {
    string descripcion;
    int prioridad;
    Tarea* siguiente;
};

struct Lista {
    Tarea* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarTarea(Lista&, const string&, int);
void mostrarLista(const Lista&);
void eliminarTareasPrioridad(Lista&, int);
void vaciarLista(Lista&);
void borrarCabeza(Lista&);
bool verificarLista(const Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0, prioridad;
    string descripcion;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar una tarea\n"
            << "2.- Mostrar lista de tareas\n"
            << "3.- Eliminar tareas por prioridad\n"
            << "4.- Vaciar lista\n"
            << "5.- Salir del programa\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite la descripcion: "; cin >> descripcion;
                cout << "Digite la prioridad: "; cin >> prioridad;
                while(prioridad != 1 && prioridad != 2 && prioridad != 3) {
                    cout << "Digite la prioridad: "; cin >> prioridad;
                }
                agregarTarea(lista,descripcion,prioridad);
                break;
            case 2:
                if(verificarLista(lista)) {
                    cout << "Imprimiendo tareas: ";
                    mostrarLista(lista);
                } else {
                    cout << "Ingrese alguna tarea primero.\n";
                }
                break;
            case 3:
                if(verificarLista(lista)) {
                    cout << "Digite la prioridad: "; cin >> prioridad;
                    while(prioridad != 1 && prioridad != 2 && prioridad != 3) {
                        cout << "Digite la prioridad: "; cin >> prioridad;
                    }
                    eliminarTareasPrioridad(lista, prioridad);
                } else {
                    cout << "Ingrese alguna tarea primero.\n";
                }
                break;
            case 4:
                cout << "Vaciando lista.\n";
                if(!verificarLista(lista)) cout << "Lista vacia.\n";
                else vaciarLista(lista);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                if(verificarLista(lista)) vaciarLista(lista);
                break;
            default:
                cout << "Opcion no disponible.\n";
                break;
        }
        system("pause");
        system("cls");
    } while(opcion != 5);
    return 0;
}

//Definiciones
void agregarTarea(Lista& lista, const string& descripcion, int prioridad) {
    Tarea* nueva = new Tarea{descripcion, prioridad,nullptr};
    if(!lista.cabeza || lista.cabeza->prioridad > prioridad) {
        nueva->siguiente = lista.cabeza;
        lista.cabeza = nueva;
    } else {
        Tarea* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->prioridad <= prioridad) {
            aux = aux->siguiente;
        }
        nueva->siguiente = aux->siguiente;
        aux->siguiente = nueva;
    }
    lista.cantidad++;
    cout << "[" << prioridad << "] " << descripcion << " insertado con exito a la lista.\n";
}

void mostrarLista(const Lista& lista) {
    Tarea* aux = lista.cabeza;
    cout << "Cantidad de tareas en lista: " << lista.cantidad << ".\n";
    while(aux) {
        cout << "[" << aux->prioridad << "] " << aux->descripcion;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarTareasPrioridad(Lista& lista, int prioridad) {
    int borrados = 0;
    while(lista.cabeza->prioridad == prioridad) {
        borrarCabeza(lista);
        borrados++;
    }
    
    if(borrados > 0) {
        cout << "Prioridad eliminada con exito,\n";
        return;
    }

    Tarea* aux = lista.cabeza;
    while(aux && aux->siguiente) {
        if(aux->siguiente->prioridad == prioridad) {
            Tarea* temp = aux->siguiente;
            aux->siguiente = temp->siguiente;
            delete temp;
        } else {
            aux = aux->siguiente;
        }
    }
    (borrados > 0) ? cout << "Prioridad eliminada con exito,\n" : cout << "Prioridad no encontrada.\n";
}

void vaciarLista(Lista& lista) {
    while(lista.cabeza) borrarCabeza(lista);
    lista.cabeza = nullptr;
    lista.cantidad = 0;
    cout << "Lista vaciada con exito.\n";
}

void borrarCabeza(Lista& lista) {
    Tarea* temp = lista.cabeza;
    lista.cabeza = lista.cabeza->siguiente;
    delete temp;
}

bool verificarLista(const Lista& lista) {
    return lista.cabeza != nullptr;
}