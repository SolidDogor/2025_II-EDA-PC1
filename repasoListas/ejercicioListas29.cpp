/*
    Ejercicio 29 – Lista doblemente enlazada de transacciones
    Crea una lista doblemente enlazada donde cada transacción tiene:
        - id (int autoincremental)
        - monto (float)
        - descripción (string)
    Debe permitir:
        - Agregar transacción al final
        - Mostrar todas las transacciones de inicio a fin
        - Mostrar todas las transacciones de fin a inicio
        - Buscar una transacción por id
        - Eliminar una transacción por id
        - Vaciar la lista
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Transaccion {
    int id;
    float monto;
    string descripcion;
    Transaccion* siguiente;
    Transaccion* anterior;
};

struct Lista  {
    Transaccion* inicio = nullptr;
    Transaccion* fin = nullptr;
    int cantidad = 0;
    int maxId = 0;
};

//Prototipos
void agregarTransaccion(Lista&, float, const string&);
void mostrarTransaccionesInicioFin(const Lista&);
void mostrarTransaccionesFinInicio(const Lista&);
void buscarTransaccionId(const Lista&, const int);
void eliminarTransaccionId(Lista&, const int);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);

int id = 1;

//Main
int main() {
    Lista lista;
    int opcion = 0, idDigitado;
    float monto = 0.0f;
    string descripcion;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar una transaccion\n"
            << "2.- Mostrar transacciones (inicio a final)\n"
            << "3.- Mostrar transacciones (final a inicio)\n"
            << "4.- Buscar transaccion por ID\n"
            << "5.- Eliminar transaccion por ID\n"
            << "6.- Vaciar lista\n"
            << "7.- Salir del programa\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite la descripcion: "; cin >> descripcion;
                cout << "Digite el monto: "; cin >> monto;
                agregarTransaccion(lista,monto,descripcion);
                break;
            case 2:
                if(verificarLista(lista)) {
                    cout << "Imprimiendo transacciones: ";
                    mostrarTransaccionesInicioFin(lista);
                } else {
                    cout << "Ingrese alguna transaccion primero.\n";
                }
                break;
            case 3:
                if(verificarLista(lista)) {
                    cout << "Imprimiendo transacciones: ";
                    mostrarTransaccionesFinInicio(lista);
                } else {
                    cout << "Ingrese alguna transaccion primero.\n";
                }
                break;
            case 4:
                if(verificarLista(lista)) {
                    cout << "Digite el id: "; cin >> idDigitado;
                    buscarTransaccionId(lista, idDigitado);
                } else {
                    cout << "Ingrese alguna transaccion primero.\n";
                }
                break;
            case 5:
                if(verificarLista(lista)) {
                    cout << "Digite el id: "; cin >> idDigitado;
                    eliminarTransaccionId(lista, idDigitado);
                } else {
                    cout << "Ingrese alguna transaccion primero.\n";
                }
                break;
            case 6:
                cout << "Vaciando lista.\n";
                if(!verificarLista(lista)) cout << "Lista vacia.\n";
                else vaciarLista(lista);
                break;
            case 7:
                cout << "Saliendo del programa...\n";
                if(verificarLista(lista)) vaciarLista(lista);
                break;
            default:
                cout << "Opcion no disponible.\n";
                break;
        }
        system("pause");
        system("cls");
    } while(opcion != 7);
    return 0;
}

//Definiciones
void agregarTransaccion(Lista& lista, float monto, const string& descripcion) {
    int idActual = id++;
    Transaccion* nueva = new Transaccion{idActual, monto, descripcion, nullptr, nullptr};
    if(!lista.fin) {
        lista.fin = lista.inicio = nueva;
    } else {
        lista.fin->siguiente = nueva;
        nueva->anterior = lista.fin;
        lista.fin = nueva;
    }
    cout << idActual << ": " << descripcion << " [S./"<< monto << "]" 
        << " agregada con exito a la lista.\n";
    lista.cantidad++;
    if(idActual > lista.maxId) lista.maxId = idActual;
}

void mostrarTransaccionesInicioFin(const Lista& lista) {
    Transaccion* aux = lista.inicio;
    cout << "Cantidad de transacciones en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << aux->id << ": " << aux->descripcion << "[S/." << aux->monto << "]";
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void mostrarTransaccionesFinInicio(const Lista& lista) {
    Transaccion* aux = lista.fin;
    cout << "Cantidad de transacciones en lista: " << lista.cantidad << "\n";
    while(aux) {
        cout << aux->id << ": " << aux->descripcion << "[S/." << aux->monto << "]";
        (aux->anterior) ? cout << ",\n" : cout << ".\n";
        aux = aux->anterior;
    }
}

void buscarTransaccionId(const Lista& lista, const int id) {
    if(id > lista.maxId && id <= 0) {
        cout << "Transaccion no existente.\n";
        return;
    }
    int mid = (lista.maxId + 1) / 2;
    const Transaccion* aux = (id > mid ? lista.fin : lista.inicio);

    if(id > mid) {
        while(aux && aux->id != id) {
            aux = aux->anterior;
        }
    } else {
        while(aux && aux->id != id) {
            aux = aux->siguiente;
        }
    }

    if (!aux) {
        cout << "Transaccion no encontrada.\n";
        return;
    }
    cout << aux->id << ": " << aux->descripcion << "[S/." << aux->monto << "]";
}

void eliminarTransaccionId(Lista& lista, const int id) {  // <- quita 'const'
    if (id <= 0 || id > lista.maxId) {
        cout << "Transaccion no existente.\n";
        return;
    }
    if (!lista.inicio) { cout << "Lista vacia.\n"; return; }

    int mid = (lista.maxId + 1) / 2;
    Transaccion* aux = (id > mid ? lista.fin : lista.inicio);

    if (id > mid) {
        while (aux && aux->id != id) aux = aux->anterior;
    } else {
        while (aux && aux->id != id) aux = aux->siguiente;
    }
    if (!aux) { cout << "Transaccion no encontrada.\n"; return; }

    // Desenlazar con casos borde
    Transaccion* pre = aux->anterior;
    Transaccion* sig = aux->siguiente;

    if (!pre && !sig) {
        //Único nodo
        lista.inicio = lista.fin = nullptr;
    } else if (!pre) {
        //Primer nodo
        lista.inicio = sig;
        sig->anterior = nullptr;
    } else if (!sig) {
        //Último nodo
        lista.fin = pre;
        pre->siguiente = nullptr;
    } else {
        //Nodo medio
        pre->siguiente = sig;
        sig->anterior  = pre;
    }

    cout << aux->id << ": " << aux->descripcion << " eliminada con exito.\n";
    delete aux;
    lista.cantidad--;
}

void vaciarLista(Lista& lista) {
    while(lista.inicio) {
        Transaccion* temp = lista.inicio;
        lista.inicio = lista.inicio->siguiente;
        delete temp;
    }
    lista.inicio = nullptr;
    lista.fin = nullptr;
    lista.cantidad = 0;
    lista.maxId = 0;
    id = 1;
    cout << "Lista vaciada con exito.\n";
}

bool verificarLista(const Lista& lista) {
    return lista.inicio != nullptr;
}
