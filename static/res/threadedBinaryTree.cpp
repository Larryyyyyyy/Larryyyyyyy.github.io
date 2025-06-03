#include "header.h"
using namespace std;
enum PointerTag{Link,Thread};
template<typename T>
class threadedBinaryTree{
public:
    struct Node{
        T data;
        Node *left,*right;
        PointerTag leftTag,rightTag;
        Node(T value):data(value),left(nullptr),right(nullptr),leftTag(Link),rightTag(Link){}
    };
    threadedBinaryTree():root(nullptr),pre(nullptr){}
    void insert(T value){
        root=insertRec(root,value);
    }
    void inorder(){
        inorderThreaded(root);
    }
    void createthreadedBinaryTree(){
        pre=nullptr;
        createthreadedBinaryTreeRec_In(root);
    }
private:
    Node* root;
    Node* pre;
    Node* insertRec(Node* node,T value){
        if(!node){
            return new Node(value);
        }
        if(value<node->data){
            node->left=insertRec(node->left,value);
        }else{
            node->right=insertRec(node->right,value);
        }
        return node;
    }
    void inorderThreaded(Node* node){
        Node* current=node;
        while(current){
            while(current->leftTag==Link&&current->left){
                current=current->left;
            }
            cout<<current->data<<" ";
            while(current->rightTag==Thread&&current->right){
                current=current->right;
                cout<<current->data<<" ";
            }
            current=current->right;
        }
    }
    void preorderThreaded(Node* node){
        Node* current=node;
        while(current){
            while(current->leftTag==Link&&current->left){
                cout<<current->data<<" ";
                current=current->left;
            }
            cout<<current->data<<" ";
            while(current->rightTag==Thread&&current->right){
                current=current->right;
                cout<<current->data<<" ";
            }
            current=current->right;
        }
    }
    void postorderThreaded(Node* node){
        //略
    }
    void createthreadedBinaryTreeRec_In(Node* node){
        if(!node)return;
        createthreadedBinaryTreeRec_In(node->left);
        if(!node->left){
            node->leftTag=Thread;
            node->left=pre;
        }
        if(pre){
            pre->rightTag=Thread;
            pre->right=node;
        }
        pre=node;
        createthreadedBinaryTreeRec_In(node->right);
    }
    void createthreadedBinaryTreeRec_Pre(Node* node){
        if(!node)return;
        if(!node->left){
            node->leftTag=Thread;
            node->left=pre;
        }
        if(pre){
            pre->rightTag=Thread;
            pre->right=node;
        }
        pre=node;
        createthreadedBinaryTreeRec_Pre(node->left);
        createthreadedBinaryTreeRec_Pre(node->right);
    }
    void createthreadedBinaryTreeRec_Post(Node* node){
        if(!node)return;
        createthreadedBinaryTreeRec_Post(node->left);
        createthreadedBinaryTreeRec_Post(node->right);
        if(!node->left){
            node->leftTag=Thread;
            node->left=pre;
        }
        if(pre){
            pre->rightTag=Thread;
            pre->right=node;
        }
        pre=node;
    }
};
int main() {
    threadedBinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);
    tree.createthreadedBinaryTree();
    tree.inorder();
    return 0;
}
