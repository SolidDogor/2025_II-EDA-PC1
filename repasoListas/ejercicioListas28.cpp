/*
    Ejercicio 28: Lista de calificaciones por alumno
        Crear un programa que gestione alumnos y sus notas
        Cada alumno tiene:
            - nombre (string)
            - una lista enlazada de notas (float)
        Debe permitir:
            - Registrar un alumno (ordenado alfabeticamente)
            - Agregar una nota a un alumno
            - Mostrar todos los alumnos con sus notas
            - Calcular el promedio de un alumno
            - Vaciar toda la lista
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Nota {
    float nota;
    Nota* siguiente;
};

struct Alumno {
    string nombre;
    Nota* listaNotas;
    Alumno* siguiente;
    float sumaNotas;
    int cantidadNotas;
};

struct Lista {
    Alumno* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipado
void registrarAlumno(Lista&, const string&);
void registrarNota(Lista&, const string&, float);
void mostrarAlumnos(const Lista&);
void mostrarNotas(const Alumno*);
void mostrarPromedio(Lista&, const string&);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);
Alumno* buscarAlumno(Lista&, const string&);

//Main
int main() {
    Lista lista;
    int opcion = 0;
    float nota = 0.0f;
    string nombre;
    do {
        cout << "\t---MENU---\n"
            << "1.- Registrar un alumno\n"
            << "2.- Agregar nota a un alumno\n"
            << "3.- Mostrar alumnos con sus notas\n"
            << "4.- Calcular el promedio de un alumno\n"
            << "5.- Vaciar lista\n"
            << "6.- Salir del programa\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el nombre: "; cin >> nombre;
                registrarAlumno(lista,nombre);
                break;
            case 2:
                if(verificarLista(lista)) {
                    cout << "Digite el nombre: "; cin >> nombre;
                    cout << "Digite la nota: "; cin >> nota;
                    registrarNota(lista,nombre,nota);
                } else {
                    cout << "Ingrese algun alumno primero.\n";
                }
                break;
            case 3:
                if(verificarLista(lista)) {
                    cout << "Imprimiendo alumnos y notas: \n";
                    mostrarAlumnos(lista);
                } else {
                    cout << "Ingrese algun alumno primero.\n";
                }
                break;
            case 4:
                if(verificarLista(lista)) {
                    cout << "Digite el nombre: "; cin >> nombre;
                    mostrarPromedio(lista,nombre);
                } else {
                    cout << "Ingrese algun alumno primero.\n";
                }
                break;
            case 5:
                cout << "Vaciando lista.\n";
                if(!verificarLista(lista)) cout << "Lista vacia.\n";
                else vaciarLista(lista);
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                if(verificarLista(lista)) vaciarLista(lista);
                break;
            default:
                cout << "Opcion no disponible.\n";
                break;
        }
        system("pause");
        system("cls");
    } while(opcion != 6);
    return 0;
}

//Definiciones
void registrarAlumno(Lista& lista, const string& nombre) {
    Alumno* nuevo = new Alumno {nombre, nullptr, nullptr, 0, 0};
    if(!lista.cabeza || lista.cabeza->nombre > nombre) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
    } else {
        Alumno* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->nombre <= nombre) {
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
    lista.cantidad++;
    cout << nombre << " registrado con exito en lista.\n";
}

void registrarNota(Lista& lista, const string& nombre, float nota) {
    Alumno* a = buscarAlumno(lista,nombre);
    if(!a) {
        cout << "Alumno no encontrado.\n";
        return;
    }
    Nota* nueva = new Nota{nota,nullptr};
    nueva->siguiente = a->listaNotas;
    a->listaNotas = nueva;
    a->sumaNotas += nota;
    a->cantidadNotas++;
    cout << "Nota registrada con exito.\n";
    return;
}

void mostrarAlumnos(const Lista& lista) {
    const Alumno* aux = lista.cabeza;
    cout << "Cantidad de alumnos en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << aux->nombre << ":\n";
        mostrarNotas(aux);
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void mostrarNotas(const Alumno* alumno) {
    const Nota* aux = alumno->listaNotas;
    int contador = 1;
    if(!aux) {
        cout << "\tNo hay notas registradas.\n";
        return;
    }
    cout << "Cantidad de notas: " << alumno->cantidadNotas << ":\n"; 
    while(aux) {
        cout << "\t" << contador++ << ".- " << aux->nota;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void mostrarPromedio(Lista& lista, const string& nombre) {
    Alumno* a = buscarAlumno(lista,nombre);
    if(!a) {
        cout << "Alumno no registrado.\n";
        return;
    }
    if(a->cantidadNotas == 0) {
        cout << "No hay notas registradas.\n";
        return;
    }
    
    float promedio = lista.cabeza->sumaNotas / lista.cabeza->cantidadNotas;
    cout << "Promedio de " << nombre << ": " << promedio << "\n";
}

void vaciarLista(Lista& lista) {
    while (lista.cabeza) {
        Nota* n = lista.cabeza->listaNotas;
        while (n) {
            Nota* t = n;
            n = n->siguiente;
            delete t;
        }
        Alumno* temp = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete temp;
    }
    lista.cantidad = 0;
    cout << "Lista vaciada con exito.\n";
}


bool verificarLista(const Lista& lista) {
    return lista.cabeza != nullptr;
}

Alumno* buscarAlumno(Lista& lista, const string& nombre) {
    Alumno* a = lista.cabeza;
    while(a && a->nombre != nombre) a = a->siguiente;
    return a;
}