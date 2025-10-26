/*
    Ejercicio 7: Cola de clientes del banco
    Cada cliente llega y se encola al final.
    Cuando se atiende, se elimina el primero (frente).
    Debe poder:
        Agregar cliente
        Mostrar cola
        Atender (eliminar frente)
        Vaciar cola
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Cliente {
    string nombre;
    int turno;
    Cliente* siguiente;
};

struct Cola {
    Cliente* frente = nullptr;
    Cliente* final = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarCliente(Cola&,string&);
void mostrarCola(Cola&);
void atenderCliente(Cola&);
void vaciarCola(Cola&);

//Variables globales
Cola cola;
int turno = 1;

//Main
int main() {
    int opcion = 0;
	string nombre;
	do {
		cout << "1.- Agregar cliente a la cola\n2.- Mostrar cola de clientes\n"
			<< "3.- Atender cliente\n4.- Eliminar cola\n"
            << "5.- Salir\n> ";
		cin >> opcion;
		switch (opcion) {
			case 1:
				cout << "Digite el nombre del cliente: "; cin >> nombre;
				agregarCliente(cola,nombre);
				break;
			case 2:
				cout << "Mostrando cola de clientes:\n";
				mostrarCola(cola);
				break;
			case 3:
				atenderCliente(cola);
				break;
			case 4:
				vaciarCola(cola);
				break;
			case 5:
				cout << "Saliendo del programa...\n";
				break;
			default:
				cout << "Opcion no disponible!\n";
				break;
		}
		system("pause");
		system("cls");
	} while (opcion != 5);
	return 0;
}

//Definiciones
void agregarCliente(Cola& cola,string& nombre) {
    Cliente* nuevo = new Cliente{nombre, turno, nullptr};
    if(!cola.frente) {
        nuevo->siguiente = cola.frente = cola.final;
        cola.frente = cola.final = nuevo;
    } else {
        cola.final->siguiente = nuevo;
        cola.final = nuevo;
    }
    cola.cantidad++;
    cout << nombre << " agregado a la cola con turno " << turno++ << ".\n";
}

void mostrarCola(Cola& cola) {
    if(!cola.final) {
        cout << "No hay clientes en cola.\n";
        return;
    }
    Cliente* aux = cola.frente;
    while(aux) {
        cout << "[" << aux-> turno << "] " << aux->nombre << "\n";
        aux = aux->siguiente;
    }
}

void atenderCliente(Cola& cola) {
    if(!cola.frente) {
        cout << "No hay clientes en cola.\n";
        return;
    }
    Cliente* aux = cola.frente;
    (!aux->siguiente) ? cola.frente = cola.final = nullptr : cola.frente = cola.frente->siguiente;
    cola.cantidad--;
    cout << aux->nombre << " atentido con exito.\n";
    delete aux;
}

void vaciarCola(Cola& cola) {
    if(!cola.frente) {
        cout << "No hay clientes en cola.\n";
        return;
    }
    while(cola.frente) {
        Cliente* aux = cola.frente;
        (!aux->siguiente) ? cola.frente = cola.final = nullptr : cola.frente = cola.frente->siguiente;
        delete aux;
    }
    cola.cantidad = 0;
    turno = 1;
    cout << "Cola vaciada con exito.\n";
}