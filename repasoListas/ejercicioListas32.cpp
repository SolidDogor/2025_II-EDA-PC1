/*
    Ejercicio 32 – Lista simple de plantas
    Cada planta tiene:
        - nombre (string)
        - riegoCadaDias (int)
    Funciones:
        - Agregar planta al inicio
        - Mostrar todas las plantas
        - Vaciar lista
        - Salir
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Planta {
    string nombre;
    int riegoCadaDias;
    Planta* siguiente;
};

struct Lista {
    Planta* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarPlanta(Lista&, const string&, int);
void mostrarLista(const Lista&);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0, cantidad;
    string nombre;
    do {
        cout << "\t---MENU---"
            << "\n1.- Agregar planta"
            << "\n2.- Mostrar lista"
            << "\n3.- Vaciar lista"
            << "\n4.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el nombre: "; cin >> nombre;
                cout << "Digite la cantidad de dias de riego: "; cin >> cantidad;
                agregarPlanta(lista,nombre,cantidad);
                break;
            case 2:
                if(verificarLista(lista)) mostrarLista(lista);
                else cout << "Agregue una planta primero.\n";
                break;
            case 3:
                if(verificarLista(lista)) vaciarLista(lista);
                else cout << "Lista vacia.\n";
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                if(verificarLista(lista)) vaciarLista(lista);
                break;
            default:
                cout << "Opcion no disponible.\n";
        }
        system("pause");
        system("cls");
    } while(opcion != 4);
    return 0;
}

//Definiciones
void agregarPlanta(Lista& lista, const string& nombre, int cantidad) {
    Planta* nueva = new Planta{nombre,cantidad,nullptr};
    nueva->siguiente = lista.cabeza;
    lista.cabeza = nueva;
    lista.cantidad++;
    cout << nombre << " agregada con exito a la lista.\n";
}

void mostrarLista(const Lista& lista) {
    Planta* aux = lista.cabeza;
    cout << "Cantidad de plantas en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << aux->nombre << " [Dias de riego: " << aux->riegoCadaDias << "]";
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void vaciarLista(Lista& lista) {
    while(lista.cabeza) {
        Planta* temp = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete temp;
    }
    lista.cantidad = 0;
    lista.cabeza = nullptr;
    cout << "Lista vaciada con exito.\n";
}

bool verificarLista(const Lista& lista) {
    return lista.cabeza != nullptr;
}
