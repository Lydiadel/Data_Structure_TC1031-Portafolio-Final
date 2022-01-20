//  Act 3.3 - Árbol Desplegado: Implementando un AVL Tree
//  A01740532 Lydia Delgado Uriarte 22/10/21.
//  Profesor: Luis Ricardo Peña Llamas

#include <iostream>

using namespace std;

template <class T>
class Node
{
public:
    T data;         // The object information
    int key;        // key of the value
    Node<T> *left;  // Pointer to the left node element
    Node<T> *right; // Pointer to the right node element

    Node(T new_data, int key)
    {
        this->data = new_data;
        this->key = key;
        this->left = NULL;
        this->right = NULL;
    }

    Node(T new_data, int key, Node<T> *left, Node<T> *right)
    {
        this->data = new_data;
        this->key = key;
        this->left = left;
        this->right = right;
    }
};

template <class T>
class BinarySearchTree
{
public:
    Node<T> *root;
    int size;

    BinarySearchTree()
    {
        this->root = NULL;
        this->size = 0;
    }

    ~BinarySearchTree()
    {
    }

    /*
     Inserta un nuevo nodo en el arbol y retorna a su padre
     Complejidad O(n)
     En el peor de los casos recorre una rama completa del arbol O(log(n)), pero las rotaciones
     tiene complejidad de O(n)
     @param currentNode es el nodo actual del arbol
     @nodeInsert el nodo que vamos insertar
     @return el nodo hijo
    */
    Node<T> *insert(Node<T> *currentNode, Node<T> *nodeInsert)
    {
        if (currentNode == NULL)
            return nodeInsert;

        if (nodeInsert->key < currentNode->key)
            currentNode->left = this->insert(currentNode->left, nodeInsert);
        else
            currentNode->right = this->insert(currentNode->right, nodeInsert);

        Node<T> *aux = applyRotations(currentNode);

        return (aux == NULL) ? currentNode : aux;
    }

    /*
     Aplica las rotaciones para balancear el arbol en el caso de insercion
     Complejidad O(n)
     La rotaciones tienen complejidad O(1), pero la funcion de balance en el peor de los casos
     recorre todo el arbol O(n)
     @param n1 el nodo que se aplica rotacion
     @return nuevo nodo raiz de rotacion
    */
    Node<T> *applyRotations(Node<T> *node)
    {
        int balance = this->balance(node);
        int balanceLeft = this->balance(node->left);
        int balanceRight = this->balance(node->right);

        if (balance == 2 && balanceLeft == 1)
            return this->leftLeft(node);

        if (balance == -2 && balanceRight == -1)
            return this->rightRight(node);

        if (balance == -2 && balanceRight == 1)
            return this->rightLeft(node);

        if (balance == 2 && balanceLeft == -1)
            return this->leftRight(node);

        return NULL;
    }

    /*
     Inserta un nuevo nodo en el arbol
     Complejidad O(n)
     @param data el valor a insertar
     @param key la key del nuevo nodo
    */
    void insert(T data, int key)
    {
        Node<T> *nodeInsert = new Node<T>(data, key);
        if (this->root)
            root = this->insert(this->root, nodeInsert);
        else
            this->root = nodeInsert;
        this->size++;
    }

    /*
     Busca y retorna un nodo de manera recursiva
     Complejidad O(log(n))
     En el peor de los casos recorre una rama completa del arbol
     @param current_node nodo actual del arbol
     @param key_searched nodo que buscamos
     @return nodo buscado o NULL si no existe
    */
    bool find(Node<T> *current_node, int key_searched)
    {
        if (current_node != NULL){
            if (current_node->key == key_searched){
                return true;
            }
            else if(current_node->key < key_searched){
                return find(current_node->right, key_searched);
            }
            else{
                return find(current_node->left, key_searched);
            }
        }
        return false;
    }

    /*
     Busca y retorna un nodo
     Complejidad O(log(n))
     @param key_searched  nodo que busca
     @return nodo encontrado o NULL si no existe
    */
    void find(int key_searched)
    {
        cout << this->find(this->root, key_searched) << endl;
    }

    /*
     Encuentra el nodo menor de un subarbol (el nodo de hasta la izquierda)
     Complejidad O(logn)
     @param currentNode nodo actual del arbol
     @return nodo menor
    */
    Node<T> *minimumElement(Node<T> *currentNode)
    {
        if (!currentNode->left)
            return currentNode;
        return minimumElement(currentNode->left);
    }

    /*
    Elimina un nodo del arbol de manera recursiva
    Complejidad O(n)
    esto debido a las rotaciones y a la funcion balance()
    @param currentNode nodo actual del arbol
    @param keyDelete llave que vamos eliminar
    @return el nodo del hijo eliminado
    */
    Node<T> *del(Node<T> *currentNode, int keyDelete)
    {
        if (!currentNode)
            return NULL;

        else if (keyDelete < currentNode->key)
            currentNode->left = this->del(currentNode->left, keyDelete);
        else if (keyDelete > currentNode->key)
            currentNode->right = this->del(currentNode->right, keyDelete);
        else
        {
            if (currentNode->left == NULL || currentNode->right == NULL)
            {
                Node<T> *aux = currentNode->left ? currentNode->left : currentNode->right;
                delete currentNode;
                if (aux == NULL)
                    currentNode = NULL;
                else
                    currentNode = aux;
            }
            else
            {
                Node<T> *successor = this->minimumElement(currentNode->right);
                Node<T> *new_node_minimum = new Node<T>(
                    successor->data, successor->key,
                    currentNode->left, currentNode->right);

                currentNode = new_node_minimum;
                currentNode->right = this->del(currentNode->right, successor->key);
            }
        }

        if (currentNode == NULL)
            return currentNode;

        Node<T> *aux = applyRotationsDelete(currentNode);
        return (aux == NULL) ? currentNode : aux;
    }

