/*
    Ejercicio 17: Lista de estudiantes ordenados por nota (ordenado ascendente)
            Queremos registrar estudiantes en orden de menor a mayor nota.
            Debe permitir:
                Agregar estudiante
                Mostrar lista completa
                Vaciar lista
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Estudiante {
    string nombre;
    float nota;
    Estudiante* siguiente;
};

struct Lista {
    Estudiante* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarEstudiante(Lista&,string&,float);
void mostrarLista(Lista&);
void vaciarLista(Lista&);

//Variables globales
Lista lista;

//Main
int main() {
    int opcion = 0;
    string nombre;
    float nota = 0.0f;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar estudiante\n"
            << "2.- Mostrar lista\n"
            << "3.- Vaciar lista\n"
            << "4.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el nombre: "; cin >> nombre;
                cout << "Digite la nota: "; cin >> nota;
                agregarEstudiante(lista,nombre,nota);
                break;
            case 2:
                cout << "Mostrando cola:\n";
                mostrarLista(lista);
                break;
            case 3:
                vaciarLista(lista);
                break;
            case 4:
                vaciarLista(lista);
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no disponible.\n";
                break;
        }
        system("pause");
        system("cls");
    } while (opcion != 4);
    return 0;
}

//Definiciones
void agregarEstudiante(Lista& lista,string& nombre,float nota) {
    Estudiante* nuevo = new Estudiante{nombre,nota,nullptr};
    if(!lista.cabeza || lista.cabeza->nota > nota) {
        nuevo->siguiente  = lista.cabeza;
        lista.cabeza = nuevo;
    } else {
        Estudiante* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->nota <= nota) {
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
    lista.cantidad++;
    cout << nombre << " agregado con exito a la lista.\n";
}

void mostrarLista(Lista& lista) {
    if(!lista.cabeza) {
        cout << "Lista vacia.\n";
        return;
    }
    Estudiante* aux = lista.cabeza;
    cout << "Cantidad de estudiantes en lista: " << lista.cantidad << ".\n";
    while(aux) {
        cout << aux->nombre << ", nota: " << aux->nota;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void vaciarLista(Lista& lista) {
    if(!lista.cabeza) {
        cout << "Lista vacia.\n";
        return;
    }
    while(lista.cabeza) {
        Estudiante* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete aux;
    }
    lista.cantidad = 0;
    cout << "Lista vaciada con exito.\n";
}
