/*
    Ejercicio 24: Eliminación compuesta con reutilización
        Implementa una lista simple de productos con:
            - nombre (string)
            - precio (float)
            - categoría (string)

        Debe permitir:
            - insertar ordenado alfabéticamente por nombre
            - mostrar lista
            - eliminar un producto por nombre
            - eliminar todos los productos de una categoría
            - vaciar lista
            
        Usa funciones reutilizables
*/
#include <iostream>
#include <string>
#include <limits>
using namespace std;

//Estructuras
struct Producto {
    string nombre;
    float precio;
    string categoria;
    Producto* siguiente;
};

struct Lista{
    Producto* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void insertarProducto(Lista&, const string&, float, const string&);
void mostrarLista(const Lista&);
void eliminarProductoNombre(Lista&, const string&);
void eliminarProductoCategoria(Lista&, const string&);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);
void borrarCabeza(Lista&);
void borrarProducto(Lista&, Producto*);

//Main
int main() {
    Lista lista;
    int opcion = 0;
    string nombre, categoria;
    float precio = 0.0f;
    do {
        cout << "\t---MENU---"
            << "\n1.- Insertar producto"
            << "\n2.- Mostrar lista"
            << "\n3.- Eliminar producto (por nombre)"
            << "\n4.- Eliminar categoria"
            << "\n5.- Vaciar lista"
            << "\n6.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Precio: "; cin >> precio;
                fflush(stdin);
                cout << "Categoria: "; getline(cin, categoria);
                insertarProducto(lista,nombre,precio,categoria);
                break;
            case 2:
                cout << "Mostrando lista:\n";
                if(verificarLista(lista)) mostrarLista(lista);
                else cout << "Lista vacia.\n";
                break;
            case 3:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Nombre: "; getline(cin, nombre);
                if(verificarLista(lista)) eliminarProductoNombre(lista, nombre);
                else cout << "Inserte algun producto primero.\n";
                break;
            case 4:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Categoria: "; getline(cin, categoria);
                if(verificarLista(lista)) eliminarProductoCategoria(lista, categoria);
                else cout << "Inserte algun producto primero.\n";
                break;
            case 5:
                if(verificarLista(lista)) vaciarLista(lista);
                else cout << "Inserte algun producto primero.\n";
                break;
            case 6:
                vaciarLista(lista);
                cout << "Saliendo del programa...\n";
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
void insertarProducto(Lista& lista, const string& nombre, float precio, const string& categoria) {
    Producto* nuevo = new Producto{nombre,precio,categoria,nullptr};
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
    cout << "[" << categoria << "] " << nombre << " - S/." << precio 
        << " agregado con exito a la lista.\n";
    lista.cantidad++;
}

void mostrarLista(const Lista& lista) {
    Producto* aux = lista.cabeza;
    cout << "Cantidad de productos en lista: " << lista.cantidad << ".\n";
    while(aux) {
        cout << "[" << aux->categoria << "] " << aux->nombre << " - S/." << aux->precio;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarProductoNombre(Lista& lista, const string& nombre) {
    if(lista.cabeza->nombre == nombre) {
        borrarCabeza(lista);
        cout << nombre << " eliminado con exito de la lista.\n";
        return;
    }
    Producto* previo = lista.cabeza;
    while(previo->siguiente && previo->siguiente->nombre != nombre) {
        previo = previo->siguiente;
    }
    if(!previo) {
        cout << nombre << " no se encuentra en lista.\n";
        return;
    }
    borrarProducto(lista,previo);
    cout << nombre << " eliminado con exito de la lista.\n";
}

void eliminarProductoCategoria(Lista& lista, const string& categoria) {
    int cantidadBorrada = 0;
    while(lista.cabeza->categoria == categoria) {
        borrarCabeza(lista);
        cantidadBorrada++;
    }
    Producto* previo = lista.cabeza;
    while(previo && previo->siguiente) {
        if(previo->siguiente->categoria == categoria) {
            borrarProducto(lista,previo);
            cantidadBorrada++;
        } else {
            previo = previo->siguiente;
        }
    }
    if (cantidadBorrada != 0) {
        cout << "Categoria: " << categoria << " eliminada con exito de la lista.\n";
    }else {
        cout << "No se encontro esa categoria.\n";
    }
}

void vaciarLista(Lista& lista) {
    while(lista.cabeza) borrarCabeza(lista);
    lista.cabeza = nullptr;
    lista.cantidad = 0;
    cout << "Lista vaciada con exito.\n";
}

bool verificarLista(const Lista& lista) {
    return lista.cabeza != nullptr;
}

void borrarCabeza(Lista& lista) {
    Producto* temp = lista.cabeza;
    lista.cabeza = lista.cabeza->siguiente;
    delete temp;
    lista.cantidad--;
}

void borrarProducto(Lista& lista, Producto* previo) {
    if(!previo->siguiente) return;
    Producto* temp = previo->siguiente;
    previo->siguiente = temp->siguiente;
    delete temp;
    lista.cantidad--;
}
