#include <iostream>

using namespace std;

// Nodo para el arbol binario
struct Nodo {
  int data;
  Nodo *derecha;
  Nodo *izquierda;
};

Nodo *nuevoNodo(int data){
  Nodo *nodo = new Nodo();

  nodo->data = data;
  nodo->derecha = NULL;
  nodo->izquierda = NULL;

  return nodo;
}

void insertarNodoArbol(Nodo *&arbol, int data){
  if(arbol == NULL){
    Nodo *nodo = nuevoNodo(data);
    arbol = nodo;
  }
  else {
    if(data < arbol->data){
      insertarNodoArbol(arbol->izquierda, data);
    }
    else {
      insertarNodoArbol(arbol->derecha, data);
    }
  }
}


void mostrarArbol(Nodo *arbol, int contador){
  if(arbol == NULL){
    return;
  }
  else {
    mostrarArbol(arbol->derecha, contador+1);
    for(int i = 0; i < contador; i++){
      cout << "   ";
    }
    cout << arbol->data << endl;
    mostrarArbol(arbol->izquierda, contador+1);
  }
}

void mostrarArbol2(Nodo *arbol, int contador, int previo){
  if(arbol == NULL){
    return;
  }
  else {
    
    mostrarArbol2(arbol->derecha, contador+1, arbol->data);
    //for(int i = 0; i < contador; i++){
    cout << "Altura: " << contador << " Nodo: " << arbol->data << " Padre: "<< previo <<endl;
    //}
    //cout << arbol->data << endl;
    mostrarArbol2(arbol->izquierda, contador+1, arbol->data);
  }
}

bool busquedaNodo(Nodo *arbol, int data){
  if (arbol == NULL){
    return false;
  }
  else if (arbol->data == data){
    return true;
  }
  else if(data < arbol->data){
    return busquedaNodo(arbol->izquierda, data);
  }
  else {
    return busquedaNodo(arbol->derecha, data);
  }
}
void preOrden(Nodo *arbol){
  if(arbol == NULL){
    return;
  } else {
    cout << arbol->data << " - ";
    preOrden(arbol->izquierda);
    preOrden(arbol->derecha);
  }   
}

void postOrden(Nodo *arbol){
  if(arbol == NULL){
    return;
  } else{
    postOrden(arbol->izquierda);
    postOrden(arbol->derecha);
    cout << arbol->data << " - ";
  }
}
void inOrden(Nodo *arbol){
  if(arbol == NULL){
    return;
  } else{
    inOrden(arbol->izquierda);
    cout << arbol->data << " - ";
    inOrden(arbol->derecha);
  }
}

void eliminarNodo(Nodo *arbol, int dato){
  if(arbol == NULL){
    return;
  }
  else if(dato < arbol->data){
    eliminarNodo(arbol->izquierda, dato);
  }
  else if(dato > arbol->data){
    eliminarNodo(arbol->derecha, dato);
  }
  else {
    Nodo *p, *q;
    q = arbol;
    p = q->izquierda;
    while(p->derecha != NULL){
      q = p;
      p = p->derecha;
    }
    arbol->data = p->data;
    q->derecha = p->izquierda;
    delete p;
  }
}
