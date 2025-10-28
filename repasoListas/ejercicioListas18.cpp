/*
    Ejercicio 18: Registro de productos por precio (orden ascendente)
        Cada producto tiene un nombre y un precio.
        Se deben insertar ordenados de menor a mayor precio.
        Debe permitir:
            - Agregar producto
            - Mostrar lista completa
            - Vaciar lista
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Producto {
    string nombre;
    float precio;
    Producto* siguiente;
};

struct Lista {
    Producto* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarProducto(Lista&, string&, float);
void mostrarLista(Lista&);
void vaciarLista(Lista&);

//Variables globales?
//Lista lista;

//Main
int main() {
    Lista lista;
    int opcion = 0;
    string nombre;
    float precio = 0.0f;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar producto\n"
            << "2.- Mostrar lista\n"
            << "3.- Vaciar lista\n"
            << "4.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el nombre: "; cin >> nombre;
                cout << "Digite el precio: "; cin >> precio;
                agregarProducto(lista,nombre,precio);
                break;
            case 2:
                mostrarLista(lista);
                break;
            case 3:
                vaciarLista(lista);
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                vaciarLista(lista);
                break;
            default:
                cout << "Opcion no implementada.\n";
        }
        system("pause");
        system("cls");
    } while (opcion !=4);
    return 0;
}

//Definiciones
void agregarProducto(Lista& lista, string& nombre, float precio) {
    Producto* nuevo = new Producto{nombre,precio,nullptr};
    if(!lista.cabeza || lista.cabeza->precio >= precio) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
    } else {
        Producto* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->precio < precio) {
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
    lista.cantidad++;
    cout << nombre << " agregado con exito a la lista.\n";
}

void mostrarLista(Lista& lista) {
    if(!lista.cabeza) {
        cout << "Lista vacia.\n";
        return;
    }
    cout << "Cantidad de productos en lista: " << lista.cantidad << "\n";
    Producto* aux = lista.cabeza;
    while(aux) {
        cout << aux->nombre << " - S/." << aux->precio;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void vaciarLista(Lista& lista) {
    if(!lista.cabeza) {
        cout << "Ingrese algun producto primero.Qn";
        return;
    }
    while(lista.cabeza) {
        Producto* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete aux;
    }
    lista.cantidad = 0;
    cout << "Lista vaciada con exito.\n";
}