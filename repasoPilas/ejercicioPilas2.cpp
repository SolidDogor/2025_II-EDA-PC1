/*
    Ejercicio 2: Lista de espera para un servicio. Cada usuario puede darse de baja, 
        y al hacerlo se elimina al último de la lista. Insertar usuarios al final (orden de registro),
        eliminar al usuario final y mostrar el nombre del usuario eliminado
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Usuario {
    string nombre;
    int turno;
    Usuario *siguiente;
};

struct Pila {
    Usuario *cabeza = nullptr;
    int cantidad = 1;
};

//Prototipado de funciones
void agregarUsuario(Pila &, string);
void eliminarUsuario(Pila &);
void mostrarUsuarios(Pila &);
void menu();

//Variables globales
Pila pila;

int main() {
    menu();
    return 0;
}

//Definicion de funciones
void agregarUsuario(Pila &pila, string nombre) {
    int turno = pila.cantidad;
    Usuario *nuevo_usuario = new Usuario{nombre,turno,nullptr};
    if(pila.cabeza == NULL || pila.cabeza->turno < turno) {
        nuevo_usuario->siguiente = pila.cabeza;
        pila.cabeza = nuevo_usuario;
    } else {
        Usuario *aux = pila.cabeza;
        while(aux->siguiente && aux->siguiente->turno >= turno) {
            aux = aux->siguiente;
        }
        nuevo_usuario->siguiente = aux->siguiente;
        aux->siguiente = nuevo_usuario;
    }
    cout << "Usuario: " << nombre << " agregado a la pila (";
    cout << "puesto: " << turno << ")\n";
    pila.cantidad++;
}

void eliminarUsuario(Pila &pila) {
    if(pila.cabeza == nullptr) {
        cout << "Pila vacia!\n";
        return;
    }
    Usuario *eliminado = pila.cabeza;
    pila.cabeza = pila.cabeza->siguiente;
    cout << "Usuario: " << eliminado->nombre << " eliminado de la pila (";
    cout << "puesto: " << eliminado->turno << ")\n";
    delete eliminado;
}

void mostrarUsuarios(Pila &pila) {
    if(pila.cabeza == nullptr) {
        cout << "Pila vacia!\n";
        return;
    }
    Usuario *p = pila.cabeza;
    while (p) {
        cout << "Usuario: " << p->nombre;
        cout << " puesto: " << p->turno << "\n";
        p = p->siguiente;
    }
}

void menu () {
    int opcion = 0;
    float val;
    string nom;

    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar usuario\n2.- Mostrar pila\n3.- Sacar usuario\n4.- Salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite el nombre: "; cin >> nom;
            agregarUsuario(pila, nom);
            cout << "Lista hasta el momento:\n";
            mostrarUsuarios(pila);
            break;
        case 2:
            cout << "Imprimiendo pila:\n";
            mostrarUsuarios(pila);
            break;
        case 3:
            cout << "Sacando al primer cliente...\n";
            eliminarUsuario(pila);
            cout << "Lista restante:\n";
            mostrarUsuarios(pila);
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
    
}