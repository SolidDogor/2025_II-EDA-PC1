/*
        Ejercicio 11: Sistema de gestión de pedidos avanzados.
                Permitir eliminar un pedido específico por su ID dentro de cada cliente,
                y calcular el total gastado por cada cliente.
                Los clientes deben mantenerse ordenados alfabéticamente,
                y los pedidos deben conservar su orden de inserción (FIFO).
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Pedido {
        int id;
        string descripcion;
        float monto;
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

//Prototipado de funciones
void agregarCliente (Lista &, string &);
Cliente* buscarCliente (Lista &, string &);
void agregarPedido (Lista &, string &, string &, float);
void mostrarPedidos (Cliente *);
float calcularTotalCliente (Lista &, string &);
void mostrarClientes (Lista &);
void eliminarPedido (Lista &, string &, int);
void eliminarCliente (Lista &, string &);
void eliminarLista (Lista &);
void menu();

//Variables globlales
Lista lista;
int idPedido = 1;

int main () {
        menu ();
        return 0;
}

//Definiciones de funciones
//Función que agrega un nuevo cliente a la lista
void agregarCliente (Lista &lista, string &nombre) {
        Cliente *nuevoCliente = new Cliente{nombre, nullptr, nullptr};
        if (!lista.cabeza || lista.cabeza->nombre > nombre) {
                nuevoCliente->siguiente = lista.cabeza;
                lista.cabeza = nuevoCliente;
        } else {
                Cliente *aux = lista.cabeza;
                while (aux->siguiente && aux->siguiente->nombre <= nombre) {
                        aux = aux->siguiente;
                }
                nuevoCliente->siguiente = aux->siguiente;
                aux->siguiente = nuevoCliente;
        }
        cout << "Cliente " << nombre << " agregado con exito a la lista.\n";
        lista.cantidad++;
}

Cliente* buscarCliente (Lista &lista, string &nombre) {
        Cliente *caux = lista.cabeza;
        while (caux && caux->nombre < nombre) {
                caux = caux->siguiente;
        }
        return (caux && caux->nombre == nombre) ? caux : nullptr;
}

//Función que agrega un pedido a un cliente en especifico
void agregarPedido (Lista &lista, string &nombre, string &descripcion, float monto){
        //Verificando que un cliente exista 
        Cliente *caux = buscarCliente(lista, nombre);
        if(!caux) {
                cout << "No existe el cliente indicado!\n";
                return;
        } 
        //Agregando pedido en caso de existir el cliente
        Pedido *nuevoPedido = new Pedido{idPedido++, descripcion, monto, nullptr};
        if (!caux->listaPedidos) {
                caux->listaPedidos = nuevoPedido;
        } else {
                Pedido *paux = caux->listaPedidos;
                while (paux->siguiente) {
                        paux = paux->siguiente;
                }
                paux->siguiente = nuevoPedido;
        }
        cout << "Pedido " << descripcion << " agregado con exito a la lista de " << nombre << ".\n";
}

//Funcion que muestra los pedidos de un cliente en caso de tener minimo uno
void mostrarPedidos (Cliente *cliente) {
        Pedido *temp = cliente->listaPedidos;
        if (!temp) {
                cout << "\tNo hay pedidos registrados.\n";
                return;
        }
        while (temp) {
                cout << "\tPedido #" << temp->id << ": " << temp->descripcion;
                cout << " - S/." << temp->monto << "\n";
                temp = temp->siguiente;
        }
}

//Funcion que calcula el total que ha gastado un cliente
float calcularTotalCliente (Lista &lista, string &nombre) {
        //Verificando que un cliente exista
        Cliente *caux = buscarCliente(lista, nombre);
        if(!caux) {
                cout << "No existe el cliente indicado!\n";
                return 0;
        }
        float total = 0.0f;
        for (Pedido *paux = caux->listaPedidos; paux; paux = paux->siguiente) {
                total += paux->monto;
        }
        return total;
}

//Funcion que muestra toda la lista de clientes en caso de contener minimo uno
void mostrarClientes (Lista &lista) {
        Cliente *temp = lista.cabeza;
        //En caso de no haber clientes, retornamos
        if (!temp) {
                cout << "No hay clientes en lista!\n";
                return;
        }
        while (temp) {
                cout << "Cliente: " << temp->nombre << ":\n";
                mostrarPedidos(temp);
                cout << "\tTotal gastado: S/." << calcularTotalCliente(lista, temp->nombre) << "\n";
                temp = temp->siguiente;
        }
}

//Función que elimina un pedido de un cliente mediante el id
void eliminarPedido (Lista &lista, string &nombre, int id) {
        //Verificando que un cliente exista o tenga pedidos
        Cliente *caux = buscarCliente(lista, nombre);
        if(!caux) {
                cout << "No existe el cliente indicado!\n";
                return;
        }
        if (!caux->listaPedidos) {
                cout << "El cliente no tiene pedidos!\n";
                return;
        }

        if (caux->listaPedidos->id == id) {
                Pedido *paux = caux->listaPedidos;
                caux->listaPedidos = caux->listaPedidos->siguiente;
                delete paux;
                cout << "Pedido #" << id << " eliminado del cliente " << nombre << "\n";
                return;
        }

        Pedido *previo = caux->listaPedidos;
        Pedido *actual = caux->listaPedidos->siguiente;
        while (actual && actual->id != id) { 
                previo = actual;
                actual = actual->siguiente;
        }
        if (!actual) { 
                cout << "Pedido no encontrado.\n";
                return;
        }
        previo->siguiente = actual->siguiente;
        delete actual;
        cout << "Pedido #" << id << " eliminado del cliente " << nombre << ".\n";
}

//Funcion que elimina un cliente mediante su nombre
void eliminarCliente (Lista &lista, string &nombre) {
        if (!lista.cabeza) {
                cout << "No hay clientes registrados!\n";
                return;
        }

        if (lista.cabeza->nombre == nombre) {
                Cliente* caux = lista.cabeza;
                lista.cabeza = lista.cabeza->siguiente;
                //Borrar sublista
                Pedido* paux = caux->listaPedidos;
                while (paux) {
                        Pedido* temp = paux;
                        paux = paux->siguiente;
                        delete temp;
                }
                delete caux;
                lista.cantidad--;
                cout << "Cliente '" << nombre << "' eliminado.\n";
                return;
        }

        Cliente* previo = lista.cabeza;
        Cliente* actual  = lista.cabeza->siguiente;
        while (actual && actual->nombre != nombre) {
                previo = actual;
                actual = actual->siguiente;
        }
        if (!actual) {
                cout << "No existe el cliente '" << nombre << "'.\n";
                return;
        }

        previo->siguiente = actual->siguiente;
        Pedido* paux = actual->listaPedidos;
        while (paux) {
                Pedido* temp = paux;
                paux = paux->siguiente;
                delete temp;
        }
        delete actual;
        lista.cantidad--;
        cout << "Cliente '" << nombre << "' eliminado.\n";
}

//Función que elimina toda la lista de clientes
void eliminarLista (Lista &lista) {
        Cliente* caux = lista.cabeza;
        while (caux) {
                Cliente* ctemp = caux;
                caux = caux->siguiente;
                Pedido* paux = ctemp->listaPedidos;
                while (paux) {
                        Pedido* ptemp = paux;
                        paux = paux->siguiente;
                        delete ptemp;
                }
                delete ctemp;
        }
        lista.cabeza = nullptr;
        lista.cantidad = 0;
        idPedido = 1;
        cout << "Lista completa eliminada.\n";
}

//Función que despliega el menu de opciones
void menu() {
        int opcion = 0;
        float monto = 0.0f;
        string nombre, descripcion;

        do {
                cout << "\t---Menu---\n";
                cout << "1.- Agregar cliente\n2.- Agregar pedido\n3.- Mostrar clientes\n";
                cout << "4.- Eliminar pedido por ID\n5.- Eliminar cliente\n6.- Eliminar lista\n7.- Salir\n> ";
                cin >> opcion;

                switch (opcion) {
                case 1:
                        cout << "Nombre: "; cin >> nombre;
                        agregarCliente(lista, nombre);
                        break;
                case 2:
                        cout << "Cliente: "; cin >> nombre;
                        cout << "Descripcion: "; cin >> descripcion;
                        cout << "Monto: "; cin >> monto;
                        agregarPedido(lista, nombre, descripcion, monto);
                        break;
                case 3:
                        mostrarClientes(lista);
                        break;
                case 4:
                        int id; 
                        cout << "Cliente: "; cin >> nombre;
                        cout << "ID de pedido a eliminar: "; cin >> id;
                        eliminarPedido(lista, nombre, id);
                        break;
                case 5:
                        cout << "Nombre: "; cin >> nombre;
                        eliminarCliente(lista, nombre);
                        break;
                case 6:
                        eliminarLista(lista);
                        break;
                case 7:
                        cout << "Saliendo del programa...\n";
                        break;
                default:
                        cout << "Opcion no disponible!\n";
                        break;
                }
                system("pause");
                system("cls");
        } while (opcion != 7);
}