/*
	Ejercicio 15: Registro de temperaturas diarias
		Se debe insertar una temperatura al final de la lista
		No hace falta ordenarla, solo guardarla en el orden que ingresó
		Mostrar las temperaturas registradas
		Mostrar la temperatura máxima, promedio y mínima
		Vaciar la lista
*/
#include <iostream>
using namespace std;

//--Estructuras--
struct Nodo {
    float temperatura;
    Nodo* siguiente;
};

struct Lista {
    Nodo* cabeza = nullptr;
    int cantidad = 0;
    float max = 0;
    float min = 0;
    float suma = 0;
};

//--Prototipado--
void registrarTemperatura(Lista&,float);
void mostrarLista(Lista&);
void mostrarPromedio(Lista&);
void mostrarMaxMin(Lista&);
void vaciarLista(Lista&);

//--Variables globales--
Lista lista;

//--Main--
int main() {
	int opcion = 0;
	float temperatura;
	do {
		cout << "1.- Registrar temperatura\n2.- Mostrar lista\n"
			<< "3.- Mostrar promedio\n4.- Mostrar max/min\n"
			<< "5.- Vaciar lista\n6.- Salir\n> ";
		cin >> opcion;
		switch (opcion) {
			case 1:
				cout << "Digite la temperatura: "; cin >> temperatura;
				registrarTemperatura(lista,temperatura);
				break;
			case 2:
				cout << "Imprimiendo la lista:\n";
				mostrarLista(lista);
				break;
			case 3:
				mostrarPromedio(lista);
				break;
			case 4:
				mostrarMaxMin(lista);
				break;
			case 5:
				vaciarLista(lista);
				break;
			case 6:
				cout << "Saliendo del programa...\n";
				break;
			default:
				cout << "Opcion no disponible!\n";
				break;
		}
		system("pause");
		system("cls");
	} while (opcion != 6);
	return 0;
}

//--Definiciones--
void registrarTemperatura(Lista& lista,float temperatura) {
	Nodo* nuevo = new Nodo{temperatura, nullptr};
	nuevo->siguiente = lista.cabeza;
	lista.cabeza = nuevo;
	lista.cantidad++;
    if(lista.max < temperatura || lista.cantidad == 1) lista.max = temperatura;
    if(lista.min > temperatura || lista.cantidad == 1) lista.min = temperatura;
    lista.suma += temperatura;
	cout << temperatura << "° agregado con exito a la lista!\n";
}

void mostrarLista(Lista& lista) {
	if(!lista.cabeza) {
		cout << "Lista vacia\n";
		return;
	}
	Nodo* aux = lista.cabeza;
	while (aux) {
		cout << aux->temperatura << "°";
		(aux->siguiente) ? cout << " - " : cout << ".\n";
		aux = aux->siguiente;
	}
}
void mostrarPromedio(Lista& lista) {
	if(!lista.cabeza) {
		cout << "Ingrese alguna temperatura primero.\n";
		return;
	}
	cout << "Promedio de temperaturas: " << lista.suma / lista.cantidad << "°\n";
}

void mostrarMaxMin(Lista& lista) {
	if(!lista.cabeza) {
		cout << "Ingrese alguna temperatura primero.\n";
		return;
	}
	cout << "Temperatura maxima: " << lista.max << "°\n";
	cout << "Temperatura minima: " << lista.min << "°\n";
}

void vaciarLista(Lista& lista) {
	if(!lista.cabeza) {
		cout << "Ingrese alguna temperatura primero.\n";
		return;
	}
	while (lista.cabeza) {
		Nodo* aux = lista.cabeza;
		lista.cabeza = lista.cabeza->siguiente;
		delete aux;
	}
	lista.cantidad = 0;
    lista.max = 0;
    lista.min = 0;
    lista.suma = 0;
	cout << "Lista vaciada.\n";
}