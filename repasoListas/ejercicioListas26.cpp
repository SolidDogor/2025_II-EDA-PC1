/*
    Ejercicio 26 – Eliminar todos los negativos
        Tema: Eliminación múltiple (todos los que cumplan condición)
        Estructura: Lista simple de enteros
        Instrucciones:
            - Usa una lista con valores positivos y negativos.
            - Implementa eliminarNegativos(Lista&) que:
                - Elimine todos los nodos con dato < 0.
                - Tenga cuidado con los que estén al inicio.
                - Muestra cuántos elementos fueron eliminados.
*/
#include <iostream>
using namespace std;

//Estructuras
struct Nodo {
    int dato;
    Nodo* siguiente;
};

struct Lista {
    Nodo* cabeza = nullptr;
    int cantidad = 0;
    bool negativos = false;
};

//Prototipado
void agregarNodo(Lista&, int);
void mostrarLista(Lista&);
void eliminarNegativos(Lista&);
void vaciarLista(Lista&);
bool verificarLista(Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0, dato;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar dato\n"
            << "2.- Eliminar negativos en lista\n"
            << "3.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el dato: "; cin >> dato;
                agregarNodo(lista,dato);
                break;
            case 2:
                if(verificarLista(lista)) eliminarNegativos(lista);
                else cout << "Ingrese algun valor primero.\n";
                break;
            case 3:
                if(verificarLista(lista)) vaciarLista(lista);
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
        system("pause");
        system("cls");
    } while(opcion != 3);
    return 0;
}

//Definiciones
void agregarNodo(Lista& lista, int dato) {
    Nodo* nuevo = new Nodo{dato,nullptr};
    nuevo->siguiente = lista.cabeza;
    lista.cabeza = nuevo;
    lista.cantidad++;
    cout << dato << " agregado con exito a la lista.\n";
    cout << "Imprimiendo lista actual: "; mostrarLista(lista);
    if(dato < 0) lista.negativos = true;
}

void mostrarLista(Lista& lista) {
    Nodo* aux = lista.cabeza;
    cout << "Cantidad de datos en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << aux->dato;
        (aux->siguiente) ? cout << " - " : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarNegativos(Lista& lista) {
    if(!lista.negativos) {
        cout << "No hay negativos en lista.\n";
        return;
    }
    cout << "Imprimiendo lista actual: "; mostrarLista(lista);
    int borrados = 0;
    while(lista.cabeza->dato < 0) {
        Nodo* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        cout << aux->dato << " eliminado de lista.\n";
        delete aux;
        lista.cantidad--;
        borrados++;
    }
    Nodo* previo = lista.cabeza;
    while(previo->siguiente) {
        if(previo->siguiente->dato < 0) {
            Nodo* aux = previo->siguiente;
            previo->siguiente = aux->siguiente;
            cout << aux->dato << " eliminado de lista.\n";
            delete aux;
            lista.cantidad--;
            borrados++;
        } else {
            previo = previo->siguiente;
        }
    }
    if(borrados > 0) {
        cout << "Imprimiendo lista actual: "; mostrarLista(lista);
        lista.negativos = false;
    } else {
        cout << "No se encontraron negativos.\n";
    }
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

bool verificarLista(Lista& lista) {
    return lista.cabeza != nullptr;
}