    /*
     Ejecuta las rotaciones con condiciones de eliminacion de un nodo
     Complejidad O(n)
     Las rotaciones tienen complejidad O(1), pero calcular el balance es O(n)
     @param node el nodo que se aplica rotacion
     @return nuevo nodo raiz de rotacion
    */
    Node<T> *applyRotationsDelete(Node<T> *node)
    {
        int balance = this->balance(node);
        int balanceLeft = this->balance(node->left);
        int balanceRight = this->balance(node->right);

        if (balance > 1 && balanceLeft >= 0)
            return this->leftLeft(node);

        if (balance < -1 && balanceRight <= 0)
            return this->rightRight(node);

        if (balance < -1 && balanceRight > 0)
            return this->rightLeft(node);

        if (balance > 1 && balanceLeft < 0)
            return this->leftRight(node);

        return NULL;
    }

    /*
    Elimina el nodo especificado del arbol
    Complejidad O(n)
    Parametros:
    @param key_delete key del nodo que se quiere eliminar
    */
    void del(int keyDel)
    {
        this->size--;
        this->root = this->del(this->root, keyDel);
    }

    /*
    Calcula el balance de un nodo especifico del arbol
    Complejidad O(n)
    @param current nodo que se calculara el balance
    @return balance del nodo
    */
    int balance(Node<T> *current)
    {
        if (current == NULL)
            return 0;
        return height(current->left, 0) - height(current->right, 0);
    }

    /*
     Calcula la altura de un nodo en el arbol de manera recursiva
     Complejidad O(n)
     @param nodo el nodo que se calcula altura
     @return altura de este nodo
    */
    int height(Node<T> *current, int h)
    {
        if (current == NULL)
            return h;
        return max(height(current->left, h + 1),
                   height(current->right, h + 1));
    }

    /*
     Hace una rotacion left left
     Complejidad O(1)
     @param n1 el nodo que se aplica rotacion
     @return nuevo nodo raiz de rotacion
    */
    Node<T> *leftLeft(Node<T> *node)
    {
        Node<T> *n2 = node->left;
        node->left = n2->right;
        n2->right = node;
        return n2;
    }

    /*
     Hace una rotacion right right
     Complejidad O(1)
     @param nodo el nodo que se aplica rotacion
     @return nuevo nodo raiz de rotacion
    */
    Node<T> *rightRight(Node<T> *node)
    {
        Node<T> *n2 = node->right;
        node->right = n2->left;
        n2->left = node;
        return n2;
    }

    /*
    Hace una rotacion right left
     Complejidad O(1)
     @param n1 el nodo que se aplica rotacion
     @return nuevo nodo raiz de rotacion
     */
    Node<T> *rightLeft(Node<T> *n1)
    {
        Node<T> *n2 = n1->right;
        Node<T> *n3 = n2->left;

        n2->left = n3->right;
        n3->right = n2;

        n1->right = n3->left;
        n3->left = n1;

        return n3;
    }

    /*
     Hace una rotacion left right
     Complejidad O(1)
     @param n1 el nodo que se aplica rotacion
     @return nuevo nodo raiz de rotacion
    */
    Node<T> *leftRight(Node<T> *n1)
    {
        Node<T> *n2 = n1->left;
        Node<T> *n3 = n2->right;

        n2->right = n3->left;
        n3->left = n2;

        n1->left = n3->right;
        n3->right = n1;

        return n3;
    }

    /*
     Retorna el tamaño del arbol
     Complejidad O(1)
     */
    int sizeT()
    {
        return this->size;
    }
    
    void inorder(Node<T> *current_node)
    {
        if (current_node)
        {
            inorder(current_node->left);
            cout << current_node->key << " ";
            inorder(current_node->right);
        }

        if (this->root == current_node)
        {
            cout << endl;
        }
    }

    void inorder()
    {
        inorder(root);
    }

    void print2DUtil(Node<T> *root, int space)
    {
        int COUNT = 2;
        // Base case
        if (root == NULL)
            return;

        // Increase distance between levels
        space += COUNT;

        // Process right child first
        print2DUtil(root->right, space);

        // Print current node after space
        // count
        cout << endl;
        for (int i = COUNT; i < space; i++)
            cout << " ";
        cout << root->key << "\n";

        // Process left child
        print2DUtil(root->left, space);
    }

    // Wrapper over print2DUtil()
    void print2D()
    {
        cout << "______________________________________" << endl;
        print2DUtil(root, 0);
        cout << "______________________________________" << endl;
    }
};

/*

La manera en la que se imprime el arbol con la orientacion es de izquierda a derecha en lugar de
arriba hacia abajo, ejemplo:
   16
  /  \
 11   21
    /
   12
Seria en este caso:

   21
     18
16
   11
*/
int main()
{
    BinarySearchTree<char> bst;
    int arrayNumbers[9] = {20, 30, 20, 40, 70, 55, 80, 90, 100};

    for (int i = 0; i < 9; i++)
    {
        cout << "Agregando el: " << arrayNumbers[i] << endl;
        bst.insert('a', arrayNumbers[i]);
        cout << "Size: " << bst.sizeT() << endl;
        cout << "Find: " ;
        bst.find(30);
        bst.print2D();
    }

    for (int i = 0; i < 9; i++)
    {
        cout << "Eliminando el: " << arrayNumbers[i] << endl;
        bst.del(arrayNumbers[i]);
        cout << "Size: " << bst.sizeT() << endl;
        cout << "Find: " ;
        bst.find(30) ;
        bst.print2D();
    }

    return 0;
}
