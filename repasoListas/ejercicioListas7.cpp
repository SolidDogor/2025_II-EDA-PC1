/*
    Ejercicio 7: Eliminar un producto especifico dentro de un inventario de productos
                    Cada producto tiene un nombre y un precio. Se debe insertar productos ordenados por 
                    nombre o precio. Permitir eliminar un producto ingresando su nombre
                    Mostrar mensaje si el producto no existe.
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Producto {
    string nombre;
    float precio;
    Producto *siguiente;
};

struct Inventario {
    Producto *cabeza = nullptr;
    int cantidad = 0;
};

//Prototipado de funciones
void agregarProducto(Inventario &, string, float);
void eliminarProducto(Inventario &, string);
void mostrarInventario(Inventario &);
void menu();

//Variables globales
Inventario inventario;

int main() {
    menu();
    return 0;
}

//Definiciones de funciones
void agregarProducto(Inventario &inventario, string nombre, float precio) {
    Producto *nuevo_producto = new Producto{nombre, precio, nullptr};
    if (inventario.cabeza == NULL || inventario.cabeza->precio > precio) {
        nuevo_producto->siguiente = inventario.cabeza;
        inventario.cabeza = nuevo_producto;
    } else {
        Producto *aux = inventario.cabeza;
        while(aux->siguiente && aux->siguiente->precio <= precio) {
            aux = aux->siguiente;
        }
        nuevo_producto->siguiente = aux->siguiente;
        aux->siguiente = nuevo_producto;
    }

    cout << "Producto: " << nombre << " (precio: S/." << precio << ") agregado con exito al inventario.\n";
    inventario.cantidad++;
}

void eliminarProducto(Inventario &inventario, string nombre) {
    if (!inventario.cabeza) {
        cout << "Inventario vacio! Ingrese algun producto primero.\n";
        return;
    }

    //Caso 1: el primero es el que quiero borrar
    if (inventario.cabeza->nombre == nombre) {
        Producto *borrar = inventario.cabeza;
        inventario.cabeza = inventario.cabeza->siguiente;
        cout << "Producto: " << borrar->nombre << " (precio: S/." << borrar->precio
            << ") eliminado con exito del inventario.\n";
        delete borrar;
        inventario.cantidad--;
        return;
    }

    //Caso 2: buscar en el resto (necesitamos 'prev' y 'curr')
    Producto *prev = inventario.cabeza;
    Producto *curr = inventario.cabeza->siguiente;

    while (curr && curr->nombre != nombre) {
        prev = curr;
        curr = curr->siguiente;
    }

    if (!curr) {
        cout << "No se encontro el producto '" << nombre << "'.\n";
        return;
    }

    //Desenganchar y borrar
    prev->siguiente = curr->siguiente;
    cout << "Producto: " << curr->nombre << " (precio: S/." << curr->precio
        << ") eliminado con exito del inventario.\n";
    delete curr;
    inventario.cantidad--;
}


void mostrarInventario(Inventario &inventario) {
    if (inventario.cabeza == nullptr) {
        cout << "Inventario vacio! Ingrese algun producto primero.\n";
        return;
    }
    Producto *p = inventario.cabeza;
    while (p) {
        cout << "Producto: " << p->nombre;
        cout << " (precio: S/." << p->precio << ")\n";
        p = p->siguiente;
    }
}

void menu() {
    int opcion = 0;
    float precio;
    string nombre;

    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar producto\n2.- Mostrar inventario\n3.- Eliminar producto\n4.- Salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite el nombre del producto: "; cin >> nombre;
            cout << "Digite el precio del producto: "; cin >> precio;
            agregarProducto(inventario, nombre, precio);
            cout << "Lista hasta el momento:\n";
            mostrarInventario(inventario);
            break;
        case 2:
            cout << "Imprimiendo inventario:\n";
            mostrarInventario(inventario);
            break;
        case 3:
            cout << "Digite el nombre del producto a eliminar: "; cin >> nombre;
            eliminarProducto(inventario, nombre);
            cout << "Lista restante:\n";
            mostrarInventario(inventario);
            break;
        case 4:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion no disponible!\n";
            break;
        }

        system("pause");
        system("cls");

    } while (opcion != 4);
}