#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

struct comp {
    template <typename T>
    // Comparator function
    bool operator()(const T& l,
                    const T& r) const
    {
        if (l.second != r.second) {
            return l.second > r.second;
        }
        return l.first > r.first;
    }
};


void sort(map<string, int>& M)
{
    // Declare set of pairs and insert
    // pairs according to the comparator
    // function comp()
    set<pair<string, int>, comp> S(M.begin(),
                                   M.end());
  
    // Print the sorted value
    for (auto& it : S) {
        cout << it.first << ' '
             << it.second << endl;
    }
}

// 10/10/2021 <--> 11/10/2021 <--> 12/10/2021

// (10/10/2021)
/* {
   ip = 1.1.1.1 value = 1
   ip = 1.1.1.2 value = 3
   ip = 1.1.1.3 value = 1
   ip = 1.1.1.4 value = 4    
   } 

  {
   ip = 1.1.1.4 value = 4  
   1.1.1.4 se accedio 4 veces el dia 10/10/2021  
   ip = 1.1.1.2 value = 3
   1.1.1.2 se accedio 3 veces el dia 10/10/2021  
   ip = 1.1.1.1 value = 1
   1.1.1.1 se accedio 1 veces el dia 10/10/2021  
   ip = 1.1.1.1 value = 1
   1.1.1.1 se accedio 1 veces el dia 10/10/2021  
   } */

template <class T> class Node {
    private:
        T data; // The object information
  
        Node* prev;
        Node* next; // Pointer to the next node element

    public:
        map<string, int> ipsNRep; 
        
        Node(T new_data,Node* prev_node, Node* next_node){
            this->data = new_data;
            this->next = next_node;
            this->prev = prev_node;
        }

        Node(T new_data){
            this->data = new_data;
            this->next = NULL;
            this->prev = NULL;
        }

        void set_data(T new_data){
            this->data = new_data;
        }

        T get_data(){
            return this->data;
        }

        void set_next(Node *next_node){
            this->next = next_node;
        }

        Node* get_next(){
            return this->next;
        }

        void set_prev(Node *prev_node){
            this->prev = prev_node;
        }

        Node* get_prev(){
            return this->prev;
        }

        void show_map(){
          for ( auto it = ipsNRep.begin(); it != ipsNRep.end(); ++it  )
          {
            cout << it->first << '\t' << it->second << std::endl;
          } 
        }
};

template <class T> class CustomLinkedList{
    T date;

    public:
        Node<T> *head, *tail;
        CustomLinkedList(){
            head = NULL;
            tail = NULL;
        }

        ~CustomLinkedList(){

        }

        // Method adds data to the end of the list
        void add_end(T data){
            if(head == NULL){ //if our list is currently empty
                head = new Node<T>(data); //Create new node of type T
                tail = head;
            }
            else{ //if not empty add to the end and move the tail
                Node<T>* temp = new Node<T>(data);

                this->tail->set_next(temp);
                temp->set_prev(this->tail);

                this->tail = temp;
            }
        }

        // Method adds data to the begining of the list
        void add_begin(T data){
            Node<T>* temp = new Node<T>(data,NULL,head);
            head->set_prev(temp);
            this->head = temp;
        }

        // Method adds info to the begining of the list
        void add_after_node(T value_insert, T value_target){
            Node<T>* current_node = this->head;
            // Search for the node to delete
            while(current_node && current_node->get_data() != value_target){
                current_node = current_node->get_next();
            }

            // current node is empty the node wasn't found 
            if(!current_node){
                return;
            }
            Node<T>* next_node = current_node->get_next();

            Node<T>* temp = new Node<T>(value_insert,current_node,next_node);

            if(!next_node){
                this->tail = temp;
            }else{
                next_node->set_prev(temp);
            }
            
            current_node->set_next(temp);

            if(current_node == this->tail){
                this->tail = temp;
            }
        }


        void delete_node(T value){
            if(!this->head){
                // Empty linked list, no values to delete
                return;
            }
            
            // Check if the node to delete is the head
            if(this->head->get_data() == value){
                this->head = this->head->get_next();
                return;
            }

            Node<T>* current_node = this->head;
            // Search for the node to delete
            while ( current_node && current_node->get_next()->get_data() != value){
                current_node = current_node->get_next();
            }

            // check if node to delete is the tail
            if(current_node->get_next() == NULL){
                current_node->get_prev()->set_next(NULL);
                return;
            }

            // current node is empty the node wasn't found 
            if(!current_node){
                return;
            }

            Node<T>* node_to_delete = current_node->get_next(); 
            Node<T>* next_node = node_to_delete->get_next();

            next_node->set_prev(current_node);
            current_node->set_next(next_node);

            delete node_to_delete;
        }

        Node<T>* search_node(T value_target){
            Node<T>* current_node = this->head;
            // Search for the node to delete
            while ( current_node && current_node->get_data() == value_target){
                current_node = current_node->get_next();
            }
            return current_node;

            return NULL;
        }
        void print_list(){
            Node<T>* current_node = this->head;
            while (current_node != NULL){
              cout << endl << "Registers during: " <<current_node->get_data() << endl;
              sort(current_node->ipsNRep);
              //current_node->show_map();
              current_node = current_node->get_next();
            }
            cout << endl;
        }
};