/*
    Ejercicio 5: Hacer una estructura llamada alumno, en la cual se tendrán los siguientes campos: 
    Nombre, edad, promedio. Pedir datos al usuario para 3 alumnos, comprobar cuál de los 3 tiene 
    el mejor promedio y posteriormente imprimir los datos del alumno.
    N OTA: Usar punteros a estructura
*/

#include <iostream>
using namespace std;

//Estructuras
struct Alumno{
    char nombre[30];
    int edad;
    float promedio;
} alumno[3], *puntero_alumno = alumno;

//Prototipo de funciones
void pedirDatos();
int mejorPromedio();
void imprimirMejorAlumno(int);

int main () {
    pedirDatos();
    imprimirMejorAlumno(mejorPromedio());
    return 0;
}

//Declaración de funciones
void pedirDatos() {
    for (int i = 0; i < 3; i++) {
        fflush(stdin);
        cout << "---Datos del alumno #" << i + 1 << "---\n";
        cout << "Ingrese el nombre: "; cin.getline((puntero_alumno+i)->nombre,30,'\n');
        cout << "Ingrese la edad: "; cin >> (puntero_alumno+i)->edad;
        cout << "Ingrese el promedio: "; cin >> (puntero_alumno+i)->promedio;
    }
}

int mejorPromedio() {
    float max = 0;
    int valor = 0;

    for (int i = 0; i < 3; i++) {
        if (((puntero_alumno+i)->promedio) > max) {
            max = (puntero_alumno+i)->promedio;
            valor = i;
        }
    }

    return valor;
}

void imprimirMejorAlumno(int i) {
    cout << "---Datos del mejor alumno---";
    cout << "\nNombre: " << (puntero_alumno+i)->nombre;
    cout << "\nEdad: " << (puntero_alumno+i)->edad;
    cout << "\nPromedio: " << (puntero_alumno+i)->promedio;
}