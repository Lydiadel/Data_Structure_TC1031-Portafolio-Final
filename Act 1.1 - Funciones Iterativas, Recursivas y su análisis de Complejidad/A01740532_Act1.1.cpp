// A01740532_Act1.1 Funciones iterativas, recursivas y su análisis de complejidad
// Aplicación en C++ en forma individual,  que calcule la sumatoria de 1 hasta n y llame a tres funciones.
// Autor: Lydia Delgado Uriarte A01740532 on 16/08/21.
// Fecha de creacion: 16/08/21.
// Fecha de modificacion: 18/08/21.
// Profesor: Luis Ricardo Peña Llamas.

#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

/* Metodo iterativo
 Esta funcion recibe un valor n y hace una suma desde 0 hasta el valor n que es el máximo.
 Es un contador que empieza de 0 hasta n y hace una suma de este contador en un for.
 Complejidad Computacional O(n) ya que se ejecuta n veces.
 Parametro n: es un numero entero que es el maximo que se calculara la suma.
 Return devuelve la suma hecha en el for de 0 hasta n.
 */
 int sumaIterativa(int n) {
    if (n == 1) {
        return 1;
    }
    int suma = 0;
    for (int i = 0; i <= n; i++) {
        suma += i;
    }
    return suma;
}

/* Metodo recursivo
 La funcion hace una suma del numero actual mas el numero menos 1 llamando esta funcion varias veces, de n hasta 0.
 Complejidad Computacional O(n) ya que se ejecuta un numero n de veces.
 Parametro n: es un numero entero que es el maximo que se calculara la suma.
 Return devuelve la suma de n hasta 0.
 */
int sumaRecursiva(int n) {
    if (n == 1) {
        return 1;
    }
    return n + sumaRecursiva(n - 1); // 2
}

/* Metodo directo
 La funcion hace una operacion que devuelve una suma de 0 hasta n usando la suma de Gauss.
 Complejidad Computacional O(1) ya que se ejecuta 1 vez.
 Parametro n: es un numero entero que es el maximo que se calculara la suma.
 Return devuelve la sumatoria desde 0 hasta n con el cálculo n + (n + 1 ) / 2.
 */
int sumaDirecta(int n) {
    if (n == 1) {
        return 1;
    }
    return n * (n + 1) / 2;
}

int main(){
    srand(time(NULL));
    for (int i = 1; i <= 4; i++) {
        int n = 1 + rand() % 101;
        cout << "Caso de prueba [" << i << "]: " << endl;
        cout << "La suma de 0 hasta " << n << " con suma iterativa es: " << sumaIterativa(n) << endl;
        cout << "La suma de 0 hasta " << n << " con suma recursiva es: " << sumaRecursiva(n) << endl;
        cout << "La suma de 0 hasta " << n << " con suma directa es: " << sumaDirecta(n) << endl << endl;
    }
    return 0;
};
