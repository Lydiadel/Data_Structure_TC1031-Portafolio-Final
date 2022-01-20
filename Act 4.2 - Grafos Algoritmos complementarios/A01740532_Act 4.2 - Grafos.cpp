//
//  main.cpp
//  Act 4.2 - Grafos
//  Lydia Delgado uriarte on 14/11/21.
//  Profesor: Luis Ricardo Peña Llamas

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

class Graph{
    public:
        // Hacemos uso de map con set, no usamos un vector ya que los vectores pueden tener valores
        // repetidos y lo que usamos es set
        map<string, set<string>> adj;
        int n; //vertice
        int m; // arco
    
        Graph(){
        }
        
        // loadGraph
        // Lo que hace esta funcion es guardar los nodos y arcos.
        // @param n es el numero de vertices o nodos
        // @param m es el numero de arcos
        void loadGraph(int n, int m){
            this->n = n;
            this -> m = m;
        }
        
        // Complejidad O(1)
        // Esta funcion agrega un nodo y su conexion a otro nodo
        void addEdge(string a, string b) {
            adj[a].insert(b);
        }
        
        // Complejidad O(n + m)
        // Esta funcion imprime la lista de adyacencia de los grafos
        void printAdjList() {
            for (auto const &x : adj) {
                cout << x.first << ':';
                for (auto f : x.second) {
                    cout << f << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        // Utilizando Depth First Search para ver si es un arbol.
        // Complejidad O(n)+O(a) donde n representa el numero de vertices/nodos y a son los arcos
        // Complejidad O(n+a)
        // La busqueda es con el primer vertice y vamos avanzando al llegar a los limites de cada nodo
        // devolviendonos a los ya visitados y asegurandonos que no se encuentre algun ciclo pues si hay uno
        // esto quiere decir que no es un arbol.
        // @param source es el nodo que estamos actualmente
        // @param visited son los nodos que ya fueron visitados
        // @param loopStack nodos que no se han visitado todavia
        // @param return bool true en caso de que sea arbol, false en caso de que no sea.
        bool depthFirst(string source, set<string> &visited, set<string> &loopStack){
            if (loopStack.find(source) != loopStack.end()){
                return false;
            }
            loopStack.insert(source);
            for (auto f : adj[source]){
                bool res = depthFirst(f, visited, loopStack);
                if (!res)
                    return false;
            }
            return true;
        }
        
        // Complejidad O(n(n+a))
        // Por cada nodo se recorre cada uno de los aristas que tiene este nodo y asi sucesivamente
        bool isTree(){
            set<string> visited;
            for (auto const &node: adj){
                set<string> loopStack;
                if (visited.find(node.first) == visited.end()){
                    bool res = depthFirst(node.first, visited, loopStack);
                    if (!res)
                        return false;
                }
            }
            return true;
        }
};


int main() {
    Graph grafo;
    Graph grafo2;
    Graph grafo3;
    Graph grafo4;

    cout << "Grafo 1: " << endl;
    grafo.addEdge("B", "E");
    grafo.addEdge("E", "A");
    grafo.addEdge("A", "F");
    grafo.addEdge("F", "B");
    grafo.loadGraph(4, 4);
    grafo.printAdjList();
    if (grafo.isTree()){
        cout << "Si es arbol!" << endl << "----------------------" << endl;;
    }
    else{
        cout << "NO es arbol" << endl << "----------------------" << endl;
    }
    
    // B-> H -> A -> D -> G -- No es un ciclo por lo cual es un arbol
    cout << "Grafo 2: " << endl;
    grafo2.addEdge("B", "H");
    grafo2.addEdge("H", "A");
    grafo2.addEdge("A", "D");
    grafo2.addEdge("D", "G");
    grafo2.loadGraph(4, 4);
    grafo2.printAdjList();
    if (grafo2.isTree()){
        cout << "Si es arbol!" << endl << "----------------------" << endl;;
    }
    else{
        cout << "NO es arbol" << "----------------------" << endl;
    }
    // A-> B -> C -> D ->? C -- Es un ciclo por lo cual es un arbol
    cout << "Grafo 3:" << endl;
    grafo3.addEdge("A", "B");
    grafo3.addEdge("B", "C");
    grafo3.addEdge("C", "D");
    grafo3.addEdge("D", "C");
    grafo3.loadGraph(4, 4);
    
    grafo3.printAdjList();
    if (grafo3.isTree()){
        cout << endl <<"Si es arbol!" << endl << "----------------------" << endl;;
    }
    else{
        cout << "NO es arbol" << endl << "----------------------" << endl;
    }

    // E-> F-> A -> C -> T -> S es un arbol ya que no hay ningun ciclo
    cout << "Grafo 4:" << endl;
    grafo4.addEdge("E", "F");
    grafo4.addEdge("F", "A");
    grafo4.addEdge("A", "C");
    grafo4.addEdge("C", "T");
    grafo4.addEdge("T", "S");
    grafo4.loadGraph(5, 5);

    grafo4.printAdjList();
    if (grafo4.isTree()){
        cout << "Si es arbol!" << endl << "----------------------" << endl;;
    }
    else{
        cout << "NO es arbol" << endl << "----------------------" << endl;
    }
    return 0;
    
}
