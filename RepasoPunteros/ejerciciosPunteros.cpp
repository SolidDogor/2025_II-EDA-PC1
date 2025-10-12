/*
    Punteros - Declaración de punteros
    
    &n = La dirección de n
    *n = La variable cuya dirección está almacenada en n
*/


#include <iostream>
using namespace std;

// Reto 1: direccion y dereference
void reto1() {
    int x = 10;
    int* p = &x;
    cout << "[R1] x=" << x << " &x=" << &x << "\n";
    cout << "[R1] p=" << p << " *p=" << *p << "\n";
    *p = 42; // modifica x a través de p
    cout << "[R1] x ahora=" << x << "\n";
}

// Reto 2: new/delete
void reto2() {
    int x = 7;
    int* q = &x /* TODO: reserva un int con valor 7 en heap */;
    cout << "[R2] *q=" << *q << " (direccion " << q << ")\n";
    // TODO: libera memoria de q y ponlo en nullptr
    delete[] q;
    q = nullptr;
    cout << "[R2] q=" << q << " (debe ser nullptr)\n";
}

// Reto 3: puntero a puntero
void reto3() {
    int v = 5;
    int* a = &v;
    int** b = &a/* TODO: haz que b apunte a a */;
    **b = 99; // cambia v a 99
    cout << "[R3] v=" << v << " *a=" << *a << " **b=" << **b << "\n";
}

// Reto 4: pasar por puntero vs referencia
void inc_ptr(int* p) { /* TODO: incrementa el entero apuntado por p */ 
    *p += 1;
}
void inc_ref(int& r) { /* TODO: incrementa r */ 
    int* p = &r;
    *p += 1;

}

void reto4() {
    int n1 = 1, n2 = 1;
    inc_ptr(&n1);
    inc_ref(n2);
    cout << "[R4] n1=" << n1 << " n2=" << n2 << "\n"; // ambos deben ser 2
}

// Reto 5: null-safety
int safe_deref(int* p) {
    // Si p es nullptr, retorna -1; si no, retorna *p
    /* TODO */
    if (p == nullptr) return -1;
    else return *p;
}

void reto5() {
    int z = 123;
    int* good = &z;
    int* bad  = nullptr;
    cout << "[R5] good=" << safe_deref(good) << " bad=" << safe_deref(bad) << "\n";
}

int main() {
    reto1();
    reto2();
    reto3();
    reto4();
    reto5();
}
