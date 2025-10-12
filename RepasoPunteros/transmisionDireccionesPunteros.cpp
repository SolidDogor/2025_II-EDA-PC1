/*
    Transmision de direcciones

    Ejemplo: Intercambiare el valor de 2 variables
*/

#include <iostream>
#include <stdlib.h>
using namespace std;

//Prototipo de funcion
void intercambio(float *, float *);

int main () {
    float num1 = 20.8, num2 = 6.78;
    
    cout << "Numero 1: " << num1 << "\n";
    cout << "Numero 2: " << num2 << "\n";

    intercambio(&num1, &num2);
    cout << "Depues del intercambio:\n";

    cout << "Numero 1: " << num1 << "\n";
    cout << "Numero 2: " << num2 << "\n";

    return 0;
}

//Definicion de funcion
void intercambio(float *dirNum1, float *dirNum2) {
    float aux;
    aux = *dirNum1;
    *dirNum1 = *dirNum2;
    *dirNum2 = aux;
}