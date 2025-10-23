/*
    Ejercicio 6: Cola de impresión con prioridad simple
        - Los normales se encolan al final
        - Los urgentes se insertan al frente
        - Insertar, mostrar, eliminar (atender) y vaciar
*/
#include <iostream>
#include <string>
using namespace std;

// Estructuras
struct Trabajo {
    int id;
    string nombreArchivo;
    bool urgente;      //true = urgente, false = normal
    Trabajo* siguiente;
};

struct Cola {
    Trabajo* frente = nullptr; //Primero en salir
    Trabajo* final  = nullptr; //Último en la cola
    int cantidad    = 0;
};

//Prototipos
void agregarTrabajo(Cola&, const string&, bool);
void mostrarCola(const Cola&);
void eliminarTrabajo(Cola&);
void eliminarCola(Cola&);
void menu();

//Variables globales
Cola cola;
int id = 1;

//Main
int main() {
    menu();
    return 0;
}

void agregarTrabajo(Cola& cola, const string& nombreArchivo, bool urgente) {
    Trabajo* nuevo = new Trabajo{ id++, nombreArchivo, urgente, nullptr };

    if (!cola.frente) {
        // cola vacía
        cola.frente = cola.final = nuevo;
    } else if (urgente) {
        // insertar al frente
        nuevo->siguiente = cola.frente;
        cola.frente = nuevo;
    } else {
        // insertar al final
        cola.final->siguiente = nuevo;
        cola.final = nuevo;
    }

    cout << "Trabajo agregado: " << nombreArchivo
        << " [ID: " << nuevo->id << "] "
        << (urgente ? "(URGENTE)\n" : "(NORMAL)\n");
    cola.cantidad++;
}

void mostrarCola(const Cola& cola) {
    if (!cola.frente) {
        cout << "(Cola vacia)\n";
        return;
    }
    const Trabajo* p = cola.frente;
    cout << "Cola de impresion (" << cola.cantidad << "):\n";
    while (p) {
        cout << "  [" << (p->urgente ? "URGENTE" : "NORMAL ") << "] "
            << p->nombreArchivo << "  (ID " << p->id << ")\n";
        p = p->siguiente;
    }
}

void eliminarTrabajo(Cola& cola) {
    if (!cola.frente) {
        cout << "(No hay trabajos para atender)\n";
        return;
    }
    Trabajo* at = cola.frente;
    cola.frente = cola.frente->siguiente;
    if (!cola.frente) cola.final = nullptr; // quedó vacía
    cout << "Atendiendo: " << at->nombreArchivo << " (ID " << at->id << ")\n";
    delete at;
    cola.cantidad--;
}

void eliminarCola(Cola& cola) {
    while (cola.frente) {
        Trabajo* t = cola.frente;
        cola.frente = cola.frente->siguiente;
        delete t;
    }
    cola.final = nullptr;
    cola.cantidad = 0;
    id = 1;
    cout << "Cola vaciada!\n";
}

void menu() {
    int opcion = 0;
    string nombreArchivo;
    do {
        cout << "\n--- MENU ---\n"
            << "1) Agregar trabajo\n"
            << "2) Mostrar cola\n"
            << "3) Atender trabajo\n"
            << "4) Vaciar cola\n"
            << "5) Salir\n> ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int urgFlag = 0;
                cout << "Nombre del archivo: ";
                cin >> nombreArchivo;
                cout << "Es urgente? (1=si, 0=no): ";
                cin >> urgFlag;
                bool urgente = (urgFlag == 1);
                agregarTrabajo(cola, nombreArchivo, urgente);
                break;
            }
            case 2:
                mostrarCola(cola);
                break;
            case 3:
                eliminarTrabajo(cola);
                break;
            case 4:
                eliminarCola(cola);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no disponible!\n";
        }
        system("pause");
        system("cls");
    } while (opcion != 5);
}
