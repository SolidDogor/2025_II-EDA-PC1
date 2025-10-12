/*
    Ejercicio 2: Rellenar un array de 10 números, posteriormente utilizando punteros
    indicar cuales son numeros pares y su posicion en memoria
*/

#include <iostream>
using namespace std;
const int cantidad = 10;

int main() {
    int numeros[cantidad], *dir_numeros;    

    for (int i = 0; i < cantidad; i++) {
        cout << "Ingrese el valor #" << i + 1 << " del arreglo: "; 
        cin >> numeros[i];
    }

    dir_numeros = numeros;

    for (int i = 0; i < cantidad; i++) {
        if (*dir_numeros % 2 == 0) {
            cout << "Numero " << *dir_numeros;
            cout << " es par con direccion de memoria: " << dir_numeros << "\n";
        }
        dir_numeros++;
    }

    return 0;
}