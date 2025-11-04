/*
    Ejercicio 31 – Lista doblemente enlazada de clientes VIP
    Crea una lista doblemente enlazada donde cada cliente tiene:
        - nombre (string)
        - saldo (float)
    Debe permitir:
        - Agregar cliente al final
        - Mostrar clientes de inicio a fin
        - Mostrar clientes de fin a inicio
        - Buscar un cliente por nombre y actualizar su saldo
        - Eliminar un cliente por nombre
        - Vaciar lista
        - Salir
*/
#include <iostream>
#include <string>
using namespace std;

//Estructuras
struct Cliente {
    string nombre;
    float saldo;
    Cliente* siguiente;
    Cliente* anterior;
};

struct Lista {
    Cliente* frente = nullptr;
    Cliente* final = nullptr;
    int cantidad = 0;
};

//Prototipos
void agregarCliente(Lista&, const string&, float);
void mostrarClientesInicioFin(const Lista&);
void mostrarClientesFinInicio(const Lista&);
Cliente* encontrarCliente(const Lista&, const string&);
void actualizarCliente(Lista&, const string&, float);
void eliminarCliente(Lista&, const string&);
void vaciarLista(Lista&);
bool verificarLista(const Lista&);

//Main
int main() {
    Lista lista;
    int opcion = 0;
    float saldo = 0.0f;
    string nombre;
    do {
        cout << "\t---MENU---\n"
            << "1.- Agregar un cliente\n"
            << "2.- Mostrar lista de clientes (Inicio a fin)\n"
            << "3.- Mostrar lista de clientes (Fin a inicio)\n"
            << "4.- Actualizar cliente\n"
            << "5.- Eliminar cliente por nombre\n"
            << "6.- Vaciar lista\n"
            << "7.- Salir del programa\n> ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                cout << "Digite el nombre: "; cin >> nombre;
                cout << "Digite el saldo: "; cin >> saldo;
                agregarCliente(lista,nombre,saldo);
                break;
            case 2:
                if(verificarLista(lista)) {
                    cout << "Lista de clientes (Inicio a fin):\n";
                    mostrarClientesInicioFin(lista);
                } else {
                    cout << "Ingrese algun cliente primero.\n";
                }
                break;
            case 3:
                if(verificarLista(lista)) {
                    cout << "Lista de clientes (Fin a inicio):\n";
                    mostrarClientesFinInicio(lista);
                } else {
                    cout << "Ingrese algun cliente primero.\n";
                }
                break;
            case 4:
                if(verificarLista(lista)) {
                    cout << "Digite el nombre: "; cin >> nombre;
                    cout << "Digite el saldo actualizado: "; cin >> saldo;
                    actualizarCliente(lista, nombre, saldo);
                } else {
                    cout << "Ingrese algun cliente primero.\n";
                }
                break;
            case 5:
                if(verificarLista(lista)) {
                    cout << "Digite el nombre: "; cin >> nombre;
                    eliminarCliente(lista,nombre);
                } else {
                    cout << "Ingrese algun cliente primero.\n";
                }
                break;
            case 6:
                cout << "Vaciando lista.\n";
                if (verificarLista(lista)) { vaciarLista(lista); }
                else { cout << "Lista vacia.\n"; }
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
void agregarCliente(Lista& lista, const string& nombre, float saldo) {
    Cliente* nuevo = new Cliente{nombre,saldo,nullptr,nullptr};
    if(!lista.frente) {
        lista.frente = lista.final = nuevo;
    } else {
        lista.final->siguiente = nuevo;
        nuevo->anterior = lista.final;
        lista.final = nuevo;
    }
    lista.cantidad++;
    cout << nombre << " [S/. " << saldo << "] agregado con exito a la lista.\n";
}

void mostrarClientesInicioFin(const Lista& lista) {
    const Cliente* aux = lista.frente;
    while(aux) {
        cout << aux->nombre << " [S/. " << aux->saldo << "]";
        (aux->siguiente) ? cout << ",\n" : cout << ".\n";
        aux = aux->siguiente;
    }
}

void mostrarClientesFinInicio(const Lista& lista) {
    const Cliente* aux = lista.final;
    while(aux) {
        cout << aux->nombre << " [S/. " << aux->saldo << "]";
        (aux->anterior) ? cout << ",\n" : cout << ".\n";
        aux = aux->anterior;
    }
}

Cliente* encontrarCliente(const Lista& lista, const string& nombre) {
    Cliente* auxFrente = lista.frente;
    Cliente* auxFinal = lista.final;
    while(auxFrente != auxFinal) {
        if(auxFrente->nombre == nombre) {
            return auxFrente;
        }
        if(auxFinal->nombre == nombre) {
            return auxFinal;
        }
        auxFrente = auxFrente->siguiente;
        auxFinal = auxFinal->anterior;
    }
    if(auxFrente->nombre == nombre) return auxFrente;
    return nullptr;
}

void actualizarCliente(Lista& lista, const string& nombre, float saldo) {
    Cliente* cli = encontrarCliente(lista,nombre);
    if(!cli) {
        cout << "Cliente no encontrado.\n";
        return;
    } else {
        cout << "Saldo anterior: ";
        cout << cli->nombre << "[S/. " << cli->saldo << "]\n";
        cli->saldo = saldo;
        cout << "Saldo actualizado: ";
        cout << cli->nombre << "[S/. " << cli->saldo << "]\n";
    }
}

void eliminarCliente(Lista& lista, const string& nombre) {
    Cliente* temp = encontrarCliente(lista, nombre);
    if (!temp) { cout << "Cliente no encontrado.\n"; return; }

    Cliente* pre = temp->anterior;
    Cliente* sig = temp->siguiente;

    if (!pre && !sig) {
        lista.frente = lista.final = nullptr;
    } else if (!pre) {
        lista.frente = sig;
        sig->anterior = nullptr;
    } else if (!sig) {
        lista.final = pre;
        pre->siguiente = nullptr;
    } else {
        pre->siguiente = sig;
        sig->anterior  = pre;
    }

    delete temp;
    lista.cantidad--;
    cout << nombre << " eliminado de lista.\n";
}


void vaciarLista(Lista& lista) {
    while(lista.frente) {
        Cliente* temp = lista.frente;
        lista.frente = lista.frente->siguiente;
        delete temp;
    }
    lista.frente = lista.final = nullptr;
    lista.cantidad = 0;
    cout << "Lista vaciada con exito.\n";
}

bool verificarLista(const Lista& lista) {
    return lista.frente != nullptr;
}
