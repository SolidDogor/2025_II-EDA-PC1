/*
    Punteros - Declaración de punteros
    
    &n = La dirección de n
    *n = La variable cuya dirección está almacenada en n
*/

#include <iostream>

using namespace std;

int main() {
    int num, *dir_num;
    num = 20;
    dir_num = &num;

    cout << "Numero: " << *dir_num << "\n";
    cout << "Direccion de memoria: " << dir_num << "\n";
    
    return 0;
}