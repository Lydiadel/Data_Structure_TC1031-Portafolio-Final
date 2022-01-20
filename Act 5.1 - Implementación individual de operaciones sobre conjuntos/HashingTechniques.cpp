//  Act 5.1 - Implementación individual de operaciones sobre conjuntos
//  Created by Lydia Delgado uriarte on 22/11/21.
//  Profesor: Luis Ricardo Peña Llamas


#include <iostream>
#include "tabla_hash.h"
#include <time.h>
#include <iostream>

using namespace std;
int main() {
    
    srand (time(NULL));
    int n = 12;
    
    cout <<"\n        Chain   \n " << endl;
    for (int c = 1; c <= 4 ; c++){
        HashTable tabla(n);
        cout << " -----------------------" << endl;
        cout <<"    Caso de prueba "<< c << endl;
        cout << "    Tamaño tabla: " << n << endl;
        cout << " -----------------------" << endl;
        for (int i = 0; i < n ; i++){
            tabla.chain((rand()%100)+1,(rand()%100)+1);
        }
        tabla.imprimirHashTableChain();
        cout << endl;
        n = (rand()%15)+1;
    }
    
    cout << "\n -----------------------" << endl;
    cout <<"       Quadratic      \n" << endl;
    for (int c = 1; c <= 4 ; c++){
        HashTable quadraticTable(n);
        cout <<"   Caso de prueba "<< c << endl;
        cout << "   Tamaño tabla: " << n << endl;
        cout << " -----------------------" << endl;
        for (int i = 0; i < n ; i++){
            quadraticTable.quadratic((rand()%100)+1,(rand()%100)+1);
        }
        quadraticTable.imprimirHashTableQuadratic();
        cout << endl;
        n = (rand()%15)+1;
    }
    
    return 0;
}
