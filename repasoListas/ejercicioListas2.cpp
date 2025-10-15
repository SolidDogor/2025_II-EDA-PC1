/*
    Ejercicio 2: Crear una lista que almanece 'n' numeros reales
                    Calcular la suma y promedio de estos
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

struct Nodo{
    float dato;
    Nodo *siguiente;
};

//Prototipos de funciones
void insertarElemento(Nodo *&, float);
void mostrarLista(Nodo *);
float calcularSuma(Nodo *);
float calcularPromedio(float);
void menu();

Nodo *lista = NULL;
int cantidad = 0;

int main() {
    menu();
    return 0;
}

//Definicion de funciones
void insertarElemento(Nodo *&lista, float nota) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = nota;
    nuevo_nodo->siguiente = NULL;

    Nodo *aux1 = lista;
    Nodo *aux2 = NULL;

    while (aux1 != NULL && aux1->dato < nota) {
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }

    if (aux2 == NULL) { 
        nuevo_nodo->siguiente = lista;
        lista = nuevo_nodo;
    } else {
        aux2->siguiente = nuevo_nodo;
        nuevo_nodo->siguiente = aux1;
    }

    cantidad++;
    cout << "Nota " << nota << " insertada con exito.\n";
}

void mostrarLista(Nodo *lista) {
    if (!lista) { cout << "(lista vacia)\n"; return; }
    while (lista != NULL) {
        (lista->siguiente == NULL) ? cout << lista->dato << ".\n" : cout << lista->dato << " , ";
        lista = lista->siguiente;
    }
}

float calcularSuma(Nodo *lista) {
    float suma = 0;
    while (lista != NULL) {
        suma += lista->dato;
        lista = lista->siguiente;
    }
    return suma;
}

float calcularPromedio(float sumaNotas) {
    if (cantidad == 0) return 0.0f;
    return sumaNotas / cantidad;
}

void menu () {
    float n;
    int opcion = 0;

    do {
        cout << "\n\t---Menu---\n";
        cout << "1.- Agregar elemento\n2.- Calcular suma de notas\n3.- Calcular promedio\n4.- Salir\n";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite un numero: "; cin >> n;
            insertarElemento(lista, n);
            cout << "Lista hasta el momento: ";
            mostrarLista(lista);
            break;
        case 2:
            cout << "Suma de notas: " << calcularSuma(lista) << "\n";
            break;
        case 3: {
            float sumaNotas = calcularSuma(lista);
            cout << "Promedio de notas: " << calcularPromedio(sumaNotas) << "\n";
            break;
        }
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
