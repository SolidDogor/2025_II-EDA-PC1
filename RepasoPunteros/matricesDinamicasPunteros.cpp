/*
    Matrices dinámicas
    
    Ejemplo: Rellenar una matriz NxM y mostrar su contenido

    **puntero_matriz -> *puntero_fila -> [int] [int]
                        *puntero_fila -> [int] [int]
                        *puntero_fila -> [int] [int]
    
    1 2 3   1 -> 2 3
    4 5 6   4 -> 5 6
    7 8 9   7 -> 8 9
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

//Prototipo de función
void pedirDatos();
void mostrarMatriz(int **, int, int);

int **puntero_matriz, nFilas, nColumnas;

int main () {
    pedirDatos();
    mostrarMatriz(puntero_matriz,nFilas,nColumnas);

    for (int i = 0; i < nFilas; i++) {
        delete [] puntero_matriz[i];
    }

    delete [] puntero_matriz;
    return 0;
}

void pedirDatos() {
    cout << "Digite el numero de filas: "; cin >> nFilas;
    cout << "Digite el numero de columnas: "; cin >> nColumnas;

    puntero_matriz = new int*[nFilas];          //Reservando memoria para las filas
    for (int i = 0; i < nFilas; i++) {
        puntero_matriz[i] = new int[nColumnas]; //Reservando memoria para las columnas
    }

    cout << "Digitando los elementos de la matriz: ";
    for (int i = 0; i < nFilas; i++) {
        for (int j = 0; j < nColumnas; j++) {
            cout << "Digite un numero [" << i << "][" << j << "]: ";
            cin >> *(*(puntero_matriz+i)+j);
        }
    }
}

void mostrarMatriz (int **puntero_matriz, int nFilas, int nColumnas) {
    cout << "\nImprimiendo matriz\n";
    for (int i = 0; i < nFilas; i++) {
        for (int j = 0; j < nColumnas; j++) {
            cout << *(*(puntero_matriz+i)+j) << " ";
        }
        cout << "\n";
    }
}