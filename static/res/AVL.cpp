#include "header.h"
using namespace std;
template<typename T=int>
class AVLTree{
private:
    struct Node{
        T data;
        Node *lchild,*rchild;
        int height;
        Node():data(0),lchild(nullptr),rchild(nullptr),height(1){}
        Node(T data):data(data),lchild(nullptr),rchild(nullptr),height(1){}
    };
public:
    Node *root;
    AVLTree():root(nullptr){}
    int height(Node *node){
        return node?node->height:0;
    }
    void updateHeight(Node *node){
        if(node)
            node->height=max(height(node->lchild),height(node->rchild))+1;
    }
    int balanceFactor(Node *node){
        return height(node->lchild)-height(node->rchild);
    }
    //LL
    Node* rightRotate(Node *y){
        Node *x=y->lchild;
        Node *T2=x->rchild;
        x->rchild=y;
        y->lchild=T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }
    //RR
    Node* leftRotate(Node *x){
        Node *y=x->rchild;
        Node *T2=y->lchild;
        y->lchild=x;
        x->rchild=T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }
    //LR
    Node* leftRightRotate(Node *node){
        node->lchild=leftRotate(node->lchild);
        return rightRotate(node);
    }
    //RL
    Node* rightLeftRotate(Node *node){
        node->rchild=rightRotate(node->rchild);
        return leftRotate(node);
    }
    Node* insert(Node *node,T data){
        if(!node)return new Node(data);
        if(data<node->data)node->lchild=insert(node->lchild,data);
        else if(data>node->data)node->rchild=insert(node->rchild,data);
        else return node;
        updateHeight(node);
        int balance=balanceFactor(node);
        if(balance>1){
            if(data<node->lchild->data){
                return rightRotate(node);//LL
            }else{
                return leftRightRotate(node);//LR
            }
        }
        if(balance<-1){
            if(data>node->rchild->data){
                return leftRotate(node);//RR
            }else{
                return rightLeftRotate(node);//RL
            }
        }
        return node;
    }
    Node* deleteNode(Node *node,T data){
        if(!node)return node;
        if(data<node->data)node->lchild=deleteNode(node->lchild,data);
        else if(data>node->data)node->rchild=deleteNode(node->rchild,data);
        else{
            if(!node->lchild||!node->rchild){
                Node *temp=node->lchild?node->lchild:node->rchild;
                if(!temp){
                    temp=node;
                    node=nullptr;
                }else{
                    *node=*temp;
                }
                delete temp;
            }else{
                Node *temp=minValueNode(node->rchild);
                node->data=temp->data;
                node->rchild=deleteNode(node->rchild,temp->data);
            }
        }
        if(!node)return node;
        updateHeight(node);
        int balance=balanceFactor(node);
        if(balance>1){
            if(balanceFactor(node->lchild)>=0){
                return rightRotate(node);//LL
            }else{
                return leftRightRotate(node);//LR
            }
        }
        if(balance<-1){
            if(balanceFactor(node->rchild)<=0){
                return leftRotate(node);//rr
            }else{
                return rightLeftRotate(node);//RL
            }
        }
        return node;
    }
    Node* minValueNode(Node *node){
        Node *current=node;
        while(current&&current->lchild){
            current=current->lchild;
        }
        return current;
    }
    void insert(T data){
        root=insert(root,data);
    }
    void del(T data){
        root=deleteNode(root,data);
    }
    //中序遍历
    void show(Node *node){
        if(node){
            show(node->lchild);
            cout<<node->data<<" ";
            show(node->rchild);
        }
    }
    //显示树
    void show(){
        show(root);
    }
};
int main(){
    AVLTree<int> tree;
    int x;
    while(cin>>x){
        if(x==-1)break;
        tree.insert(x);
        tree.show();
        puts("");
    }
    cin>>x;
    tree.del(x);
    tree.show();
    return 0;
}