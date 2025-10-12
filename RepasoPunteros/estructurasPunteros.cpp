//Puntero a estructuras
#include <iostream>
using namespace std;

struct Persona {
    char nombre[30];
    int edad;
} persona, *puntero_persona = &persona;

//Prototipo de función
void pedirDatos();
void mostrarDatos(Persona *);

int main() {
    pedirDatos();
    mostrarDatos(puntero_persona);
    return 0;
}

void pedirDatos() {
    cout << "Digite su nombre: ";
    cin.getline(puntero_persona->nombre,30,'\n');
    cout << "Digite su edad: ";
    cin >> puntero_persona->edad;
}

void mostrarDatos(Persona *puntero_persona) {
    cout << "Nombre: " << puntero_persona->nombre; 
    cout << "\nEdad: " << puntero_persona->edad;
}