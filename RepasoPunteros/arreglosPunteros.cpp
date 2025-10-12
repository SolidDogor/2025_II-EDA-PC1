//Correspondencia entre arrays y punteros

#include <iostream>
using namespace std;

int main() {
    int numeros [] = {1,2,3,4,5};
    int *dir_numeros;

    dir_numeros = numeros;  //Para asignar un arreglo a una variable puntero se igual de esta manera

    for (int i = 0; i < 5; i++) {
        //La dirección de un valor del array está 4 bits por delante del anterior
        cout << "Posicion de memoria: " << numeros[i] << " es: " << dir_numeros++ << "\n";
    }

    return 0;
}