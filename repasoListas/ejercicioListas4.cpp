/*
	Ejercicio 4: Hacer una lista de 5 estudiantes con distintas notas
				Mostrar la lista completa en orden descendente, el estudiante con mayor nota
					y el estudiante con menor nota
*/
#include <iostream>
#include <string>
using namespace std;

struct Alumno {
	string nombre;
	int nota;
	Alumno *siguiente;
};

struct Lista {
    Alumno *cabeza = nullptr;
    Alumno *mejorAlumno = nullptr;
    Alumno *peorAlumno = nullptr;
};

//Prototipo de funciones
void insertarAlumno(Lista &, string, int);
void mostrarLista(const Lista &);


int main() {
    Lista lista;
	int cantidad = 5, nota;
	string nom;

	while (cantidad--) {
		cout << "Digite el nombre del alumno: "; cin >> nom;
		cout << "Digite la nota de " << nom << ": "; cin >> nota;
		insertarAlumno(lista, nom, nota);
	}

    mostrarLista(lista);
	
	cout << "\nMejor alumno: " << lista.mejorAlumno->nombre << " ( " << lista.mejorAlumno->nota << " )\n";
	cout << "Peor alumno: " << lista.peorAlumno->nombre << " ( " << lista.peorAlumno->nota << " )\n";

	return 0;
}

void insertarAlumno(Lista &lista, string nombre, int nota) {
	Alumno *nuevo_alumno = new Alumno{nombre,nota,nullptr};

	if(lista.cabeza == nullptr || lista.cabeza->nota <= nota) {
		nuevo_alumno->siguiente = lista.cabeza;
		lista.cabeza = nuevo_alumno;
	} else {
		Alumno *aux = lista.cabeza;
		while(aux->siguiente && aux->siguiente->nota > nota) {
			aux = aux->siguiente;
		}
		nuevo_alumno->siguiente = aux->siguiente;
		aux->siguiente = nuevo_alumno;
	}

    if (lista.mejorAlumno == nullptr || nota > lista.mejorAlumno->nota) lista.mejorAlumno = nuevo_alumno;
    if (lista.peorAlumno == nullptr || nota < lista.peorAlumno->nota) lista.peorAlumno = nuevo_alumno;

	cout << "Alumno: " << nombre << " insertado a la lista.\n";
}

void mostrarLista(const Lista &lista) {
	Alumno *p = lista.cabeza;
	cout << "\n------Lista de alumnos------\n";
	while (p) {
		cout << "{Alumno: " << p->nombre << " , ";
		cout << "Nota: " << p->nota << "}\n";
		p = p->siguiente;
	}
}