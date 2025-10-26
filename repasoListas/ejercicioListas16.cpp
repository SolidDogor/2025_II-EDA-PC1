/*
    Ejercicio 16: Lista de tareas ordenadas por prioridad (ordenado)
        Queremos insertar tareas en orden ascendente de prioridad (1 = más importante).
        Debe poder:
            Agregar tarea (ordenada)
            Mostrar lista
            Vaciar lista
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Tarea { 
    string descripcion;
    int prioridad;
    Tarea* siguiente;
};

struct Lista {
    Tarea* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarTarea(Lista&,string&,int);
void mostrarLista(Lista&);
void vaciarLista(Lista&);

//Variables globales
Lista lista;

//Main
int main() {
    int opcion = 0, prioridad;
	string descripcion;
	do {
		cout << "1.- Agregar tarea\n2.- Mostrar lista\n"
			<< "3.- Vaciar lista\n4.- Salir\n> ";
		cin >> opcion;
		switch (opcion) {
			case 1:
				cout << "Digite la descripcion: "; cin >> descripcion;
                cout << "Digite la prioridad: "; cin >> prioridad;
				agregarTarea(lista,descripcion,prioridad);
				break;
			case 2:
				mostrarLista(lista);
				break;
			case 3:
				vaciarLista(lista);
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
	return 0;
}

//Definiciones
void agregarTarea(Lista& lista,string& descripcion,int prioridad) {
    Tarea* nueva = new Tarea{descripcion,prioridad,nullptr};
    if(!lista.cabeza || lista.cabeza->prioridad >= prioridad) {
        nueva->siguiente = lista.cabeza;
        lista.cabeza = nueva;
    } else {
        Tarea* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->prioridad < prioridad) {
            aux = aux->siguiente;
        }
        nueva->siguiente = aux->siguiente;
        aux->siguiente = nueva;        
    }
    lista.cantidad++;
    cout << descripcion << " agregada con exito a la lista\n";
}

void mostrarLista(Lista& lista) {
    if(!lista.cabeza) {
        cout << "Lista vacia.\n";
        return;
    }
    Tarea* aux = lista.cabeza;
    cout << "Cantidad de tareas en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << "[Tarea: " << aux->descripcion << ", prioridad: " << aux->prioridad << "]\n";
        aux = aux->siguiente;
    }
}

void vaciarLista(Lista& lista) {
    if(!lista.cabeza) {
        cout << "Lista vacia.\n";
        return;
    }
    while(lista.cabeza) {
        Tarea* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete aux;
    }
    lista.cantidad = 0;
    cout << "Lista eliminada con exito.\n";
}