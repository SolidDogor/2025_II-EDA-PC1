/*
    Ejercicio 20: Carrito de compras con limpieza por umbral
        Construye un carrito de compras como lista simple.
        Cada ítem tiene nombre y precio.
        Inserta ordenado alfabéticamente por nombre.
        El programa debe permitir:
            - Agregar ítem
            - Mostrar carrito
            - Eliminar un ítem por nombre (primera coincidencia)
            - Eliminar todos los ítems con precio < UMBRAL (limpieza por condición)
            - Vaciar carrito
            - Salir
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Item {
    string nombre;
    float precio;
    Item* siguiente;
};

struct Carrito {
    Item* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarItem(Carrito&, string&,float);
void mostrarCarrito(Carrito&);
void eliminarItemNombre(Carrito&, string&);
void eliminarItemsUmbral(Carrito&, float);
void vaciarCarrito(Carrito&);

//Main
int main() {
    Carrito carrito;
    int opcion = 0;
    string nombre;
    float precio = 0.0f;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar item\n"
            << "2.- Mostrar carrito\n"
            << "3.- Eliminar item (por nombre)\n"
            << "4.- Eliminar item (por umbral de precio)\n"
            << "5.- Vaciar lista\n"
            << "6.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el nombre: "; cin >> nombre;
                cout << "Digite el precio: "; cin >> precio;
                agregarItem(carrito,nombre,precio);
                break;
            case 2:
                mostrarCarrito(carrito);
                break;
            case 3:
                cout << "Digite el nombre: "; cin >> nombre;
                eliminarItemNombre(carrito,nombre);
                break;
            case 4:
                cout << "Digite el umbral de precio: "; cin >> precio;
                eliminarItemsUmbral(carrito,precio);
                break;
            case 5:
                vaciarCarrito(carrito);
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                vaciarCarrito(carrito);
                break;
            default:
                cout << "Opcion no implementada.\n";
        }
        system("pause");
        system("cls");
    } while (opcion != 6);
    return 0;
}

//Definiciones
void agregarItem(Carrito& carrito, string& nombre, float precio) {
    Item* nuevo = new Item{nombre, precio, nullptr};
    if(!carrito.cabeza || carrito.cabeza->nombre > nombre) {
        nuevo->siguiente = carrito.cabeza;
        carrito.cabeza = nuevo;
    } else {
        Item* aux = carrito.cabeza;
        while(aux->siguiente && aux->siguiente->nombre <= nombre){
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
    carrito.cantidad++;
    cout << nombre << " - S/." << precio << " agregado con exito al carrito.\n";
}

void mostrarCarrito(Carrito& carrito) {
    if(!carrito.cabeza) {
        cout << "Carrito vacio.\n";
        return;
    }
    Item* aux = carrito.cabeza;
    cout << "Cantidad de items en carrito: " << carrito.cantidad << "\n";
    while(aux) {
        cout << aux->nombre << " - S/." << aux->precio;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarItemNombre(Carrito& carrito, string& nombre) {
    if(!carrito.cabeza) {
        cout << "Ingrese algun item primero.\n";
        return;
    }
    //Caso 1: El item es el primero en el carrito
    if(carrito.cabeza->nombre == nombre) {
        Item* temp = carrito.cabeza;
        carrito.cabeza = carrito.cabeza->siguiente;
        cout << "Item " << nombre << " eliminado del carrito.\n";
        carrito.cantidad--;
        delete temp;
        return;
    }
    //Caso 2: El item está en el medio o al final
    Item* previo = nullptr;
    Item* actual = carrito.cabeza;
    while(actual && actual->nombre != nombre) {
        previo = actual;
        actual = actual->siguiente;
    }
    if(!actual) {
        cout << "Item " << nombre << " no encontrado.\n";
        return;
    }
    previo->siguiente = actual->siguiente;
    cout << "Item " << nombre << " eliminado del carrito.\n";
    carrito.cantidad--;
    delete actual;
}

void eliminarItemsUmbral(Carrito& carrito, float precio) {
    if (!carrito.cabeza) {
        cout << "Ingrese algun item primero.\n";
        return;
    }
    int borrados = 0;
    //Caso 1: Las cabezas son menores
    while (carrito.cabeza && carrito.cabeza->precio < precio) {
        Item* t = carrito.cabeza;
        carrito.cabeza = carrito.cabeza->siguiente;
        delete t;
        carrito.cantidad--;
        borrados++;
    }
    //Caso 2: Se elimina en cualquier orden
    Item* prev = carrito.cabeza;
    while (prev && prev->siguiente) {
        if (prev->siguiente->precio < precio) {
            Item* t = prev->siguiente;
            prev->siguiente = t->siguiente;
            delete t;
            carrito.cantidad--;
            borrados++;
        } else {
            prev = prev->siguiente;
        }
    }

    cout << "Eliminacion completa. Items borrados: " << borrados << "\n";
}


void vaciarCarrito(Carrito& carrito) {
    if(!carrito.cabeza){
        cout << "Carrito vacio.\n";
        return;
    }
    while(carrito.cabeza) {
        Item* temp = carrito.cabeza;
        carrito.cabeza = carrito.cabeza->siguiente;
        delete temp;
    }
    carrito.cantidad = 0;
    cout << "Carrito vaciado con exito.\n";
}
