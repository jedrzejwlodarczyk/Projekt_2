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
    BST bst;
    BSTNode* root = nullptr;

int main(int argc, char* argv[]) {

    if (string(argv[1]) != "--tree" || (string(argv[2]) != "AVL" && string(argv[2]) != "BST")){
        cout << "--tree [type of tree: BST/AVL]" << endl;
    }

    int nodes;
    cout << "nodes> ";
    cin >> nodes;
    int elements[nodes];
    cout << "insert> ";
    for (int i = 0; i < nodes; ++i) {
        cin >> elements[i];
    }
    

    //wywolanie bst
    if(string(argv[2])=="BST"){

    for (int i=0; i<nodes; ++i) {
        root = bst.Insert(root, elements[i]);
    }
    }


    int* sorted=sortarr(elements,nodes);
    //wywolanie AVL
    if(string(argv[2])=="AVL"){
        for(int i=0; i<nodes; i++){
            root=bst.createAVL(root,sorted,0,nodes-1);
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
        else if (action == "FindMinMax"){
            cout<<"minmalny węzeł: "<< bst.Searchmin(root)->Key<<endl;
            cout<<"maksymalny węzeł: "<< bst.Searchmax(root)->Key<<endl;
        }
        else{
            cout << "Wrong action! Type 'Help'" << endl;
        }
   }


//12345
}