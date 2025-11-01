/*
    Ejercicio 25 – Eliminar el primer número par
    Tema: Eliminar un solo elemento según una condición simple
    Estructura: lista simple de enteros
    Instrucciones:
        - Crea una lista simple (struct Nodo { int dato; Nodo* sig; })
        - Permite insertar números al final.
        - Crea una función eliminarPrimerPar(Lista&) que:
            - Elimine solo el primer número par que encuentre.
            - Si no hay pares, muestra un mensaje.
            - Muestra la lista antes y después.
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Nodo {
    int dato;
    Nodo* siguiente;
};

struct Lista {
    Nodo* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarNodo(Lista&, int);
void mostrarLista(Lista&);
void eliminarPrimerPar(Lista&);
void vaciarLista(Lista&);
bool verificarLista(Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0, dato;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar dato\n"
            << "2.- Eliminar primer par en lista\n"
            << "3.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el dato: "; cin >> dato;
                agregarNodo(lista,dato);
                break;
            case 2:
                if(verificarLista(lista)) eliminarPrimerPar(lista);
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

void eliminarPrimerPar(Lista& lista) {
    int posicion = 1;
    if(lista.cabeza->dato % 2 == 0) {
        cout << "Imprimiendo lista actual: "; mostrarLista(lista);
        Nodo* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        cout << aux->dato << " eliminado de lista en posicion " << posicion << ".\n";
        delete aux;
        lista.cantidad--;
        cout << "Imprimiendo lista actual: "; mostrarLista(lista);
        return;
    }
    posicion++;
    Nodo* previo = lista.cabeza;
    while(previo->siguiente && previo->siguiente->dato % 2 != 0) {
        previo = previo->siguiente;
        posicion++;
    }
    if(!previo->siguiente || previo->siguiente->dato % 2 != 0) {
        cout << "No se encontraron pares en lista.\n";
        return;
    }
    cout << "Imprimiendo lista actual: "; mostrarLista(lista);
    Nodo* aux = previo->siguiente;
    previo->siguiente = aux->siguiente;
    cout << aux->dato << " eliminado de lista en posicion " << posicion << ".\n";
    delete aux;
    lista.cantidad--;
    cout << "Imprimiendo lista actual: "; mostrarLista(lista);
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
