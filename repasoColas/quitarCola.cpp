//Insertar elementos en una cola
#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;
};

//Prototipo de función
void agregarElemento(Nodo *&, Nodo *&, int);
void quitarElemento(Nodo *&, Nodo *&, int &);

int main () {
    Nodo *frente = NULL;
    Nodo *fin = NULL;

    int n; 
    
    cout << "Digite un dato: "; cin >> n;
    agregarElemento(frente, fin, n);

    cout << "Digite un dato: "; cin >> n;
    agregarElemento(frente, fin, n);

    cout << "Digite un dato: "; cin >> n;
    agregarElemento(frente, fin, n);

    cout << "Digite un dato: "; cin >> n;
    agregarElemento(frente, fin, n);

    cout << "Quitando elementos de la cola: ";
    while (frente != NULL) {
        quitarElemento(frente,fin,n);
        (frente != NULL) ? cout << n << " , " : cout <<  n << ".";
    }

    return 0;
}

//Definición de funciones
void agregarElemento(Nodo *&frente, Nodo *&fin, int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->siguiente = NULL;

    (frente == NULL)? frente = nuevo_nodo : fin->siguiente = nuevo_nodo;

    fin = nuevo_nodo;
    cout << "Elemento " << n << " agregado con exito a la cola\n";
}

void quitarElemento(Nodo *&frente, Nodo *&fin, int &n) {
    n = frente -> dato;
    Nodo *aux = frente;

    if (frente == fin) {
        frente = NULL;
        fin = NULL;
    } else {
        frente = frente -> siguiente;
    }

    delete aux;
}