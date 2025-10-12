/*
    Asignación dinámica de arreglos

    new: Reserva el número de bytes solicitado por la declaración
    delete: Libera un bloque de bytes reservado con anterioridad

    Ejemplo: Pedir al usuario n calificaciones y almacenarlos en un arreglo dinámico
*/

#include <iostream>
#include <stdlib.h>     //Librería para que new y delete funcionen
using namespace std;

//Prototipo de función
void pedirNotas();
void mostrarNotas();

int numCalif, *calif;

int main() {
    pedirNotas();
    mostrarNotas();

    delete[] calif; //Liberando los bytes utilizados

    return 0;
}

void pedirNotas() {
    cout << "Digite el numero de calificaciones: "; cin >> numCalif;

    calif = new int[numCalif];

    for (int i = 0; i < numCalif; i++) {
        cout << "Ingrese una nota: "; cin >> calif[i];
    }
}

void mostrarNotas() {
    cout << "\nMostrando notas\n";
    for (int i = 0; i < numCalif; i++) {
        cout << calif[i] << "\n";
    }
}