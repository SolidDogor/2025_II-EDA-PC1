/*
    Ejercicio 4: Ingresar 3 personas en una cola. Usar frente y final para mostrar en O(1)
*/
#include <iostream>
#include <string>

//Estructuras
struct Nodo {
    std::string nombre;
    Nodo *siguiente;
};

struct Cola {
    Nodo *frente = nullptr;
    Nodo *final = nullptr;
};

//Prototipado de funciones
void agregarNodo(Cola &, std::string);
void eliminarNodo(Cola &);
void mostrarCola(Cola &);
void eliminarCola(Cola &);

int main() {
    Cola c;
    agregarNodo(c, "Ana");
    agregarNodo(c, "Bruno");
    agregarNodo(c, "Carla");
    mostrarCola(c);
    eliminarNodo(c);
    mostrarCola(c);
    eliminarCola(c);
    mostrarCola(c);
    return 0;
}

//Definiciones de funciones
void agregarNodo(Cola &cola, std::string nombre) {
    Nodo *nuevo_nodo = new Nodo{nombre, nullptr};
    if(cola.final == nullptr) {
        cola.frente = cola.final = nuevo_nodo;
    } else {
        cola.final->siguiente = nuevo_nodo;
        cola.final = nuevo_nodo;
    }
    std::cout << nombre << " agregado a la cola.\n";
}

void eliminarNodo(Cola &cola) {
    if (cola.frente == nullptr) {
        std::cout << "Cola vacia! Ingrese algun nodo.\n";
        return;
    }
    Nodo *aux = cola.frente;
    cola.frente = cola.frente->siguiente;
    if(cola.frente == nullptr) {
        cola.final = nullptr;
    }
    std::cout << "Atendido: " << aux->nombre << "\n";
    delete aux;
}

void mostrarCola(Cola &cola) {
    if (cola.frente == nullptr) {
        std::cout << "Cola vacia! Ingrese algun nodo.\n";
        return;
    }
    Nodo *p = cola.frente;
    while (p) {
        std::cout << "Persona: " << p->nombre << "\n";
        p = p->siguiente;
    }
}

void eliminarCola(Cola &cola) {
    while (cola.frente) {
        Nodo *aux = cola.frente;
        cola.frente = cola.frente->siguiente;
        delete aux;
    }
    cola.final = nullptr;
    std::cout << "Cola liberada!\n";
}
