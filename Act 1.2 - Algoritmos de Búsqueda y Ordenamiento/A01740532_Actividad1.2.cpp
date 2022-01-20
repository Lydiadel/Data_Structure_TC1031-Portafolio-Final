// Actividad 1.2 Algoritmos de Búsqueda y Ordenamiento
// Created by Lydia Delgado uriarte on 02/09/21.
// Profesor: Luis Ricardo Peña Llamas

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

// Imprime la lista con un for que va por el tamaño del vector
void imprimeLista(vector<int> lista) {
    for (int i = 0; i < lista.size(); i++){
        cout << lista[i] << " ";
    }
}

// Forma iterativa
// Complejidad mejor de los casos O(n), peor de los casos O(n^2)
// Lo que hace es que va comparando si el valor del siguiente es mayor o menor y los intercambia.
vector <int> ordenaIntercambio(vector<int> lista) {
    cout << endl;
    for (int i = 0; i < lista.size(); i++) {
        for (int j = i; j < lista.size(); j++) {
            if (lista[i] > lista[j]) {
                int temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
    cout << "Ordena intercambio: " << endl;
    imprimeLista(lista);
    return lista;
}


// Forma iterativa.
// Complejidad o(n), peor de los casos o(n^2)
// Esta funciona en donde si el valor mayor esta al principio de la lista va a pasar intercambiando uno por uno de los siguientes hasta llegar al final.
// La variable temp se utiliza para guardar este valor de la lista ya que llega a desaparecer en la asignacion de una variable.
vector <int> ordenaBurbuja(vector <int> lista) {
    for (int i = 0; i < lista.size(); i++) {
        for (int j = 0; j < lista.size() - 1 ; j++){
            if (lista[j] > lista[j + 1]) {
                int temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
    cout <<"Bubble Sort: " << endl;
    imprimeLista(lista);
    return lista;
}

// Forma recursiva
// Complejidad O(nlog(n)), peor de los casos O(nlog(n))
// Ordena la parte izquierda y luego la parte derecha, después las mezcla y ordena
// Creamos dos vectores de cada division para compararlos y se van acomodando
vector<int> mezclar(vector<int> &lista, int inicio, int med, int fin){
    int n1 = med - inicio + 1;
    int n2 = fin - med;
    vector<int> izq(n1);
    vector<int> der(n2);
    
    for(int i = 0; i < n1; i++) {
        izq[i] = lista[inicio + i];
    }
    for(int i = 0; i < n2; i++) {
        der[i] = lista[med + 1 + i];
    }
    int i = 0, j = 0, k = inicio;
    while(i < n1 && j < n2) {
        if(izq[i] <= der[j]) {
            lista[k] = izq[i];
            i++;
        }
        else {
            lista[k] = der[j];
            j++;
        }
        k++;
    }
    while(i < n1) {
        lista[k] = izq[i];
        i++;
        k++;
    }
    while(i < n2){
        lista[k] = der[i];
        i += 1;
        k += 1;
    }
    return lista;
}

// Funcion principal, indica el inicio, medio y final de la lista como parametros el cual se va a dividir en dos partes
void ordenaMerge(vector<int> &lista, int inicio, int fin){
    if (inicio < fin){
        int med = (inicio + fin) / 2; // Calcular el medio con un floor que redondea hacia abajo
        ordenaMerge(lista, inicio, med);
        ordenaMerge(lista, med + 1, fin);
        //Mezclar
        mezclar(lista, inicio, med, fin);
    }
}

// Ambos casos de busquedas ordena la lista al principio de forma ascendente para poder trabajar con ella

// La complejidad es O(1) peor de los casos O(n)
// La funcion es una busqueda lineal, quiere decir que va de uno en uno de izquierda a derecha
// Los parametros es el valor y la lista a buscar, cree el vector posicion para guardar las pocisiones guardadas y las busquedas de misma fomra en caso de que se repitan.
void busqSecuencial(vector <int> lista, int valor){
    vector < int> posicion;
    vector <int> busqueda;
    cout << "Busqueda Secuencial: " << endl << "Lista: " ;
    imprimeLista(lista);
    vector <int> listaSort = ordenaIntercambio(lista);
    cout << endl << "Valor a encontrar: " << valor << endl;
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i] == valor){
            busqueda.push_back(lista[i]);
            posicion.push_back(i+1);
        }
    }
    if (busqueda.size() > 0){
        cout << "Los valores encontrados fueron: " << endl ;
        for (int i = 0; i < busqueda.size(); i++){
            cout << busqueda[i] << " en la posicion " << posicion[i] << endl;
        }
    }
    else {
        cout << "No se encontro ningun valor" << endl;
    }
}

// En el mejor de los casos la complejidad es O(1) y peor O(n/2)
// Se divide la lista otra vez donde se busca la posicion del valor hasta que se encuentre o no, en caso de que sea el peor caso es que se tenga quee dividir la lista hasta que un elemento de lista
void busqBinaria(vector<int> lista, int valor){
    cout << endl << "Busqueda Binaria con lista: " ;
    imprimeLista(lista);
    vector < int> posicion;
    vector <int> busqueda;
    cout << endl;
    vector<int> listaSort = ordenaBurbuja(lista);
    cout << endl << "Valor a encontrar: " << valor << endl;
    int inicio = 0;
    int fin = listaSort.size() - 1;
    while(inicio <= fin){
        int med = (inicio + (fin - 1) / 2);
        if (valor == listaSort[med]) {
            busqueda.push_back(listaSort[med]);
            posicion.push_back(med+1);
            if(listaSort[med] < valor) {
                inicio = med + 1;
            }
            else {
                fin = med - 1;
            }
        }
        else if(listaSort[med] < valor) {
            inicio = med + 1;
        }
        else {
            fin = med - 1;
        }
    }
    if (busqueda.size() > 0) {
        cout << "Los valores encontrados fueron: " << endl ;
        for (int i = 0; i < busqueda.size(); i++){
            cout << busqueda[i] << " en la posicion " << posicion[i] << endl;
        }
    }
    else {
        cout << "No se encontro ningun valor" << endl;
    }
}

vector <int> crearListaAleatoria(){
    vector <int> lista;
    int n= 4;
    // Hacemos vector aleatorio
    cout << "Lista:" << endl;
    for (int i = 0; i < n; i++) {
        int num = 1 + rand() % (101);
        lista.push_back(num);
        cout << lista[i] << " ";
    }
    return lista;
}
int main() {
    srand(time(NULL));
    // Caso 1,2,3 valores aleatorios
    for (int j= 1; j < 4; j++){
        int valor = 1 + rand() % (101);
        cout << "----------------------------------------" << endl;
        cout << "CASO " << j << endl;
        vector <int> lista = crearListaAleatoria();
        ordenaIntercambio(lista);
        cout << endl << endl;
        ordenaBurbuja(lista);
        cout << endl << endl;
        cout << "Merge sort: " << endl;
        ordenaMerge(lista, 0, lista.size()-1);
        imprimeLista(lista);
        cout << endl << endl;
        busqSecuencial(lista, valor);
        busqBinaria(lista, valor);
        cout << "----------------------------------------" << endl;
    }
    // Caso 4 con valores similares y valor de busqueda presente
    cout << "CASO 4" << endl << "Lista: " << endl;
    vector<int> lista = {60,20,30,40,30};
    imprimeLista(lista);
    ordenaIntercambio(lista);
    cout << endl << endl;
    ordenaBurbuja(lista);
    cout << endl << endl;
    cout << "Merge sort: " << endl;
    ordenaMerge(lista, 0, lista.size()-1);
    imprimeLista(lista);
    cout << endl << endl;
    busqSecuencial(lista, lista[3]);
    busqBinaria(lista, lista[0]);
    cout << "----------------------------------------" << endl;
    return 0;
}
