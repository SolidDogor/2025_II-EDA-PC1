/*
    Ejercicio 9: Cola de reproducción de canciones
        Simula una lista de canciones en reproducción.
        Cada canción nueva se agrega al final, y cuando termina, se elimina del inicio.
        Debe permitir:
            - Agregar canción
            - Mostrar lista de canciones pendientes
            - Vaciar la lista
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Cancion {
    string titulo;
    string artista;
    Cancion* siguiente;
};

struct Cola {
    Cancion* frente = nullptr;
    Cancion* final = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarCancion(Cola&, string&, string&);
void mostrarCola(Cola&);
void eliminarCancion(Cola&);
void vaciarCola(Cola&);

//Main
int main() {
    Cola cola;
    int opcion = 0;
    string titulo, artista;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar cancion\n"
            << "2.- Mostrar cola de canciones\n"
            << "3.- Eliminar cancion\n"
            << "4.- Vaciar cola\n"
            << "5.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el titulo: "; cin >> titulo;
                cout << "Digite el artista: "; cin >> artista;
                agregarCancion(cola,titulo,artista);
                break;
            case 2:
                mostrarCola(cola);
                break;
            case 3:
                eliminarCancion(cola);
                break;
            case 4:
                vaciarCola(cola);
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                vaciarCola(cola);
                break;
            default:
                cout << "Opcion no implementada.\n";
        }
        system("pause");
        system("cls");
    } while (opcion !=5);
    return 0;
}

//Definiciones
void agregarCancion(Cola& cola, string& titulo, string& artista) {
    Cancion* nueva = new Cancion{titulo,artista,nullptr};
    if (!cola.frente) {
        nueva->siguiente = cola.final;
        cola.final = cola.frente = nueva;
    } else {
        cola.final->siguiente = nueva;
        cola.final = nueva;
    }
    cola.cantidad++;
    cout << artista << " - " << titulo << " agregado con exito a la cola.\n";
}

void mostrarCola(Cola& cola) {
    if(!cola.final) {
        cout << "Cola vacia.\n";
        return;
    }
    Cancion* aux = cola.frente;
    while(aux) {
        cout << aux->artista << " - " << aux->titulo;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarCancion(Cola& cola) {
    if(!cola.frente) {
        cout << "Ingrese alguna cancion primero.\n";
        return;
    }
    Cancion* temp = cola.frente;
    cola.frente = cola.frente->siguiente;
    cout << temp->artista << " - " << temp->titulo << " eliminado de cola.\n";
    cola.cantidad--;
    delete temp;
}

void vaciarCola(Cola& cola) {
    if(!cola.final) {
        cout << "Cola vacia.\n";
        return;
    }
    while(cola.frente) {
        Cancion* temp = cola.frente;
        cola.frente = cola.frente->siguiente;
        delete temp;
    }
    cola.frente = cola.final = nullptr;
    cola.cantidad = 0;
    cout << "Cola vaciada con exito.\n";
}
