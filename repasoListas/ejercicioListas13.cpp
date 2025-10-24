/*
        Ejercicio 13: Ranking de jugadores
                Se debe hacer un ranking de jugadores, ordenado de mayor a menor puntajes.
                Si se inserta un jugador existente:
                        Si su puntaje es mayor, se actualiza. Caso contrario, se ignora.
                El ranking debe tener un maximo de 5 jugadores, si entra uno nuevo y se excede:
                        Se elimina al que quedó último
                Se debe agregar/actualizar, buscar por nombre, eliminar por nombre, mostrar
                ranking, vaciar el ranking.
*/
#include <iostream>
#include <string>
using namespace std;

constexpr int TOP_N = 5;

struct Jugador {
    string nombre;
    float puntaje;
    Jugador* siguiente;
};

struct Lista {
    Jugador* cabeza = nullptr;
    int cantidad = 0;
};

// ---- Prototipos ----
void eliminarJugador(Lista&, string&);
void agregarJugador(Lista&, string&, float);
void actualizarPuntaje(Lista&, string&, float);
void mostrarLista(Lista&);
bool buscarJugador(Lista&, string&);
void eliminarLista(Lista&);
static Jugador* encontrarJugador(Lista& L, const string& nombre);
static void recortarTopN(Lista& L); // elimina el último si size > TOP_N

// ---- Main ----
int main() {
    Lista lista;
    int opcion = 0;
    float puntaje = 0.0f;
    string nombre;

    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar/Actualizar jugador\n2.- Mostrar lista\n3.- Eliminar jugador\n";
        cout << "4.- Eliminar lista\n5.- Salir\n> ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Nombre: "; cin >> nombre;
            cout << "Puntaje: "; cin >> puntaje;
            if (buscarJugador(lista, nombre)) {
                actualizarPuntaje(lista, nombre, puntaje);
            } else {
                agregarJugador(lista, nombre, puntaje);
            }
            break;
        case 2:
            mostrarLista(lista);
            break;
        case 3:
            cout << "Nombre: "; cin >> nombre;
            eliminarJugador(lista, nombre);
            break;
        case 4:
            eliminarLista(lista);
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

    eliminarLista(lista); // por si acaso
    return 0;
}

// ---- Implementaciones ----

static Jugador* encontrarJugador(Lista& L, const string& nombre) {
    Jugador* p = L.cabeza;
    while (p && p->nombre != nombre) p = p->siguiente;
    return p; // nullptr si no está
}

bool buscarJugador(Lista& lista, string& nombre) {
    return encontrarJugador(lista, nombre) != nullptr;
}

void mostrarLista(Lista& lista) {
    if (!lista.cabeza) { cout << "(Lista vacia)\n"; return; }
    Jugador* p = lista.cabeza;
    int pos = 1;
    while (p) {
        cout << pos++ << ") " << p->nombre << " - " << p->puntaje << " pts\n";
        p = p->siguiente;
    }
}

void agregarJugador(Lista& lista, string& nombre, float puntaje) {
    Jugador* nuevo = new Jugador{nombre, puntaje, nullptr};

    if (!lista.cabeza || lista.cabeza->puntaje < puntaje) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
    } else {
        Jugador* aux = lista.cabeza;
        while (aux->siguiente && aux->siguiente->puntaje >= puntaje) {
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }

    lista.cantidad++;
    recortarTopN(lista);

    cout << "Jugador " << nombre << " con puntaje " << puntaje << " agregado a lista.\n";
}

void actualizarPuntaje(Lista& lista, string& nombre, float nuevoPuntaje) {
    Jugador* j = encontrarJugador(lista, nombre);
    if (!j) { cout << "No existe el jugador!\n"; return; }

    if (nuevoPuntaje <= j->puntaje) {
        cout << "Puntaje no mejora. Se mantiene " << j->puntaje << ".\n";
        return;
    }

    if (lista.cabeza == j) {
        lista.cabeza = j->siguiente;
    } else {
        Jugador* prev = lista.cabeza;
        while (prev && prev->siguiente != j) prev = prev->siguiente;
        if (prev) prev->siguiente = j->siguiente;
    }
    lista.cantidad--;

    delete j;

    agregarJugador(lista, nombre, nuevoPuntaje);

    cout << "Puntaje del jugador " << nombre << " actualizado a " << nuevoPuntaje << " puntos.\n";
}

void eliminarJugador(Lista& lista, string& nombre) {
    if (!lista.cabeza) { cout << "(Lista vacia)\n"; return; }

    if (lista.cabeza->nombre == nombre) {
        Jugador* vict = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete vict;
        lista.cantidad--;
        cout << "Jugador " << nombre << " eliminado.\n";
        return;
    }

    Jugador* prev = lista.cabeza;
    Jugador* cur  = lista.cabeza->siguiente;
    while (cur && cur->nombre != nombre) {
        prev = cur; cur = cur->siguiente;
    }
    if (!cur) {
        cout << "No existe el jugador!\n";
        return;
    }

    prev->siguiente = cur->siguiente;
    delete cur;
    lista.cantidad--;
    cout << "Jugador " << nombre << " eliminado.\n";
}

void eliminarLista(Lista& lista) {
    while (lista.cabeza) {
        Jugador* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete aux;
    }
    lista.cantidad = 0;
    cout << "Lista vaciada.\n";
}

static void recortarTopN(Lista& L) {
    if (L.cantidad <= TOP_N) return;
    if (TOP_N == 0) { eliminarLista(L); return; }

    Jugador* p = L.cabeza;
    for (int i = 1; i < TOP_N && p && p->siguiente; ++i) {
        p = p->siguiente;
    }
    if (p && p->siguiente) {
        Jugador* vict = p->siguiente;
        p->siguiente = vict->siguiente;
        delete vict;
        L.cantidad--;
    }
}
