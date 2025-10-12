/*
    Ejercicio 4: Pedir su nombre al usuario y devolver el número de vocales que hay.
    NOTA: Recuerda que debes utilizar punteros.
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//Prototipo de funciones
void pedirDatos();
int cantidadVocales(char *);

char nombreUsuario[30];

int main() {
    pedirDatos();
    cout << "Numero de vocales de " << nombreUsuario << " es: " 
        << cantidadVocales(nombreUsuario) << "\n";
    
    return 0;
}

void pedirDatos() {
    cout << "Digite su nombre: "; 
    cin.getline(nombreUsuario,30,'\n');

    strupr(nombreUsuario);  //Transformando el nombre a MAYUSCULAS
}

int cantidadVocales(char *nombre) {
    int cant = 0;
    
    while(*nombre) {
        switch(*nombre) {
            case 'A':  
            case 'E':
            case 'I':   
            case 'O':   
            case 'U':   cant++;
        }
        nombre++;
    }

    return cant;
}