/*
    Ejercicio 19: Inventario con eliminación por nombre
        Queremos administrar un pequeño inventario de productos.
        Cada producto tiene un nombre y un precio.
        Los productos se insertan ordenados por nombre (ascendente).
        El programa debe permitir:
            - Agregar producto
            - Mostrar lista completa
            - Eliminar producto por nombre
            - Vaciar lista
            - Salir
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
void agregarProducto(Lista&, string&,float);
void mostrarLista(Lista&);
void eliminarProductoNombre(Lista&, string&);
void vaciarLista(Lista&);

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
            << "3.- Eliminar producto (por nombre)\n"
            << "4.- Vaciar lista\n"
            << "5.- Salir\n> ";
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
                cout << "Digite el nombre: "; cin >> nombre;
                eliminarProductoNombre(lista,nombre);
                break;
            case 4:
                vaciarLista(lista);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                vaciarLista(lista);
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
void agregarProducto(Lista& lista, string& nombre, float precio) {
    Producto* nuevo = new Producto{nombre,precio,nullptr};
    if(!lista.cabeza || lista.cabeza->nombre > nombre) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
    } else {
        Producto* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->nombre <= nombre) {
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
    lista.cantidad++;
    cout << nombre << " - S/." << precio << " agregado con exito a la lista.\n";
}

void mostrarLista(Lista& lista) {
    if(!lista.cabeza){
        cout << "Lista vacia.\n";
        return;
    }
    Producto* aux = lista.cabeza;
    cout << "Cantidad de productos en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << aux->nombre << " - S/." << aux->precio;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarProductoNombre(Lista& lista, string& nombre) {
    if(!lista.cabeza){
        cout << "Ingrese algun producto primero.\n";
        return;
    }
    Producto* previo = nullptr;
    Producto* actual = lista.cabeza;
    //Caso 1: El producto es el primero en lista
    if(actual->nombre == nombre) {
        lista.cabeza = lista.cabeza->siguiente;
        cout << "Producto eliminado.\n";
        lista.cantidad--;
        delete actual;
        return;
    }
    //Caso 2: El producto está en el medio o al final
    while(actual->siguiente && actual->nombre != nombre) {
        previo = actual;
        actual = actual->siguiente;
    }
    if(actual->nombre != nombre) {
        cout << "Nombre no encontrado.\n";
        return;
    } else {
        previo->siguiente = actual->siguiente;
        cout << "Producto eliminado.\n";
        lista.cantidad--;
        delete actual;
    }
}

void vaciarLista(Lista& lista) {
    if(!lista.cabeza){
        cout << "Lista vacia.\n";
        return;
    }
    while(lista.cabeza) {
        Producto* temp = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete temp;
    }
    lista.cantidad = 0;
    cout << "Lista vaciada con exito.\n";
}
