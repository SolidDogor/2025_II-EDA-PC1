/*
    Ejercicio 3: Pila de navegación web
        Cada vez que el usuario visita una nueva página, se apila (inserta al inicio).
        Si presiona “Atrás”, se desapila (se elimina la cabeza).
        Debe poder:
            Agregar página visitada
            Retroceder (eliminar la última visitada del historial)
            Mostrar historial
            Vaciar historial
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Pagina {
    string url;
    Pagina* siguiente;
};

struct Pila {
    Pagina* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void modificarPagina(string&);
void agregarPagina(Pila&,string&);
void mostrarHistorial(Pila&);
void eliminarPagina(Pila&);
void eliminarHistorial(Pila&);

//Variables globales
Pila pila;

//Main
int main() {
    int opcion = 0;
	string url;
	do {
		cout << "1.- Agregar pagina\n2.- Mostrar historial\n"
			<< "3.- Eliminar ultima pagina\n4.- Eliminar historial\n"
            << "5.- Salir\n> ";
		cin >> opcion;
		switch (opcion) {
			case 1:
				cout << "Digite la pagina: "; cin >> url;
				agregarPagina(pila,url);
				break;
			case 2:
				cout << "Imprimiendo el historial:\n";
				mostrarHistorial(pila);
				break;
			case 3:
				eliminarPagina(pila);
				break;
			case 4:
				eliminarHistorial(pila);
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
void modificarPagina(string& url) {
    string inicio = "https://www.";
    string final = ".com";
    url = inicio + url + final;
}

void agregarPagina(Pila& pila,string& url) {
    modificarPagina(url);
    Pagina* nueva = new Pagina{url,nullptr};
    nueva->siguiente = pila.cabeza;
    pila.cabeza = nueva;
    pila.cantidad++;
    cout << url << " agregada con exito.\n";
}

void mostrarHistorial(Pila& pila) {
    if(!pila.cabeza) {
        cout << "Historial vacio.\n";
        return;
    }
    Pagina* aux = pila.cabeza;
    cout << "Cantidad de paginas: " << pila.cantidad << "\n";
    while (aux) {
        cout << aux->url;
        (aux->siguiente) ? cout << " - " : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarPagina(Pila& pila) {
    if(!pila.cabeza) {
        cout << "Agregue alguna pagina primero.\n";
        return;
    }
    Pagina* aux = pila.cabeza;
    pila.cabeza = pila.cabeza->siguiente;
    pila.cantidad--;
    cout << aux->url << " eliminada con exito.\n";
    delete aux;
}

void eliminarHistorial(Pila& pila) {
    if(!pila.cabeza) {
        cout << "Agregue alguna pagina primero.\n";
        return;
    }
    while (pila.cabeza) {
        Pagina* aux = pila.cabeza;
        pila.cabeza = pila.cabeza->siguiente;
        delete aux;
    }
    pila.cabeza = nullptr;
    pila.cantidad = 0;
    cout << "Historial eliminado con exito.\n";
}