#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "nodo.h"

using namespace std;

int main() {
  Nodo* arbol = NULL;
  int numero = 0;
  srand(time(NULL));
  int lista[]= {91,106,99,46,32,39,50,81,80,82};

  //Insertamos valores al arbol
  /*
  for(int i = 0; i < 20; i++){
    numero = 20 + rand()%91;
    insertarNodoArbol(arbol, numero);
    }
    */

  for(int i = 0; i < 10; i++){
    numero = lista[i];
    insertarNodoArbol(arbol, numero);
    }
  

  mostrarArbol2(arbol, 0,-1);
  cout << endl<<"PreOrden: "<<endl;
  preOrden(arbol);
  cout << endl<<"InOrden: "<<endl;
  inOrden(arbol);
  cout << endl<<"PostOrden: "<<endl;
  postOrden(arbol);
  cout << endl<<"Eliminar nodo: "<<endl;
  eliminarNodo(arbol, 46);
  mostrarArbol2(arbol, 0,-1);
  
  return 0;
}
