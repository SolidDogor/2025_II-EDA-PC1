/*
    Ejercicio 33 – Lista simple de cafes favoritos
    Cada cafe tiene:
        - nombre (string)
        - tamaño en onzas (int)
    Funciones:
        - Agregar café al final
        - Mostrar lista
        - Mostrar cantidad total de cafés
        - Vaciar lista
        - Salir
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Cafe {
    string nombre;
    int onzas;
    Cafe* siguiente;
};

struct Lista {
    Cafe* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarCafe(Lista&, const string&, int);
void mostrarLista(const Lista&);
void mostrarCantidad(const Lista&);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0, onzas;
    string nombre;
    do {
        cout << "\t---MENU---"
            << "\n1.- Agregar cafe"
            << "\n2.- Mostrar lista"
            << "\n3.- Mostrar cantidad"
            << "\n4.- Vaciar lista"
            << "\n5.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el nombre: "; cin >> nombre;
                cout << "Digite la cantidad de onzas: "; cin >> onzas;
                agregarCafe(lista,nombre,onzas);
                break;
            case 2:
                if(verificarLista(lista)) mostrarLista(lista);
                else cout << "Agregue cafes primero.\n";
                break;
            case 3:
                if(verificarLista(lista)) mostrarCantidad(lista);
                else cout << "Agregue cafes primero.\n";
                break;
            case 4:
                if(verificarLista(lista)) vaciarLista(lista);
                else cout << "Lista vacia.\n";
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                if(verificarLista(lista)) vaciarLista(lista);
                break;
            default:
                cout << "Opcion no disponible.\n";
        }
        system("pause");
        system("cls");
    } while(opcion != 5);
    return 0;
}

//Definiciones
void agregarCafe(Lista& lista, const string& nombre, int onzas) {
    Cafe* nuevo = new Cafe{nombre,onzas,nullptr};
    nuevo->siguiente = lista.cabeza;
    lista.cabeza = nuevo;
    lista.cantidad++;
    cout << nombre << " agregado con exito a la lista.\n";
}

void mostrarLista(const Lista& lista) {
    Cafe* aux = lista.cabeza;
    
    while(aux) {
        cout << aux->nombre << " [Onzas: " << aux->onzas << "]";
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void mostrarCantidad(const Lista& lista) {
    cout << "Cantidad de cafes en lista: " << lista.cantidad << "\n";
}

void vaciarLista(Lista& lista) {
    while(lista.cabeza) {
        Cafe* temp = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete temp;
    }
    lista.cantidad = 0;
    lista.cabeza = nullptr;
    cout << "Lista vaciada con exito.\n";
}

bool verificarLista(const Lista& lista) {
    return lista.cabeza != nullptr;
}
