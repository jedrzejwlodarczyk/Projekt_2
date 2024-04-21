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
        if(node!=nullptr){
            if(node->Left!=nullptr){
                return Searchmin(node->Left);
                }
            return node;
        }
        else {return 0;}
        

    }

     BSTNode * Searchmax(BSTNode * node)
    {
        if(node!=nullptr){
            if(node->Right!=nullptr){
                return Searchmax(node->Right);
                }
            return node;
        
        }
        else {return 0;}

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


};