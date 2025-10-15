/*
	Ejercicio 5: Insertar 6 pasajeros con distintas prioridades (1 = VIP, 2 = normal, 3 = lista de espera)
			Verificar que los VIP estén al inicio
			Insertar un nuevo pasajero con prioridad 1 y observar si sube al tope
*/
#include <iostream>
#include <string>
using namespace std;

enum Prioridad {
    VIP = 1,
    NORMAL = 2,
    ESPERA = 3
};

struct Pasajero {
    string nombre;
    Prioridad prioridad;
    Pasajero *siguiente;
};

struct Lista {
    Pasajero *cabeza = nullptr;
    int cantidad = 0;
};

//Prototipo de funcion
void insertarPasajero(Lista &, string, Prioridad);
string prioridadToString(Prioridad);
void mostrarLista(const Lista &);

int main() {
	Lista lista;

	int cantidad = 6, prioridad;
	string nombre;

	while(cantidad--) {
		cout << "Digite el nombre del pasajero: "; cin >> nombre;
		cout << "Digite la prioridad del pasajero: "; cin >> prioridad;
		insertarPasajero(lista, nombre, (Prioridad)prioridad);
	}
	cout << "Lista de pasajeros hasta el momento:\n";
	mostrarLista(lista);

	cout << "Digite el nombre del pasajero: "; cin >> nombre;
	cout << "Digite la prioridad del pasajero: "; cin >> prioridad;
	insertarPasajero(lista, nombre, (Prioridad)prioridad);
	cout << "Lista de pasajeros actualizada:\n";
	mostrarLista(lista);
	return 0;
}

void insertarPasajero(Lista &lista, string nombre, Prioridad prioridad) {
	Pasajero *nuevo_pasajero = new Pasajero{nombre, prioridad, nullptr};
	if(lista.cabeza == NULL || lista.cabeza->prioridad > prioridad) {
		nuevo_pasajero->siguiente = lista.cabeza;
		lista.cabeza = nuevo_pasajero;
	} else {
		Pasajero *aux = lista.cabeza;
		while(aux->siguiente && aux->siguiente->prioridad <= prioridad) {
			aux = aux->siguiente;
		}
		nuevo_pasajero->siguiente = aux->siguiente;
		aux->siguiente = nuevo_pasajero;
	}

	cout << "Pasajero: " << nombre << " agregado con exito a la lista.\n";
	lista.cantidad++;
}

string prioridadToString(Prioridad p) {
    switch (p) {
        case VIP: return "VIP";
        case NORMAL: return "Normal";
        case ESPERA: return "En espera";
        default: return "Desconocido";
    }
}

void mostrarLista(const Lista &lista) {
	Pasajero *p = lista.cabeza;
	while (p) {
		cout << "{Pasajero = " << p->nombre << " , ";
		cout << prioridadToString(p->prioridad) << "}\n";
        p = p->siguiente;
	}
    cout << "Cantidad total de pasajeros: " << lista.cantidad << "\n";
}