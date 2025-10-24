/*
    Ejercicio 12: Lista de libros
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Libro {
    int id;
    string titulo;
    float precio;
    Libro* siguiente;
};

struct Lista {
    Libro* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarLibro(Lista&, string&, float);
void mostrarLista(Lista&);
void eliminarLibro(Lista&, string&);
void eliminarLista(Lista&);
void menu();

//Variables globales
Lista lista;
int id = 1;

//Main
int main() {
    menu();
    return 0;
}

//Definiciones
void agregarLibro(Lista& lista, string& nombre, float precio) {
    Libro* nuevoLibro = new Libro{id, nombre, precio, nullptr};
    if(!lista.cabeza || lista.cabeza->titulo > nombre) {
        nuevoLibro->siguiente = lista.cabeza;
        lista.cabeza = nuevoLibro;
    } else {
        Libro* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->titulo <= nombre) aux = aux->siguiente;
        nuevoLibro->siguiente = aux->siguiente;
        aux->siguiente = nuevoLibro;
    }
    lista.cantidad++;
    id++;
    cout << nombre << " agregado con exito a la lista!\n";
}

void mostrarLista(Lista& lista) {
    Libro* p = lista.cabeza;
    if(!p) {
        cout << "Lista vacia.\n";
        return;
    }

    while(p) {
        cout << "Libro #" << p->id << ": " << p->titulo << " (S/." << p->precio << ")\n";
        p = p->siguiente;
    }
}

void eliminarLibro(Lista& lista, string& nombre) {
    Libro* p = lista.cabeza;
    if(!p) {
        cout << "No hay libros en lista\n";
        return;
    }

    if (lista.cabeza->titulo == nombre) {
        Libro* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete aux;
        lista.cantidad--;
        cout << "Libro '" << nombre << "' eliminado.\n";
        return;
    }

    Libro* previo = lista.cabeza;
    Libro* actual  = lista.cabeza->siguiente;
    while (actual && actual->titulo != nombre) {
            previo = actual;
            actual = actual->siguiente;
    }
    if (!actual) {
        cout << "No existe el libro '" << nombre << "'.\n";
        return;
    }

    previo->siguiente = actual->siguiente;
    delete actual;
    lista.cantidad--;
    cout << "Libro '" << nombre << "' eliminado.\n";
}

void eliminarLista(Lista& lista) {
    if(!lista.cabeza) {
        cout << "No hay libros en lista\n";
        return;
    }

    Libro* aux = lista.cabeza;
    while (aux) {
        Libro* temp = aux;
        aux = aux->siguiente;
        delete temp;
    }
    lista.cabeza = nullptr;
    lista.cantidad = 0;
    id = 1;
    cout << "Lista completa eliminada.\n";
}

void menu() {
    int opcion = 0;
    float monto = 0.0f;
    string nombre;

    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar libro\n2.- Mostrar lista\n3.- Eliminar libro\n";
        cout << "4.- Eliminar lista\n5.- Salir\n> ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Nombre: "; cin >> nombre;
                cout << "Precio: "; cin >> monto;
                agregarLibro(lista, nombre, monto);
                break;
            case 2:
                cout << "Mostrando lista:\n";
                mostrarLista(lista);
                break;
            case 3:
                cout << "Nombre: "; cin >> nombre;
                eliminarLibro(lista, nombre);
                break;
            case 4:
                cout << "Eliminando lista...\n";
                eliminarLista(lista);
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