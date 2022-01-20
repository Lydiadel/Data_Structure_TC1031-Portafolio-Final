//  Act 3.2 Arbol Heap: Implementando una fila priorizada
//  Programación de estructuras de datos y algoritmos fundamentales (Gpo 13)
//  Created by Lydia Delgado Uriarte on 19/10/21.
//  Profesor: Luis Ricardo Peña Llamas

#include <vector>
#include <cmath>
using namespace std;
#include <iostream>

struct PriorityQueue{
    private:
    vector <int> tree;
    
    // Complejidad O(1)
    // @param i current index in the vector
    // @returns padre del index actual
    int parent(int index){
        return (index - 1) / 2;
    }
    
    // Complejidad O(1)
    // @param i current index in the vector
    // @return devuelve el hijo de la izquierda
    int leftCh(int index){
        return (2 * index + 2);
    }
    
    //  Complejidad O(1)
    // @param i current index in the vector
    // @return devuelve el hijo de la derecha
    int rightCh(int index){
        return(2 * index + 1);
    }
    
    // Esta funcion recorre el arbol hacia abajo
    void heapifyDown(int index){
        int left = leftCh(index);
        int right = rightCh(index);
        int largest = index;
        
        // Comparacion del index con los hijos para
        // encontrar el valor mayor
        if (left < tree.size() && tree[left] > tree[index]){
            largest = left;
        }
        if (right < tree.size() && tree[right] > tree[largest]) {
            largest = right;
        }
        if (largest != index) {
            swap(tree[index], tree[largest]);
            heapifyDown(largest);
        }
    }
    
    // Esta funcion recore el arbol hacia arriba
    void heapifyUp(int index){
        // Comprobamos que el index y el padre sea menor para
        // intercambiarlos
        if (index && tree[parent(index)] < tree[index]){
            // swap the two if heap property is violated
            swap(tree[index], tree[parent(index)]);
            // Vamos a los padres del index en caso de que existan
            // y si son menores se aplica lo mismo
            heapifyUp(parent(index));
        }
    }

    public:
        PriorityQueue(){
        }
    
        // Complejidad O(log(n))
        // Esta funcion se encarga de insertar valores a la lista
        // @param index es el ultimo valor de la lista para
        //        ordenar el arbol en caso de estar desordenado.
        void push(int key){
            tree.push_back(key);
            int index = tree.size()-1;
            heapifyUp(index);
        }
        
        // Complejidad O(log(n))
        // Esta funcion elimina el dato que tiene mayor prioridad y lo substituye
        // por el ultimo valor de la lista que es el de hasta abajo en el arbol.
        // Llama la funcion heapifyDown con el index 0
        void pop(){
            // Si el arbol no tiene elementos
            if (tree.size() == 0){
            }
            tree[0] = tree.back();
            tree.pop_back();
            heapifyDown(0);
        }
        
        // Complejidad O(1)
        // @return valor con mayor prioridad
        int top(){
            if (tree.size() == 0){
                cout <<"No hay dato \ncon mayor prioridad. ";
            }
            return tree[0];
        }
    
        // Complejidad O(1)
        // El vector ya tiene una función que devuelve la cantidad
        // de elementos que tiene, solo se aplica un if & else
        // @param tree El arbol que estamos evaluando
        // @return valor booleano si contiene algo es true
        //         si no es false
        bool empty(){
            if (tree.size() == 0){
                cout << "El arbol esta vacio\n" << endl;
                return false;
            }
            cout << "El arbol contiene elementos \n" ;
            return true;
        }
        
        // Complejidad O(1)
        // @return la cantidad de elementos
        int sizeT(){
            return tree.size();
        }
        
        //Complejidad O(n)
        // Recorre toda la lista por lo cual es recursivo
        // @param tree el vector que contiene los datos
        void printTree(){
          for(int i = 0; i < tree.size(); i++){
              cout << tree[i] <<" ";
          }
          cout<<"\n\n";
        }
};
