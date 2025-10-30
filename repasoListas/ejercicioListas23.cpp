/*
    Ejercicio 23: Eliminación múltiple con condición
        Crea una lista simple donde cada nodo representa un empleado:
            - nombre (string)
            - sueldo (float)
        Se debe poder:
            - insertar empleados (orden alfabetico)
            - mostrar lista
            - eliminar todos los empleados con sueldo < UMBRAL dado
            - vaciar lista
*/
#include <iostream>
#include <string>
#include <limits>
using namespace std;

//Estructuras
struct Empleado {
    string nombre;
    float sueldo;
    Empleado* siguiente;
};

struct Lista {
    Empleado* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void insertarEmpleado(Lista&, const string&, float);
void mostrarLista(const Lista&);
void eliminarSueldo(Lista&, float);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0;
    string nombre;
    float sueldo = 0.0f;
    do {
        cout << "\t---MENU---"
            << "\n1.- Insertar empleado"
            << "\n2.- Mostrar lista"
            << "\n3.- Eliminar empleados (por umbral de sueldo)"
            << "\n4.- Vaciar lista"
            << "\n5.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el nombre: "; cin >> nombre;
                cout << "Digite el sueldo: "; cin >> sueldo;
                insertarEmpleado(lista,nombre,sueldo);
                break;
            case 2:
                cout << "Mostrando lista:\n";
                if(verificarLista(lista)) mostrarLista(lista);
                else cout << "Lista vacia.\n";
                break;
            case 3:
                cout << "Digite el sueldo: "; cin >> sueldo;
                if(verificarLista(lista)) eliminarSueldo(lista, sueldo);
                else cout << "Inserte algun empleado primero.\n";
                break;
            case 4:
                if(verificarLista(lista)) vaciarLista(lista);
                else cout << "Inserte algun empleado primero.\n";
                break;
            case 5:
                vaciarLista(lista);
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no implementada.\n";
        }
        system("pause");
        system("cls");
    } while (opcion != 5);
    return 0;
}

//Definiciones
void insertarEmpleado(Lista& lista, const string& nombre, float sueldo) {
    Empleado* nuevo = new Empleado{nombre,sueldo,nullptr};
    if(!lista.cabeza || lista.cabeza->nombre > nombre) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
    } else {
        Empleado* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->nombre <= nombre) {
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
    cout << "[" << nombre << " - S/." << sueldo << "] agregado con exito a la lista.\n";
    lista.cantidad++;
}

void mostrarLista(const Lista& lista) {
    Empleado* aux = lista.cabeza;
    cout << "Cantidad de empleados en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << "[" << aux->nombre << " - S/." << aux->sueldo << "]";
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarSueldo(Lista& lista, float sueldo) {
    cout << "Cantidad de empleados iniciales: " << lista.cantidad << ".\n";
    while(lista.cabeza->sueldo < sueldo) {
        Empleado* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        lista.cantidad--;
        delete aux;
    }
    Empleado* previo = lista.cabeza;
    while(previo && previo->siguiente) {
        if(previo->siguiente->sueldo < sueldo) {
            Empleado* aux = previo->siguiente;
            previo->siguiente = aux->siguiente;
            lista.cantidad--;
            delete aux;
        } else {
            previo = previo->siguiente;
        }
    }
    cout << "Cantidad de empleados restantes: " << lista.cantidad << ".\n";
}

void vaciarLista(Lista& lista) {
    while(lista.cabeza) {
        Empleado* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete aux;
    }
    lista.cabeza = nullptr;
    lista.cantidad = 0;
    cout << "Lista vaciada con exito.\n";
}

bool verificarLista(const Lista& lista) {
    return lista.cabeza != nullptr;
}
