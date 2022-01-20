#include <iostream>

using namespace std;

template <class T> class Node {
    public:
        T data; // The object information
        int key; // key of the value
        Node<T>* left; // Pointer to the left node element
        Node<T>* right; // Pointer to the right node element
        
        Node(T new_data, int key, Node<T>* left, Node<T>* right){
            this->data = new_data;
            this->key = key;
            this->left = left;
            this->right = right;
        }

        Node(T new_data, int key){
            this->data = new_data;
            this->key = key;
            this->left = NULL;
            this->right = NULL;
        }

        void show(){
            cout << "IP: " << data << "\tTries: " << this->key << endl;
        }
};

template <class T> class BinarySearchTree{
    public:
        Node<T> *root;
        int size;
        BinarySearchTree(){
            this->root = NULL;
            size = 0;
        }

        ~BinarySearchTree(){

        }

        /*
        This function print the tree in the 
        sequence inorder
        Complexity O(N)
        */
        void inorder(Node<T>* current_node){
            if(current_node) {
                inorder(current_node->left);
                cout << current_node->key << " ";
                inorder(current_node->right);
            }

            if(this->root == current_node){
                cout << endl;
            }
        }

        /*
        This function inserts a custom node into the binary search tree
        Complexity of this function is O(H) where H is the height of the binary tree
        @param current_node the current node keep the recursion
        @param node_insert the node to insert
        */
        void insert(Node<T> * current_node, Node<T> *node_insert){
            // Go to the next node according to the rules;
            Node<T> * next_node = current_node->left;
            bool is_left = true;            
            if(node_insert->key > current_node->key){
                next_node = current_node->right;
                is_left = false;
            }

            if(next_node){
                // If exist the next node then, we go for the next
                this->insert(next_node, node_insert);
            }
            else if(is_left){
                // If the node doesn't exist and the node is in the left then we insert in the left side
                current_node->left = node_insert;
            }
            else{
                // If the node doesn't exist and the node is in the left then we insert in the left side
                current_node->right = node_insert;
            }
        }

        /*
        This function inserts a custom node into the binary search tree
        Complexity of this function is O(H) where H is the height of the binary tree
        @param data a template to store any kind of data
        @param key An integer that contains the key to insert 
        */
        void insert(T data, int key){
            Node<T> *node_insert = new Node<T>(data, key);
            size++;
            if (this->root){
                this->insert(this->root, node_insert);
            }
            else{
                // Insert the first node, if root is NULL.
                this->root = node_insert;
            }
        }

        /*
        Complexity of this function is O(Log n)
        This function inserts a pre-created node into the binary search tree
        @param data a template to store any kind of data
        @param key An integer that contains the key to insert 
        */
        void insert(Node<T>* node_insert){
            size++;
            if (this->root){
                this->insert(this->root, node_insert);
            }
            else{
                // Insert the first node, if root is NULL.
                this->root = node_insert;
            }
        }

        /*
        This function search a node with the
        specified key in the binary search tree.
        Complexity O(n)
        Best case O(log(n)) worst case O(H) where H is the height of the binary tree
        @param current_node is the current node
        in the three
        @param key_search the key that we are
        looking for
        @return the node with the key we were
        looking for, in case this key doesn't exist it returns NULL.
        */
        Node<T>* search(Node<T>* current_node, int key_searched){
            if(!current_node || key_searched == current_node->key){
                return current_node;
            }

            if(key_searched < current_node->key){
                return search(current_node->left, key_searched);
            }
            return search(current_node->right, key_searched);
        }

        Node<T>* search(int key_searched){
            return this->search(this->root, key_searched);
        }

        Node<T>* minimum_element(Node<T>* current_node){
            if(!current_node->left){
                return current_node;
            }
            return minimum_element(current_node->left);
        }

        /*
        This function deletes a node inside the binary search tree using recursion, since the binary search tree is not balanced it'll take O(H) where H is the height of the binary tree to execute, but most of the cases it'll take O(log n) time complexity 
        @param current_node a Node object to check
        @param key_delete the key searched to delete
        */
        Node<T>* delete_node(Node<T>* current_node, int key_delete){
            if(!current_node) return NULL;
            // First search for the element to delete
            else if(key_delete < current_node->key){
                current_node->left = this->delete_node(current_node->left, key_delete);
            }
            else if(key_delete > current_node->key){
                current_node->right = this->delete_node(current_node->right, key_delete);
            }
            else{
                if(!current_node->left && !current_node->right){
                    // If the node is a leaf we just delete it
                    delete current_node;
                    current_node = NULL;
                }
                else if(!current_node->left){
                    // If the node doesn't have left node, 
                    // then just replace the current node with the right root
                    Node<T> * right_node = current_node->right;
                    delete current_node;
                    current_node = right_node;
                }
                else if(!current_node->right){
                    // If the node doesn't have right node, 
                    // then just replace the current node with the left root
                    Node<T> * left_node = current_node->left;
                    delete current_node;
                    current_node = left_node;   
                }
                else{
                    // If the node to delete has both nodes
                    // We search the minimum element in the right side
                    Node<T>* successor  = this->minimum_element(current_node->right);
                    // Replace the data with the minimum element (also the key)
                    Node<T>* new_node_minimum = new Node<T>(
                        successor ->data, successor->key, 
                        current_node->left, current_node->right);

                    if(current_node == this->root){
                        this->root = new_node_minimum;
                    }

                    // Delete the current node
                    delete current_node;

                    // Now we recursively delete the minimum element in the right subtree
                    current_node = new_node_minimum;
                    current_node->right = this->delete_node(current_node->right, successor->key);
                }
            }
            return current_node;       
        }

        /*
        This function deletes a node 
        O(H) where H is the height of the binary tree because it calls delete_node function() wich takes that complexity, it'll take O(Log n) in the best case
        @param key_delete the integer containing the key to delete
        @returns a Node object
        */
        Node<T>* delete_node(int key_delete){
            return this->delete_node(this->root, key_delete);
        }

        /*
        Find the nth largest top n inside the binary tree
        O(H) where H is the height of the binary tree because searching for a key inside an unbalaced binary search tree takes in the worst case h calls, most of the cases it'll take O(Log n)
        @param current the first node to start the search, recommended root
        @param n the parameter that specifies which nth largest number search 
        @param c the value to keep comparing until it finds the nth number 
        */
        void nthLargest(Node<T> *current, int n, int &c)
        {
            /*Do not proceed if we reach null nodes or the amount
              of nodes finded exceeds the top n.*/
            if (current == NULL || c >= n){
                return;
            }
        
            //Go to the right node in order to increase the key.
            nthLargest(current->right, n, c);
        
            //Increment count of visited nodes
            c++;
        
            // If c becomes n now, then this is the nth largest
            if (c == n)
            {
                current->show();
                return;
            }
        
            // Recursive for left subtree, as in "inverted" inorder
            nthLargest(current->left, n, c);
        }
        
        /*
        Find the nth largest top n inside the binary tree
        O(H) where H is the height of the binary tree it calls nthLargest function() wich takes that complexity, it'll take O(Log n) in the best case
        @param current the first node to start the search, recommended root
        @param n the parameter that specifies which nth largest number search 
        */
        void nthLargest(Node<T> *current, int n)
        {
            //Amount of nodes visited:
            int c = 0;
            
            nthLargest(current, n, c);
        }

};