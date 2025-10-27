/*
    Ejercicio 8: Cola de pedidos de restaurante
        Cada pedido llega con un número autoincremental y se encola.
        El primero en llegar es el primero en ser atendido.
        Debe permitir:
            Agregar pedido
            Mostrar todos los pedidos pendientes
            Atender pedido (eliminar el primero)
            Vaciar la cola
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Pedido {
    int turno;
    string plato;
    Pedido* siguiente;
};

struct Cola {
    Pedido* frente = nullptr;
    Pedido* final = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarPedido(Cola&,string&);
void mostrarCola(Cola&);
void atenderPedido(Cola&);
void vaciarCola(Cola&);

//Variables globales
Cola cola;
int turno = 1;

//Main
int main() {
    int opcion = 0;
    string plato;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar pedido\n"
            << "2.- Mostrar cola\n"
            << "3.- Atender pedido\n"
            << "4.- Vaciar cola\n"
            << "5.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el plato: "; cin >> plato;
                agregarPedido(cola,plato);
                break;
            case 2:
                cout << "Mostrando cola:\n";
                mostrarCola(cola);
                break;
            case 3:
                atenderPedido(cola);
                break;
            case 4:
                vaciarCola(cola);
                break;
            case 5:
                vaciarCola(cola);
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no disponible.\n";
                break;
        }
        system("pause");
        system("cls");
    } while (opcion != 5);
    return 0;
}

//Definiciones
void agregarPedido(Cola& cola,string& plato) {
    Pedido* nuevo = new Pedido{turno,plato,nullptr};
    if(!cola.final) {
        nuevo->siguiente = cola.final;
        cola.final = cola.frente = nuevo;
    } else {
        cola.final->siguiente = nuevo;
        cola.final = nuevo;
    }
    cola.cantidad++;
    cout << plato << " (turno " << turno++ << ") agregado con exito a la cola.\n";
}

void mostrarCola(Cola& cola) {
    if(!cola.frente){
        cout << "Cola vacia.\n";
        return;
    }
    Pedido* aux = cola.frente;
    while(aux) {
        cout << aux->turno << ": " << aux->plato;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void atenderPedido(Cola& cola) {
    if(!cola.frente){
        cout << "Ingrese algun pedido primero.\n";
        return;
    }
    Pedido* aux = cola.frente;
    cola.frente = cola.frente->siguiente;
    cout << aux->plato << " atendido.\n";
    cola.cantidad--;
    delete aux;
}

void vaciarCola(Cola& cola) {
    if(!cola.frente){
        cout << "Cola vacia.\n";
        return;
    }
    while(cola.frente) {
        Pedido* aux = cola.frente;
        cola.frente = cola.frente->siguiente;
        delete aux;
    }
    cola.frente = cola.final = nullptr;
    cola.cantidad = 0;
    turno = 1;
    cout << "Cola vaciada con exito.\n";
}
