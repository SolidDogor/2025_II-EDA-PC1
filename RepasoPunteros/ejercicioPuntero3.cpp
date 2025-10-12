/*
    Ejercicio 3: Pedir al usuario N números, almacenarlos en un arreglo dinámico.
    Posteriormente ordenar los números en orden ascendente y mostrarlos en pantalla.
    NOTA: Utilizar cualquier método de ordenamiento
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

//Prototipo de funciones
void pedirDatos();
int ordenarDatos();
int intercambiar(int *, int *);
void mostrarArreglo();

int cantidad, *numeros;

int main() {
    pedirDatos();
    cout << "---Arreglo sin ordenar---";
    mostrarArreglo();
    ordenarDatos();
    cout << "---Arreglo tras ordenar---";
    mostrarArreglo();    
    
    return 0;
}

void pedirDatos() {
    cout << "Digite la cantidad de numeros: "; cin >> cantidad;

    numeros = new int[cantidad];

    for (int i = 0; i < cantidad; i++) {
        cout << "Ingrese un numero: "; cin >> numeros[i];
    }
}

int ordenarDatos() {
    for (int i = 0; i < cantidad; i++) {
        for (int j = 0; j < i; j++) {
            if (*(numeros+j) > *(numeros+i)) intercambiar(numeros+i,numeros+j);
        }
    }
}

int intercambiar(int *n1, int *n2) {
    int aux;
    aux = *n1;
    *n1 = *n2;
    *n2 = aux;
}

void mostrarArreglo() {
    cout << "\n";
    for (int i = 0; i < cantidad; i++) {
        cout << *(numeros+i) << " ";
    }
    cout << "\n";
}