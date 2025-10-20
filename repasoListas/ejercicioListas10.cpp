/*
	Ejercicio 10: Gestión de pedidos por cliente. Una pequeña tienda online necesita un sistema para registrar 
		clientes y sus pedidos.
	Cada cliente puede tener varios pedidos, y cada pedido tiene:
		un ID numérico (autogenerado desde 1 en adelante),
		una descripción del producto,
		y el precio total del pedido.
	El sistema debe poder registrar clientes ordenados alfabéticamente,
	y dentro de cada cliente, los pedidos deben guardarse en orden de inserción (como una cola FIFO).
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Pedido {
	int id;
	string descripcion;
	float total;
	Pedido *siguiente;
};

struct Cliente {
	string nombre;
	Pedido *listaPedidos;
    Cliente *siguiente;
};

struct Lista {
	Cliente *cabeza = nullptr;
	int cantidad = 0;
};

//Prototipos
void agregarCliente(Lista &, const string &);
Cliente* buscarCliente(Lista &, const string &);
void agregarPedido(Lista &, const string &, const string &, float);
void mostrarClientes(const Lista &);
bool eliminarPedidosDeCliente(Cliente *);
bool eliminarCliente(Lista &, const string &);
void eliminarLista(Lista &);
void menu();

//Variables globales
Lista lista;
int idPedido = 1;

int main () {
	menu();
	return 0;
}

//Definiciones
void agregarCliente(Lista &lista, const string &nombre) {
    Cliente *nuevo = new Cliente{nombre, nullptr, nullptr};

    if (!lista.cabeza || nombre < lista.cabeza->nombre) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
    } else {
        Cliente *aux = lista.cabeza;
        while (aux->siguiente && aux->siguiente->nombre < nombre) {
            aux = aux->siguiente;
        }
        // (opcional) evitar duplicados:
        if (aux->nombre == nombre || (aux->siguiente && aux->siguiente->nombre == nombre)) {
            cout << "Cliente '" << nombre << "' ya existe.\n";
            delete nuevo;
            return;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
    lista.cantidad++;
    cout << "Cliente " << nombre << " agregado con exito.\n";
}

Cliente* buscarCliente(Lista &lista, const string &nombre) {
    Cliente *aux = lista.cabeza;
    while (aux && aux->nombre < nombre) aux = aux->siguiente;
    return (aux && aux->nombre == nombre) ? aux : nullptr;
}

void agregarPedido(Lista &lista, const string &nombre, const string &descripcion, float total) {
    Cliente *c = buscarCliente(lista, nombre);
    if (!c) { cout << "No existe el cliente '" << nombre << "'.\n"; return; }

    Pedido *nuevo = new Pedido{idPedido++, descripcion, total, nullptr};

    if (!c->listaPedidos) {
        c->listaPedidos = nuevo;
    } else {
        Pedido *tmp = c->listaPedidos;
        while (tmp->siguiente) tmp = tmp->siguiente;
        tmp->siguiente = nuevo;
    }
    cout << "Pedido #" << nuevo->id << " registrado para " << nombre << ".\n";
}

void mostrarClientes(const Lista &lista) {
    if (!lista.cabeza) { cout << "No hay clientes.\n"; return; }

    const Cliente *c = lista.cabeza;
    while (c) {
        cout << "Cliente: " << c->nombre << "\n";
        const Pedido *p = c->listaPedidos;
        if (!p) {
            cout << "  (sin pedidos)\n";
        } else {
            while (p) {
                cout << "  Pedido #" << p->id << " - \"" << p->descripcion
                        << "\" - S/." << p->total << "\n";
                p = p->siguiente;
            }
        }
        c = c->siguiente;
    }
}

bool eliminarPedidosDeCliente(Cliente *c) {
    if (!c || !c->listaPedidos) return false;
    Pedido *p = c->listaPedidos;
    while (p) {
        Pedido *tmp = p;
        p = p->siguiente;
        delete tmp;
    }
    c->listaPedidos = nullptr;
    return true;
}

bool eliminarCliente(Lista &lista, const string &nombre) {
    if (!lista.cabeza) { cout << "No hay clientes registrados!\n"; return false; }

    if (lista.cabeza->nombre == nombre) {
        Cliente *victima = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        eliminarPedidosDeCliente(victima);
        delete victima;
        lista.cantidad--;
        cout << "Cliente '" << nombre << "' eliminado.\n";
        return true;
    }

    Cliente *prev = lista.cabeza;
    Cliente *curr = lista.cabeza->siguiente;
    while (curr && curr->nombre != nombre) {
        prev = curr;
        curr = curr->siguiente;
    }
    if (!curr) {
        cout << "No existe el cliente '" << nombre << "'.\n";
        return false;
    }

    prev->siguiente = curr->siguiente;
    eliminarPedidosDeCliente(curr);
    delete curr;
    lista.cantidad--;
    cout << "Cliente '" << nombre << "' eliminado.\n";
    return true;
}

void eliminarLista(Lista &lista) {
    Cliente *c = lista.cabeza;
    while (c) {
        Cliente *tmp = c;
        c = c->siguiente;
        eliminarPedidosDeCliente(tmp);
        delete tmp;
    }
    lista.cabeza = nullptr;
    lista.cantidad = 0;
    idPedido = 1;
    cout << "Lista completa eliminada.\n";
}

void menu() {
    int opcion = 0;
	float monto = 0.0;
	string nombre, descripcion;
    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar cliente\n2.- Agregar pedido\n3.- Mostrar clientes\n4.- Eliminar cliente\n";
		cout << "5.- Eliminar lista\n6.- Salir\n";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            cout << "Nombre: "; cin >> nombre;
            agregarCliente(lista, nombre);
            cout << "Lista hasta el momento:\n";
            mostrarClientes(lista);
            break;
        case 2:
            cout << "Cliente: "; cin >> nombre;
            cout << "Descripcion: "; cin >> descripcion;
            cout << "Monto: "; cin >> monto;
            agregarPedido(lista, nombre, descripcion, monto);
            break;
        case 3:
            cout << "Mostrando clientes:\n";
            mostrarClientes(lista);
            break;
        case 4:
            cout << "Nombre: "; cin >> nombre;
            eliminarCliente(lista, nombre);
            break;
        case 5:
            cout << "Eliminando la lista completa...\n";
            eliminarLista(lista);
            cout << "Lista restante:\n";
            mostrarClientes(lista);
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
}