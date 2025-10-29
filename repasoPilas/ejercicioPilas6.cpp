/*
    Ejercicio 6: Pila de acciones del sistema
    Cada acción ejecutada se apila.
    Tiene:
        - descripcion (string)
        - categoria (string)
    Debe permitir:
        - Registrar acción (push al inicio)
        - Mostrar historial
        - Deshacer última acción (pop cabeza)
        - Eliminar todas las acciones de una categoría específica (p. ej. “archivo”)
        - Vaciar pila
*/
#include <iostream>
#include <string>
#include <limits>
using namespace std;

//Estructuras
struct Accion {
    string descripcion;
    string categoria;
    Accion* siguiente;
};

struct Pila {
    Accion* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void registrarAccion(Pila&, const string&, const string&);
void mostrarPila(const Pila&);
void deshacerAccion(Pila&);
void eliminarCategoria(Pila&, const string&);
void vaciarPila(Pila&);
bool verificarPila(const Pila&);

//Main
int main() {
    Pila pila;
    int opcion = 0;
    string descripcion, categoria;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar accion\n"
            << "2.- Mostrar pila\n"
            << "3.- Deshacer accion\n"
            << "4.- Eliminar categoria\n"
            << "5.- Vaciar pila\n"
            << "6.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Descripcion: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, descripcion);
                cout << "Categoria: ";
                getline(cin, categoria);
                registrarAccion(pila,descripcion,categoria);
                break;
            case 2:
                cout << "Mostrando pila de acciones: \n";
                if(verificarPila(pila)) mostrarPila(pila);
                else cout << "Pila vacia.\n";
                break;
            case 3:
                if(verificarPila(pila)) deshacerAccion(pila);
                else cout << "Agregue acciones primero.\n";
                break;
            case 4:
                cout << "Categoria: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, categoria);
                if(verificarPila(pila)) eliminarCategoria(pila, categoria);
                else cout << "Agregue acciones primero.\n";
                break;
            case 5:
                if(verificarPila(pila)) vaciarPila(pila);
                else cout << "Pila vacia\n";
                break;
            case 6:
                if(verificarPila(pila)) vaciarPila(pila);
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no disponible.\n";
        }
        system("pause");
        system("cls");
    } while (opcion != 6);
    return 0;
}

//Definiciones
void registrarAccion(Pila& pila, const string& descripcion, const string& categoria) {
    Accion* nueva = new Accion{descripcion, categoria, nullptr};
    nueva->siguiente = pila.cabeza;
    pila.cabeza = nueva;
    cout << descripcion << " [" << categoria << "] agregado con exito a la pila.\n";
    pila.cantidad++;
}

void mostrarPila(const Pila& pila) {
    Accion* aux = pila.cabeza;
    cout << "Cantidad de acciones en pila: " << pila.cantidad << "\n";
    while(aux) {
        cout << aux->descripcion << " [" << aux->categoria << "]";
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void deshacerAccion(Pila& pila) {
    Accion* temp = pila.cabeza;
    pila.cabeza = pila.cabeza->siguiente;
    cout << temp->descripcion << " [" << temp->categoria << "] sacado de pila.\n";
    delete temp;
    pila.cantidad--;
}

void eliminarCategoria(Pila& pila, const string& categoria) {
    //Eliminando los que estén consecutivos
    while(pila.cabeza->categoria == categoria) deshacerAccion(pila);
    //Eliminando el resto
    Accion* previo = pila.cabeza;
    while(previo && previo->siguiente) {
        if(previo->siguiente->categoria == categoria) {
            Accion* temp = previo->siguiente;
            previo->siguiente = temp->siguiente;
            cout << temp->descripcion << " [" << temp->categoria << "] sacado de pila.\n";
            delete temp;
            pila.cantidad--;
        } else {
            previo = previo->siguiente;
        }
    }
    cout << "Categoria: " << categoria << " eliminada con exito de la pila.\n";
}

void vaciarPila(Pila& pila) {
    while(pila.cabeza) {
        Accion* temp = pila.cabeza;
        pila.cabeza = pila.cabeza->siguiente;
        delete temp;
    }
    pila.cabeza = nullptr;
    pila.cantidad = 0;
    cout << "Pila vaciada con exito.\n";
}

bool verificarPila(const Pila& pila) {
    return pila.cabeza != nullptr;
}