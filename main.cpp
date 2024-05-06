#include <iostream>
#include <string>
#include <sstream>
#include "bst.h"
#include <unistd.h>
#include <fstream>
#include <chrono>


using namespace std;

BST bst;
BSTNode* root = nullptr;

void help(){
    cout << "Help           Show this message" << endl;
    cout << "Print          Print the tree usin In-order, Pre-order, Post-order" << endl;
    cout << "Delete         Delete elements of the tree" << endl;
    cout << "Delete_ALL     Delete all elements of the tree" << endl;
    cout << "Rebalance      Rebalance the tree" << endl;
    cout << "FindMinMax     Find the largest and smallest element" << endl;
    cout << "Exit           Exits the program" << endl;
}

void choice(string action){
    int nodestodelete;
    int *elementstodelete = nullptr;
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
        //przeniesienie tego na inne formy wpisywania danych
        else if (action == "Delete"){
            cout << "nodes> ";
            cin >> nodestodelete;
            elementstodelete = new int[nodestodelete];
            cout << "delete> ";
            for (int i = 0; i < nodestodelete; ++i) {
                cin >> elementstodelete[i];
                bst.Delete(root,elementstodelete[i]);
        }
        }
        else if (action == "Delete_ALL"){
            cout << "Deleting: ";
            bst.Deleteall(root);
            if(root==nullptr){
                cout<<endl<<"tree successfully removed"<<endl;
                exit(1);
            }
        }
        else if (action == "Print"){
            cout << "In-Order: ";
            bst.print_inorder(root);
            cout << endl;
            cout << "Post-Order: ";
            bst.print_postorder(root);
            cout << endl;
            cout << "Pre-Order: ";
            bst.print_preorder(root);
            cout << endl;
        }
        else if (action=="Rebalance"){
            root = bst.DSW(root);

        }
        else if (action == "Printforbenchmark"){
             bst.print_inorder(root);
        }
        /*
        else if (action == "Export"){
        ofstream tickzfile("./export/numbers.txt");
        if (!tickzfile.is_open()) {
        cout << "Error opening file: " << endl;
        return;}
        tickzfile<<bst.exportTree(root);
        tickzfile.close();
        }
        */
        else{
            cout << "Wrong action! Type 'Help'" << endl;
        }
}


    

int main(int argc, char* argv[]) {

    if (string(argv[1]) != "--tree" || (string(argv[2]) != "AVL" && string(argv[2]) != "BST")){
        cout << "--tree [type of tree: BST/AVL]" << endl;
    }

    bool is_redirected = !isatty(fileno(stdin));
    int nodes;
    int *elements = nullptr;

    



    if (is_redirected) {
        ostringstream oss;
        oss << cin.rdbuf(); // Odczytanie całego strumienia wejściowego

        string fileContents = oss.str(); // Pobranie zawartości do string

        istringstream iss(fileContents); // Tworzymy strumień do analizy tekstu
        string line;

        int counter = 0;
        while (getline(iss, line)) {
            if (counter == 0){
                nodes = stoi(line);
                elements = new int[nodes];
            }
            else if(counter == 1){
                istringstream lineStream(line);
                int element;
                int index = 0;
                while (lineStream >> element) {
                    elements[index++] = element;
                }
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
                
            }
            else{
                string action = line;
                choice(action);
            }
            counter++;
        } 
        
    }
    else{
        cout << "nodes> ";
        cin >> nodes;
        if(nodes<0){
            cout<<"ilosc wezlow musi byc dodatnia";
            exit(1);
        }
        elements = new int[nodes];
        cout << "insert> ";
        for (int i = 0; i < nodes; ++i) {
            cin >> elements[i];
        }
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
            if(root==nullptr){
            cout<<"Tree is empty"<<endl;
            exit(1);
            }
            string action = "";
            cout << "action> ";
            cin >> action;
            choice(action);
            if(root==nullptr){
                cout<<"Tree is empty"<<endl;
                exit(1);
            }
        }
    }

   
    delete[] elements;

  
}
