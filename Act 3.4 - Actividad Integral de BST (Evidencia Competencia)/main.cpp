#include<iostream>
#include"BST.h"
#include<vector>
#include<fstream>

using namespace std;

void clear();
vector<string> readFile(string);
void loadNodes(vector<string>, BinarySearchTree<string>&);
Node<string>* line2node(string);



int main(){
    //clear();

    //CREATION OF A TREE
    BinarySearchTree<string> bst;
    cout << "Loading file into a binary search tree ..." << endl;

    /*-readFile() returns a vector of strings, which is take by loadNodes()
       followed by the BST that is going to receive all the information.
      -loadNodes() uses line2data() to convert each line from the string vector
       into a node with its key and data. Then it inserts each node into the bst.*/
    loadNodes(readFile("bitacora_sorted_condensed.txt"), bst);

    cout << "File loaded. Requests: " << bst.size << endl;

   

    cout << endl << endl;
    cout << "Top 5 IP's are:" << endl;
    for(int i = 1; i <= 5; i++){
        cout << "\t";
        bst.nthLargest(bst.root, i);
    }
    int c = 0;

    system("Pause");

    return 0;
}



/*Grabs a vector of lines. Each line is converted to a Node and inserted to the BST.
  The BST is pass by reference to avoid having more than one huge BST.
  O(N) complexity since it goes trough each of the lines in the text*/
void loadNodes(vector<string> linesVec, BinarySearchTree<string> &bstToSave){
    for(int i = 0; i < linesVec.size(); i++){
        bstToSave.insert(line2node(linesVec[i]));
    }
}

//Grabs a string and returns a Node
//O(N) complexity since it goes through each of the letters in the line
Node<string>* line2node(string line){
    string substr = "";
    string ip;
    int tries;

    //For each character
    for(int i = 0; i < line.length(); i++){        
        //If the character is a space then we already read the ip.
        
        if(line[i] == ' '){
            ip = substr;
            substr = "";
        }else{
            //As long as it is not a space, keep accumulating characters.
            substr += line[i];
        }
    }
    //The rest of characters belongs to the number of tries.
    tries = stoi(substr);

    //Create a node with the collected information
    Node<string>* newNode = new Node<string>(ip, tries); 
    return newNode;
}

//Converts a text file into a vector of strings.
//O(N) complexity since it goes trough each of the lines in the text file
vector<string> readFile(string path){
    vector<string> lines;
    string line;
    ifstream inFile(path);
    while(getline(inFile,line)){
        lines.push_back(line);
    }
    inFile.close();
    return lines;
}

void clear(){
    if (system("CLS")) system("clear");
}