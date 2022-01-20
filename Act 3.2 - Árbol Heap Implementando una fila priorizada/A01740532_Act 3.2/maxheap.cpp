//  Act 3.2 Arbol Heap: Implementando una fila priorizada
//  Programación de estructuras de datos y algoritmos fundamentales (Gpo 13)
//  Created by Lydia Delgado Uriarte on 19/10/21.
//  Profesor: Luis Ricardo Peña Llamas

#include <iostream>
#include "priority_queue.h"

using namespace std;
// 1. Create a new node at the end of heap
// 2. Assign new value to the node.
// 3. Compare the value of this child node with its parent.
// 4. If value of parent is less than child, then swap them.
// 5. Repeat step 3 & 4 until heap property holds

int main() {
    PriorityQueue tree;
    // 1er caso prueba
    cout << "--------------------------" << endl;
    cout << "      1ER CASO PRUEBA: " << endl;
    cout << "--------------------------" << endl;
    cout << "Cantidad de datos: " << tree.sizeT() << endl;
    tree.empty();
    cout << "Insertamos 2, 6, 1" << endl;
    tree.push(2);
    tree.push(6);
    tree.push (1);
    cout << "Dato con mayor prioridad: " << tree.top() << endl;
    tree.printTree();
    cout << "Eliminar dato con mayor prioridad" << endl;
    tree.pop();
    tree.printTree();
    
    // 2do caso prueba
    cout << "--------------------------" << endl;
    cout << "      2DO CASO PRUEBA: " << endl;
    cout << "--------------------------" << endl;
    cout << "Insertamos 20, 40, 90, 80" << endl;
    tree.push(20);
    tree.push(40);
    tree.push(90);
    tree.push(80);
    cout << "Cantidad de datos: " << tree.sizeT() << endl;
    cout << "Dato con mayor prioridad: " << tree.top() << endl;
    tree.empty();
    tree.printTree();
    cout << "Elimina dato con mayor prioridad"<< endl;
    tree.pop();
    tree.printTree();
    
    // 3er caso prueba
    cout << "--------------------------" << endl;
    cout << "      3ER CASO PRUEBA: " << endl;
    cout << "--------------------------" << endl;
    cout << "Agregamos 70, 60, 3, 0"<< endl;
    tree.push(70);
    tree.push(60);
    tree.push(3);
    tree.push(0);
    cout << "Cantidad de datos: " << tree.sizeT() << endl;
    cout << "Dato con mayor prioridad: " << tree.top() << endl;
    tree.empty();
    tree.printTree();
    cout << "Elimina 2 datos con mayor prioridad" << endl;
    tree.pop();
    tree.pop();
    tree.printTree();
    cout << "Cantidad de datos: " << tree.sizeT() <<"\n"<< endl;
    
    //4to CASO PRUEBA
    cout << "--------------------------" << endl;
    cout << "      4TO CASO PRUEBA: " << endl;
    cout << "--------------------------" << endl;
    cout << "Agregamos 9" << endl;
    tree.push(9);
    tree.printTree();
    cout << "Deja el elemento con menos prioridad" << endl;
    tree.pop();
    tree.pop();
    tree.pop();
    tree.pop();
    tree.pop();
    tree.pop();
    tree.pop();
    tree.printTree();
    cout << "Dato con mayor prioridad: " << tree.top() << endl;
    cout << "Elimina dato con mayor prioridad" << endl;
    tree.pop();
    cout << "Cantidad de datos: " << tree.sizeT() << endl;
    cout << "Dato con mayor prioridad: " << tree.top() << endl;
    tree.empty();
}
