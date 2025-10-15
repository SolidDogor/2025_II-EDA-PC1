//Insertar datos en una estructura lista
#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    string nombre;
    float valor;
    Nodo *siguiente;
};

struct Lista {
    Nodo *cabeza = nullptr;
    int cantidad = 0;
};

//Prototipo de funciones
void insertarProducto(Lista &, string, float);
void mostrarLista(const Lista&);
void menu();

Lista inventario;

int main() {
    menu();
    return 0;
}

//Definicion de funciones
void insertarProducto(Lista &inventario, string nombre, float valor) {
    /*
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->nombre = nombre;
    nuevo_nodo->valor = valor;
    nuevo_nodo->siguiente = NULL;
    */
    Nodo *nuevo_nodo = new Nodo{nombre, valor, nullptr};    

    //Se puede omitir este caso y directamente usar dos nodos auxiliares
    // para ir evaluando los distintos escenarios de inserción.
    if(inventario.cabeza == nullptr || inventario.cabeza->valor >= valor) {
        nuevo_nodo->siguiente = inventario.cabeza;
        inventario.cabeza = nuevo_nodo;
    } else {
        Nodo *aux = inventario.cabeza;
        while (aux->siguiente && aux->siguiente->valor < valor) {
            aux = aux->siguiente;
        }
        nuevo_nodo->siguiente = aux->siguiente;
        aux->siguiente = nuevo_nodo;
    }

    inventario.cantidad++;
    cout << "Producto: " << nombre << " agregado con exito al inventario.\n";
}

void mostrarLista(const Lista &inventario) {
    if(!inventario.cabeza) {
        cout << "No hay elementos guardados.\n";
        return;
    }
    Nodo *p = inventario.cabeza;
    while (p) {
        cout << "{Producto: " << p->nombre << " , ";
        cout << "Valor: " << p->valor << "}\n";
        p = p->siguiente;
    }
}

void menu () {
    int opcion = 0;
    float val;
    string nom;

    do {
        cout << "\t---Menu---\n";
        cout << "1.- Agregar producto\n2.- Mostrar inventario\n3.- Salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite el nombre: "; cin >> nom;
            cout << "Digite el valor: "; cin >> val;
            insertarProducto(inventario, nom, val);
            cout << "Lista hasta el momento:\n";
            mostrarLista(inventario);
            break;
        case 2:
            cout << "Imprimiendo lista:\n";
            mostrarLista(inventario);
            break;
        case 3:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion no disponible!\n";
            break;
        }

        system("pause");
        system("cls");

    } while (opcion != 3);
    
}