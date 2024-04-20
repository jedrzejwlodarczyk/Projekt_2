#include <iostream>
#include <string>
#include <sstream>
#include "bst.h"

using namespace std;

void help(){
    cout << "Help           Show this message" << endl;
    cout << "Print          Print the tree usin In-order, Pre-order, Post-order" << endl;
    cout << "Delete         Delete elements of the tree" << endl;
    cout << "Delete ALL     Delete all elements of the tree" << endl;
    cout << "Rebalance      Rebalance the tree" << endl;
    cout << "FindMinMax     Find the largest and smallest element" << endl;
    cout << "Exit           Exits the program" << endl;
}



int main(int argc, char* argv[]) {

    int nodes;
    int elements[nodes];



    if (string(argv[1]) != "--tree" || (string(argv[2]) != "AVL" && string(argv[2]) != "BST")){
        cout << "--tree [type of tree: BST/AVL]" << endl;
    }

    if (argc < 4){
        cout << "nodes> ";
        cin >> nodes;
        cout << "insert> ";
        for (int i = 0; i < nodes; ++i) {
            cin >> elements[i];
        }
    }

    //wywolanie bst
    if(string(argv[2])=="BST"){
    BST bst;
    BSTNode* root = nullptr;

    for (int i = 0; i < nodes; ++i) {
        root = bst.Insert(root, elements[i]);
    }
    }


   while(true){
        string action = "";
        cout << "action> ";
        cin >> action;

        if (action == "Help"){
            help();
        }
        else if (action == "Exit"){
            exit(1);
        }
        else{
            cout << "Wrong action! Type 'Help'" << endl;
        }
   }


//12345
}