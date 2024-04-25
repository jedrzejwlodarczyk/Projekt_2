#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int* sortarr(int arr[], int size)
{
    int temp=0;
    for (int h=size/2; h>0; h/=2) {
        for (int i=0; i<size-h+1; i++) {
              int temp=arr[i],j=i;
              while(j>=h && arr[j-h]>temp){
                 arr[j]=arr[j-h];
                 j-=h;
             }
             arr[j]=temp;
         }
     }
    return arr;
}



class BSTNode
{
public:
    int Key;
    BSTNode * Left;
    BSTNode * Right;
    BSTNode * Parent;

};

class BST
{
public:
    BSTNode * Insert(BSTNode * node, int key)
     {
        if(node == nullptr)
        {
            node = new BSTNode;
            node->Key = key;
            node->Left = nullptr;
            node->Right = nullptr;
            node->Parent = nullptr;
        }
        else if(node->Key < key)
        {
            node->Right = Insert(node->Right, key);
            node->Right->Parent = node;
        }
        else
        {
            node->Left = Insert(node->Left, key);
            node->Left->Parent = node;
        }
        return node;
    }

    BSTNode * Searchmin(BSTNode * node)
    {
        if(node == nullptr){
            return nullptr;
        }
        else{
            if(node->Left!=nullptr){
                return Searchmin(node->Left);
                }
            return node;
        }
        

    }

    BSTNode * Searchmax(BSTNode * node)
    {
        if(node == nullptr){
            return nullptr;
        }
        else{
            if(node->Right!=nullptr){
                return Searchmax(node->Right);
                }
            return node;
        }

    }

    BSTNode * createAVL(BSTNode * node,int arr[], int start, int end) {
        if (start > end)
            return nullptr;

        int mid = (start + end)/2;
        BSTNode * avlnode = Insert(node,arr[mid]);

        avlnode->Left = createAVL(nullptr, arr, start, mid - 1);
        avlnode->Right = createAVL(nullptr, arr, mid + 1, end);

        return avlnode;
    }


    BSTNode * Delete(BSTNode*& node,int key)
        {
            if (node == nullptr) {
                return node;
            }

            if(key < node->Key){
                node->Left = Delete(node->Left,key);
            }
            else if (key > node->Key) {
                node->Right = Delete(node->Right, key);
            }

            else{
                if (node->Left == nullptr) {
                    BSTNode* temp = node->Right;
                    if (temp != nullptr) {
                        node->Key = temp->Key;
                        node->Right = Delete(node->Right, temp->Key);
                    } else {
                        delete node;
                        node = nullptr;
                    }
                }
                else if (node->Right == nullptr) {
                    BSTNode* temp = node->Left;
                    if (temp != nullptr) {
                        node->Key = temp->Key;
                        node->Left = Delete(node->Left, temp->Key);
                    } else {
                        delete node;
                        node = nullptr;
                    }
                }
                    else{
                        BSTNode* temp = Searchmin(node->Right);
                        if(temp != nullptr){
                            node->Key = temp->Key;
                            node->Right = Delete(node->Right, temp->Key);
                        }
                    }
            }
        return node;
        }
    
    
   void Deleteall(BSTNode *& node)
    {
        if(node == nullptr){
            return;
        }
        Deleteall(node->Left);
        Deleteall(node->Right);
        cout << node->Key << " ";
        node=Delete(node,node->Key);
    }



    void print_preorder(BSTNode* node){
        if(node == nullptr){
            return;
        }
        cout << node->Key << " ";
        print_preorder(node->Left);
        print_preorder(node->Right);
    }


    void print_inorder(BSTNode* node){
        if(node == nullptr){
            return;
        }
        print_inorder(node->Left);
        cout << node->Key << " ";
        print_inorder(node->Right); 
    }

    void print_postorder(BSTNode* node){
        if(node == nullptr){
            return;
        }
        print_postorder(node->Left);
        print_postorder(node->Right);
        cout << node->Key << " ";
    }
    
   /* 
    string exportTree(BSTNode* node) {
    if (!node->Left && !node->Right) {
        return "\\node {" + to_string(node->Key) + "}";
    }
    string l_str = node->Left ? "child {" + exportTree(node->Left) + "}" : "child[missing]";
    string r_str = node->Right ? "child {" + exportTree(node->Right) + "}" : "child[missing]";
    return "node {" + to_string(node->Key) + "} {" + l_str + "}} {" + r_str + "}";
    }
*/

};