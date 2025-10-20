/*
	Ejercicio 9: Lista de clientes. A cada uno se le asocia una lista de ventas
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Venta {
	float monto;
	Venta *siguiente;
};

struct Cliente {
	string nombre;
	Venta *listaVentas;
	Cliente *siguiente;
};

struct ListaClientes {
    Cliente* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void insertarCliente(ListaClientes &, const string &);
Cliente* buscarCliente(ListaClientes &, const string &);
void agregarVenta(ListaClientes &, const string &, float);
void mostrarClientes(const ListaClientes &);
void clearVentas(Venta *&);
void clearClientes(ListaClientes &);
void menu();

//Variables globales
ListaClientes lista;

int main () {
	menu();
	return 0;
}

//Definiciones de función
// Inserta clientes ordenados por nombre
void insertarCliente(ListaClientes& lista, const string& nombre) {
    Cliente* nuevo = new Cliente{ nombre, nullptr, nullptr };

	if(lista.cabeza == NULL || nombre < lista.cabeza->nombre) {
		nuevo->siguiente = lista.cabeza;
		lista.cabeza = nuevo;
	} else {
		Cliente *tmp = lista.cabeza;
		while (tmp->siguiente && tmp->siguiente->nombre <= nombre) {
			tmp = tmp->siguiente;
		}
		nuevo->siguiente = tmp->siguiente;
		tmp->siguiente = nuevo;
	}

    lista.cantidad++;
    cout << "Cliente " << nombre << " agregado.\n";
}

// Busca un cliente por nombre, devuelve puntero o nullptr
Cliente* buscarCliente(ListaClientes& lista, const string& nombre) {
    Cliente* aux = lista.cabeza;
    while (aux && aux->nombre < nombre) aux = aux->siguiente;
    return (aux && aux->nombre == nombre) ? aux : nullptr;
}

// Agregar venta a cliente existente
void agregarVenta(ListaClientes& lista, const string& nombre, float monto) {
    Cliente* c = buscarCliente(lista, nombre);
    if (!c) {
        cout << "Cliente " << nombre << " no encontrado.\n";
        return;
    }

    Venta* nueva = new Venta{ monto, nullptr };
	if (c->listaVentas == NULL) {
		nueva->siguiente = c->listaVentas;
		c->listaVentas = nueva;
	} else {
		Venta *tmp = c->listaVentas;
		while (tmp->siguiente) {
			tmp = tmp->siguiente;
		}
		nueva->siguiente = tmp->siguiente;
		tmp->siguiente = nueva;
	}

    cout << "Venta de S/." << monto << " registrada para " << nombre << ".\n";
}

// Mostrar todos los clientes con sus ventas
void mostrarClientes(const ListaClientes& lista) {
    if (!lista.cabeza) { cout << "No hay clientes.\n"; return; }
    const Cliente* c = lista.cabeza;
    while (c) {
        cout << "Cliente: " << c->nombre << "\n  Ventas: ";
        const Venta* v = c->listaVentas;
        if (!v) cout << "(sin ventas)";
        while (v) {
            cout << v->monto << " ";
            v = v->siguiente;
        }
        cout << "\n";
        c = c->siguiente;
    }
}

// Libera memoria de ventas
void clearVentas(Venta*& lista) {
	while (lista) {
		Venta *temp = lista;
		lista = lista->siguiente;
		delete temp;
	}
}

// Libera memoria de todos los clientes y sus ventas
void clearClientes(ListaClientes& L) {
    Cliente* c = L.cabeza;
    while (c) {
        clearVentas(c->listaVentas);
        Cliente* temp = c;
        c = c->siguiente;
        delete temp;
    }
    L.cabeza = nullptr;
    L.cantidad = 0;
    cout << "Memoria liberada.\n";
}

void menu() {
    int opcion = 0;
	float monto = 0.0;
	string nombre;
    do {
        cout << "\t---Menu---\n";
        cout << "1.- Insertar cliente\n2.- Agregar venta\n3.- Mostrar clientes\n4.- Limpiar lista de clientes\n";
		cout << "5.- Salir\n";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            cout << "Digite el nombre: "; cin >> nombre;
            insertarCliente(lista, nombre);
			cout << "Lista hasta el momento: \n";
			mostrarClientes(lista);
            break;
        case 2:
			cout << "Digite el nombre del cliente: "; cin >> nombre;
			cout << "Digite el monto de venta: "; cin >> monto;
            agregarVenta(lista, nombre, monto);
            break;
		case 3:
			cout << "Mostrando lista de clientes\n";
			mostrarClientes(lista);
			break;
        case 4:
            cout << "Eliminando la lista completa...\n";
            clearClientes(lista);
            cout << "Lista restante:\n";
            mostrarClientes(lista);
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
}