/*
    Ejercicio 1: Comprobar si un número es par o impar y señalar la posición de memoria del número.
    Se usará punteros.
*/

#include <iostream>

using namespace std;

int main() {
    int num, *dir_num;

    cout << "Ingrese el numero: "; cin >> num;
    dir_num = &num;
    
    if (*dir_num % 2 == 0) cout << "Numero par con direccion: " << dir_num << "\n";
    else cout << "Numero impar con direccion: " << dir_num << "\n";

    return 0;
}