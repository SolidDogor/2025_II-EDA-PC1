//Insertar elementos en una cola
#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo *siguiente;
};

//Prototipo de función
void agregarElemento(Nodo *&, Nodo *&, int );

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

    return 0;
}

void agregarElemento(Nodo *&frente, Nodo *&fin, int n) {
    Nodo *nuevo_nodo = new Nodo();
    nuevo_nodo->dato = n;
    nuevo_nodo->siguiente = NULL;

    (frente == NULL)? frente = nuevo_nodo : fin->siguiente = nuevo_nodo;

    fin = nuevo_nodo;
    cout << "Elemento " << n << " agregado con exito a la cola\n";
}
