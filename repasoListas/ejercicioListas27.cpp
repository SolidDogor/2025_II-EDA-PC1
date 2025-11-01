/*
    Ejercicio 27 – Eliminar por rango de valores
        Tema: eliminación múltiple con dos límites
        Estructura: lista simple de float (precios, notas, etc.)
        Instrucciones:
            - Inserta valores sin orden específico (puede ser al inicio o final).
            - Implementa eliminarPorRango(Lista&, float min, float max) que elimine todos los nodos 
                cuyo valor esté dentro del rango [min, max].
            - Muestra cuántos fueron eliminados.
            - Asegúrate de manejar correctamente si los primeros o los últimos elementos caen dentro 
                del rango.
*/
#include <iostream>
#include <string>
#include <limits>
using namespace std;

//Estructuras
struct Producto {
    string descripcion;
    float precio;
    Producto* siguiente;
};

struct Lista {
    Producto* cabeza = nullptr;
    int cantidad = 0;
    float max = -std::numeric_limits<float>::infinity();
    float min =  std::numeric_limits<float>::infinity();
};

//Prototipos
void agregarProducto(Lista&, const string&, float);
void mostrarLista(const Lista&);
void eliminarPorRango(Lista&, float, float);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);
void borrarCabeza(Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0;
    string descripcion;
    float precio, min, max;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar producto\n"
            << "2.- Mostrar lista\n"
            << "3.- Eliminar por rango\n"
            << "4.- Vaciar lista\n"
            << "5.- Salir\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite la descripcion: "; cin >> descripcion;
                cout << "Digite el precio: "; cin >> precio;
                agregarProducto(lista,descripcion,precio);
                break;
            case 2:
                cout << "Mostrando lista:\n";
                if(verificarLista(lista)) mostrarLista(lista);
                else cout << "Lista vacia.\n";
                break;
            case 3:
                if(!verificarLista(lista)) {
                    cout << "Ingrese algun producto primero.\n";
                } else {
                    do {
                        cout << "Digite el minimo: "; cin >> min;
                        cout << "Digite el maximo: "; cin >> max;
                        if(min > max) cout << "Intente de nuevo. ";
                    } while (min > max);
                    
                    eliminarPorRango(lista,min,max);
                }
                break;
            case 4:
                if(!verificarLista(lista)) {
                    cout << "Ingrese algun producto primero.\n";
                } else {
                    do {
                        cout << "Seguro que desea vaciar la lista? [SI = 0 | NO = 1]\n";
                        cin >> opcion;
                        if(opcion != 0 && opcion != 1) cout << "Intente de nuevo. ";
                    } while (opcion != 0 && opcion != 1);
                    vaciarLista(lista);
                    opcion = 4;
                }
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                if(verificarLista(lista)) vaciarLista(lista);
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }
        system("pause");
        system("cls");
    } while(opcion != 5);
    return 0;
}

//Definiciones
void agregarProducto(Lista& lista, const string& descripcion, float precio) {
    Producto* nuevo = new Producto{descripcion, precio, nullptr};
    if(!lista.cabeza || lista.cabeza->precio > precio) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
        lista.min = precio;
    } else {
        Producto* aux = lista.cabeza;
        while(aux->siguiente && aux->siguiente->precio <= precio) {
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
    }
    lista.cantidad++;
    if(precio > lista.max) lista.max = precio;
    cout << descripcion << " - S/." << precio << " agregado con exito a la lista.\n";
}

void mostrarLista(const Lista& lista) {
    const Producto* aux = lista.cabeza;
    cout << "Cantidad de productos en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << aux->descripcion << " - S/." << aux->precio;
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void eliminarPorRango(Lista& lista, float min, float max) {
    if(min > lista.max || max < lista.min) {
        cout << "No se encontraron precios en ese rango.\n";
        return;
    }
    int borrados = 0;
    cout << "Lista antes de borrar:\n";
    mostrarLista(lista);
    while(lista.cabeza->precio > min && lista.cabeza->precio < max) {
        borrarCabeza(lista);
        borrados++;
        lista.cantidad--;
    }
    if(borrados > 0) {
        cout << "Lista tras borrar:\n";
        mostrarLista(lista);
        return;
    }
    if (!lista.cabeza) {
        lista.min =  std::numeric_limits<float>::infinity();
        lista.max = -std::numeric_limits<float>::infinity();
        cout << "Eliminados: " << borrados << "\n";
        return;
    }
    Producto* aux = lista.cabeza;
    while(aux->siguiente && aux->siguiente->precio < max) {
        if(aux->siguiente->precio < max) {
            Producto* temp = aux->siguiente;
            aux->siguiente = temp->siguiente;
            borrados++;
            lista.cantidad--;
            delete temp;
        } else {
            aux = aux->siguiente;
        }
    }
    cout << "Lista tras borrar:\n";
    mostrarLista(lista);

    lista.min = lista.cabeza->precio;
    Producto* temp = lista.cabeza;
    while (temp->siguiente) temp = temp->siguiente;
    lista.max = temp->precio;

    cout << "Eliminados: " << borrados << "\n";
}

void vaciarLista(Lista& lista) {
    while(lista.cabeza) borrarCabeza(lista);
    lista.cabeza = nullptr;
    lista.cantidad = 0;
    lista.min =  std::numeric_limits<float>::infinity();
    lista.max = -std::numeric_limits<float>::infinity();
    cout << "Lista vaciada con exito.\n";
}

bool verificarLista(const Lista& lista) {
    return lista.cabeza != nullptr;
}

void borrarCabeza(Lista& lista) {
    Producto* aux = lista.cabeza;
    lista.cabeza = lista.cabeza->siguiente;
    delete aux;
}
