//
//  tabla_hash.h
//  Act 5.1 - Implementación individual de operaciones sobre conjuntos
//
//  Created by Lydia Delgado uriarte on 22/11/21.
//

#ifndef tabla_hash_h
#define tabla_hash_h

#include <iostream>
#include <list>
#include <utility>
#include <vector>
using namespace std;


class HashTable{
    int sizeTable;
    list<pair<int,int>> *table;
    vector<pair<int,int>> quadraticTable;
    
    public:
        HashTable(int size);
        // Esta funcion hace el calculo del modulo de la llave respecto al tamaño
        // Complejidad O(1)
        // @param int key es la llave que mandamos para calcular el indice
        // @param return devuelve el indice donde se pondrá la llave con sus datos
        int hashFunction(int key){
            return (key % sizeTable);
        }
    
        void quadratic (int key, int data);
    
        void chain(int key, int data);
        
        void imprimirHashTableQuadratic();
    
        void imprimirHashTableChain();
};

HashTable::HashTable(int size){
    this ->sizeTable = size;
    table = new list<pair<int,int>>[sizeTable];
    // Complejidad O(n)
    // Se llenan los valores de la tabla con keys de valor -1
    // Esto para poder usar la funcion cuadratica y detectar
    // Los espacios de la tabla que estan disponibles
    for (int i = 0; i < sizeTable ; i++){
        quadraticTable.push_back(make_pair(-1,NULL));
    }
}

// Esta funcion inserta los elementos de manera cuadratica
// @param int key es la llave que mandamos
// @param int data los datos que contiene la llave
void HashTable::quadratic(int key, int data){
    int index = hashFunction(key);
    for (int j = 0; j < sizeTable; j++){
        // Complejiidad O(1) si no hay colision
        // Complejidad O(log n) si se presenta una colision, n es el tamaño de la tabla
        // Complejidad O(n) si no se es posible insertar el elemento en la tabla o este
        // llegue a la ultima iteracion
        int ind = (index + (j*j)) % sizeTable;
        if (quadraticTable[ind].first == -1 || quadraticTable[index].first == key){
            quadraticTable[ind].first = key;
            quadraticTable[ind].second = data;
            break;
        }
    }
}


// Esta funcion inserta los elementos usando el metodo
// cadena que hace uso de listas ligadas
// Complejidad O(1) en el mejor de los casos
// Complejidad O(n) en el peor de los casos
// @param int key es la llave que mandamos
// @param int data los datos que contiene la llave
void HashTable::chain(int key, int data){
    int i = hashFunction(key);
    auto &list = table[i];
    for (auto &itr : list){
        if (itr.first == key){
            itr.second = data;
            return;
        }
    }
    // Complejidad O(1)
    table[i].push_back(make_pair(key,data));
}

// Funcion que imprime la tabla cuadratica
// Complejidad O(n) donde n es el tamaño de la tabla
void HashTable::imprimirHashTableQuadratic(){
    int i = 0;
    for (auto pair: quadraticTable){
        cout << i ;
        cout << "--> [" << pair.first << "," << pair.second << "] "  ;
        cout << endl;
        i++;
    }
}


// Funcion que imprime la tabla cuadratica
// Complejidad O(n^2) ya que hacemos usos de dos for
// Un for indica los indices de la tabla y el otro las llaves con los datos
void HashTable::imprimirHashTableChain(){
    for (int i = 0; i < sizeTable; i++){
        cout << i ;
        // Complejidad O(n) donde n es el tamaño de la tabla
        for (auto pair: table[i]){
            cout << "--> [" << pair.first << "," << pair.second << "] "  ;
        }
        cout << endl;
    }
}
#endif /* tabla_hash_h */
