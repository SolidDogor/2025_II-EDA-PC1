/*
    Ejercicio 3: Hacer un sistema de cola de banco, donde se insertar clientes al final (orden de llegada)
                    Cada vez que se atienden un cliente, se elimina el primero en lista. Mostrar el cliente
                    atendido y la lista actualizada
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Cliente {
    string nombre;
    int turno;
    Cliente *siguiente;
};

struct Cola {
    Cliente *cabeza = nullptr;
    int cantidad = 1;
};

//Prototipos de funciones
void insertarCliente (Cola &, string);
void atenderCliente (Cola &);
void mostrarClientes (Cola &);
void menu();

Cola cola;

int main () {
    menu();
    return 0;
}

//Definiciones de funciones
void insertarCliente (Cola &cola, string nombre) {
    int turno = cola.cantidad;
    Cliente *nuevo_cliente = new Cliente{nombre, turno, nullptr};
    if (cola.cabeza == NULL || cola.cabeza->turno > turno) {
        nuevo_cliente->siguiente = cola.cabeza;
        cola.cabeza = nuevo_cliente;
    } else {
        Cliente *aux = cola.cabeza;
        while (aux->siguiente && aux->siguiente->turno <= turno) {
            aux = aux->siguiente;
        }
        nuevo_cliente->siguiente = aux->siguiente;
        aux->siguiente = nuevo_cliente;
    }
    cout << "Cliente " << nombre << " esperando en cola con turno " << turno << "\n";
    cola.cantidad++;
}

void atenderCliente (Cola &cola) {
    if(cola.cabeza == nullptr) {
        cout << "Cola vacía!\n";
        return;
    } 
    Cliente *atendido = cola.cabeza;
    cola.cabeza = cola.cabeza->siguiente;
    cout << "Atendiendo a " << atendido->nombre;
    cout << " (turno " << atendido->turno << ")\n";
    delete atendido;
}

void mostrarClientes (Cola &cola) {
    if(cola.cabeza == nullptr) {
        cout << "Cola vacía!\n";
        return;
    } 
    Cliente *p = cola.cabeza;
    while (p) {
        cout << "Cliente: " << p->nombre << " en turno: " << p->turno << "\n";
        p = p->siguiente;
    }
}

void menu () {
    int opcion = 0;
    float val;
    string nom;

    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar cliente\n2.- Mostrar cola\n3.- Atender cliente\n4.- Salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite el nombre: "; cin >> nom;
            insertarCliente(cola, nom);
            cout << "Lista hasta el momento:\n";
            mostrarClientes(cola);
            break;
        case 2:
            cout << "Imprimiendo lista:\n";
            mostrarClientes(cola);
            break;
        case 3:
            cout << "Sacando al primer cliente...\n";
            atenderCliente(cola);
            cout << "Lista restante:\n";
            mostrarClientes(cola);
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