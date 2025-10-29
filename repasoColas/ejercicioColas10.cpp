/*
    Ejercicio 10: Cola de soporte técnico
    Cada cliente que llama al soporte se encola al final.
    Cada cliente tiene:
        - nombre
        - problema (string)
        - prioridad (1 = urgente, 2 = normal)
    Se debe poder:
        - Agregar cliente (al final)
        - Mostrar cola
        - Atender cliente (eliminar del frente)
        - Cancelar cliente por nombre (eliminar en medio o al final)
        - Vaciar cola
*/
#include <iostream>
#include <string>
#include <limits>
using namespace std;

//Estructuras
struct Cliente {
    string nombre;
    string problema;
    int prioridad;
    Cliente* siguiente;
};

struct Cola {
    Cliente* frente = nullptr;
    Cliente* final = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarCliente(Cola&, const string&, const string&, int);
void mostrarCola(const Cola&);
void atenderCliente(Cola&);
void cancelarCliente(Cola&, const string&);
void vaciarCola(Cola&);
bool verificarCola(const Cola&);

//Main
int main() {
    Cola cola;
    int opcion = 0, prioridad;
    string nombre, problema;
    do {
        cout << "\t---MENU---"
            << "\n1.- Agregar cliente"
            << "\n2.- Mostrar cola"
            << "\n3.- Atender cliente"
            << "\n4.- Cancelar cliente"
            << "\n5.- Vaciar cola"
            << "\n6.- Salir del programa\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Nombre: "; cin >> nombre;
                cout << "Problema: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, problema);
                //fflush(stdin);
                cout << "Prioridad [1 = urgente, 2 = normal]: "; 
                cin >> prioridad;
                while ((prioridad != 1) && (prioridad != 2)) {
                    fflush(stdin);
                    cout << "No valido!\nPrioridad [1 = urgente, 2 = normal]: ";
                    cin >> prioridad;
                }
                agregarCliente(cola, nombre, problema, prioridad);
                break;
            case 2:
                cout << "Mostrando cola de clientes: \n";
                if(verificarCola(cola)) mostrarCola(cola);
                break;
            case 3:
                if(verificarCola(cola)) atenderCliente(cola);
                else cout << "Agregue clientes primero.\n";
                break;
            case 4:
                cout << "Nombre: "; cin >> nombre;
                if(verificarCola(cola)) cancelarCliente(cola, nombre);
                else cout << "Agregue clientes primero.\n";
                break;
            case 5:
                if(verificarCola(cola)) vaciarCola(cola);
                else cout << "Cola vacia\n";
                break;
            case 6:
                if(verificarCola(cola)) vaciarCola(cola);
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no disponible.\n";
        }
        system("pause");
        system("cls");
    } while(opcion != 6);
    return 0;
}

//Definiciones
void agregarCliente(Cola& cola, const string& nombre, const string& problema, int prioridad) {
    Cliente* nuevo = new Cliente{nombre, problema, prioridad, nullptr};
    if (!cola.frente) {
        cola.frente = cola.final = nuevo;
    } else {
        cola.final->siguiente = nuevo;
        cola.final = nuevo;
    }
    cola.cantidad++;
    cout << nombre << " agregado con exito a la cola.\n";
}

void mostrarCola(const Cola& cola) {
    cout << "Cantidad de clientes en cola: " << cola.cantidad << "\n";
    Cliente* aux = cola.frente;
    while(aux) {
        cout << "Cliente: " << aux->nombre 
            << "\n\t[Problema: " << aux->problema << "]\n"
            << "\t[Prioridad: " << aux->prioridad << "]\n";
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void atenderCliente(Cola& cola) {
    cout << "Cliente: " << cola.frente->nombre << " atendido.\n";
    Cliente* temp = cola.frente;
    cola.frente = cola.frente->siguiente;
    if (!cola.frente) cola.final = nullptr; // quedó vacía
    delete temp;
    cola.cantidad--;
}

void cancelarCliente(Cola& cola, const string& nombre) {
    //Caso 1: El cliente se encuentra al inicio
    if (cola.frente->nombre == nombre) {
        cout << "Cliente: " << cola.frente->nombre << " cancelado.\n";
        Cliente* t = cola.frente;
        cola.frente = cola.frente->siguiente;
        if (!cola.frente) cola.final = nullptr;
        delete t;
        cola.cantidad--;
        return;
    }

    //Caso 2: El cliente se encuentra al medio o final
    Cliente* previo = cola.frente;
    Cliente* actual = cola.frente->siguiente;
    while (actual && actual->nombre != nombre) {
        previo = actual;
        actual = actual->siguiente;
    }
    if (!actual) {
        cout << "Cliente no encontrado.\n";
        return;
    }

    previo->siguiente = actual->siguiente;
    if (actual == cola.final) cola.final = previo;
    cout << "Cliente: " << actual->nombre << " cancelado.\n";
    delete actual;
    cola.cantidad--;
}

void vaciarCola(Cola& cola) {
    while (cola.frente) {
        Cliente* temp = cola.frente;
        cola.frente = cola.frente->siguiente;
        delete temp;
    }
    cola.final = nullptr;
    cola.cantidad = 0;
    cout << "Cola vaciada con exito.\n";
}

bool verificarCola(const Cola& cola) {
    return cola.frente != nullptr;
}
