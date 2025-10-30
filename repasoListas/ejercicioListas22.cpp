/*
    Ejercicio 22: Eliminación básica por valor
        Crea una lista simple de números enteros.
        Implementa las funciones:
            - insertar al final (orden de inserción)
            - mostrar lista
            - eliminar el primer nodo que contenga un valor dado
            - vaciar lista
        Prueba todos los casos:
            a) Eliminar el primer nodo
            b) Eliminar uno intermedio
            c) Eliminar el último
            d) Intentar eliminar un valor que no existe
*/
#include <iostream>
using namespace std;

//Estructuras
struct Nodo {
    int valor;
    Nodo* siguiente;
};

struct Lista {
    Nodo* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void insertarNodo(Lista&, int);
void mostrarLista(const Lista&);
void eliminarNodo(Lista&, int);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0, dato;
    do {
        cout << "\t---MENU---"
            << "\n1.- Insertar valor"
            << "\n2.- Mostrar lista"
            << "\n3.- Eliminar valor"
            << "\n4.- Vaciar lista"
            << "\n5.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el valor: "; cin >> dato;
                insertarNodo(lista,dato);
                break;
            case 2:
                cout << "Mostrando lista:\n";
                if(verificarLista(lista)) mostrarLista(lista);
                else cout << "Lista vacia.\n";
                break;
            case 3:
                cout << "Digite el valor: "; cin >> dato;
                if(verificarLista(lista)) eliminarNodo(lista, dato);
                else cout << "Inserte algun valor primero.\n";
                break;
            case 4:
                if(verificarLista(lista)) vaciarLista(lista);
                else cout << "Inserte algun valor primero.\n";
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
void insertarNodo(Lista& lista, int valor) {
    Nodo* nuevo = new Nodo{valor,nullptr};
    nuevo->siguiente = lista.cabeza;
    lista.cabeza = nuevo;
    cout << valor << " agregado con exito a la lista.\n";
    lista.cantidad++;
}

void mostrarLista(const Lista& lista) {
    Nodo* aux = lista.cabeza;
    cout << "Cantidad de valores en lista: " << lista.cantidad << "\n";
    while (aux) {
        cout << aux-> valor;
        (aux->siguiente) ? cout << " - " : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarNodo(Lista& lista, int valor) {
    if(lista.cabeza->valor == valor) {
        Nodo* temp = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        cout << valor << " eliminado de lista.\n";
        delete temp;
        lista.cantidad--;
        return;
    }
    Nodo* previo = lista.cabeza;
    while(previo && previo->siguiente->valor != valor) {
        previo = previo->siguiente;
    }
    if(!previo) {
        cout << "No se encontró el valor.\n";
        return;
    }
    Nodo* temp = previo->siguiente;
    previo->siguiente = temp->siguiente;
    cout << temp->valor << " eliminado de lista.\n";
    delete temp;
    lista.cantidad--;
}

void vaciarLista(Lista& lista) {
    while(lista.cabeza) {
        Nodo* temp = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete temp;
    }
    lista.cabeza = nullptr;
    lista.cantidad = 0;
    cout << "Lista vaciada con exito.\n";
}

bool verificarLista(const Lista& lista) {
    return lista.cabeza != nullptr;
}
