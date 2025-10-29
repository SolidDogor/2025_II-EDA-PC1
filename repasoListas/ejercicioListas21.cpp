/*
    Ejercicio 21: Lista de libros (ordenada + eliminación múltiple)
    Queremos almacenar libros ordenados por título (ascendente).
    Cada libro tiene:
        - titulo
        - autor
        - año
    Debe permitir:
        - Agregar libro (ordenado)
        - Mostrar todos
        - Eliminar un libro por título (una coincidencia)
        - Eliminar todos los libros de un autor
        - Vaciar lista
*/
#include <iostream>
#include <string>
#include <limits>
using namespace std;

//Estructuras
struct Libro {
    string titulo;
    string autor;
    int anio;
    Libro* siguiente;
};

struct Lista {
    Libro* cabeza = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarLibro(Lista&, const string&, const string&, int);
void mostrarLista(const Lista&);
void eliminarLibroTitulo(Lista&, const string&);
void eliminarLibroAutor(Lista&, const string&);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0, anio;
    string titulo, autor;
    do {
        cout << "\t---MENU---"
            << "\n1.- Agregar libro"
            << "\n2.- Mostrar lista"
            << "\n3.- Eliminar libro (por titulo)"
            << "\n4.- Eliminar libros (por autor)"
            << "\n5.- Vaciar lista"
            << "\n6.- Salir del programa\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Titulo: "; getline(cin, titulo);
                cout << "Autor: "; getline(cin, autor);
                cout << "Anio: "; cin >> anio;
                //fflush(stdin);
                agregarLibro(lista, titulo, autor, anio);
                break;
            case 2:
                cout << "Mostrando lista de libros: \n";
                if(verificarLista(lista)) mostrarLista(lista);
                else cout << "Lista vacia.\n";
                break;
            case 3:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Titulo: "; getline(cin, titulo);
                if(verificarLista(lista)) eliminarLibroTitulo(lista, titulo);
                else cout << "Agregue libros primero.\n";
                break;
            case 4:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Autor: "; getline(cin, autor);
                if(verificarLista(lista)) eliminarLibroAutor(lista, autor);
                else cout << "Agregue libros primero.\n";
                break;
            case 5:
                if(verificarLista(lista)) vaciarLista(lista);
                else cout << "Lista vacia\n";
                break;
            case 6:
                if(verificarLista(lista)) vaciarLista(lista);
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no disponible.\n";
        }
        system("pause");
        system("cls");
    } while(opcion != 6);
    return 0;
}

//Definiciones
void agregarLibro(Lista& lista, const string& titulo, const string& autor, int anio) {
    Libro* nuevo = new Libro{titulo, autor, anio, nullptr};
    if(!lista.cabeza || lista.cabeza->titulo > titulo) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
    } else {
        Libro* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->titulo <= titulo) {
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
    lista.cantidad++;
    cout << "[" << titulo << " - " << autor << ", " << anio << "] agregado con exito a la lista.\n";
}

void mostrarLista(const Lista& lista) {
    const Libro* aux = lista.cabeza;
    cout << "Cantidad de libros en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << "[" << aux->titulo << " - "
            << aux->autor << ", "
            << aux->anio << "]";
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarLibroTitulo(Lista& lista, const string& titulo) {
    //Caso 1: El libro está al inicio
    if(lista.cabeza->titulo == titulo) {
        Libro* aux = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        cout << "[" << aux->titulo 
            << " - " << aux->autor << ", "
            << aux->anio << "] eliminado con exito de la lista.\n";
        lista.cantidad--;
        delete aux;
        return;
    }
    //Caso 2: El libro se encuentra en otra parte
    Libro* previo = lista.cabeza;
    while(previo && previo->siguiente && previo->siguiente->titulo != titulo) {
        previo = previo->siguiente;
    }
    if(!previo) {
        cout << "No se encontro el titulo.\n";
        return;
    }
    Libro* aux = previo->siguiente;
    previo->siguiente = aux->siguiente;
    cout << "[" << aux->titulo 
        << " - " << aux->autor << ", "
        << aux->anio << "] eliminado con exito de la lista.\n";
    lista.cantidad--;
    delete aux;
}

void eliminarLibroAutor(Lista& lista, const string& autor) {
    if (!lista.cabeza) {
        cout << "Lista vacia.\n";
        return;
    }

    int borrados = 0;
    //Eliminación de todos los que estén al inicio
    while (lista.cabeza && lista.cabeza->autor == autor) {
        Libro* t = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete t;
        lista.cantidad--;
        borrados++;
    }
    Libro* prev = lista.cabeza;
    while (prev && prev->siguiente) {
        if (prev->siguiente->autor == autor) {
            Libro* t = prev->siguiente;
            prev->siguiente = t->siguiente;
            delete t;
            lista.cantidad--;
            borrados++;
        } else {
            prev = prev->siguiente;
        }
    }

    if (borrados == 0) cout << "No se encontraron libros de " << autor << ".\n";
    else cout << "Libros de " << autor << " eliminados: " << borrados << "\n";
}


void vaciarLista(Lista& lista) {
    while(lista.cabeza) {
        Libro* temp = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete temp;
    }
    lista.cabeza = nullptr;
    lista.cantidad = 0;
    cout << "Lista vaciada.\n";
}

bool verificarLista(const Lista& lista) {
    return lista.cabeza != nullptr;
}

