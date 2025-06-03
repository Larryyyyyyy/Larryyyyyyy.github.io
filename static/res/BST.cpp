#include "header.h"
using namespace std;
template<typename T=int>
class BST{
private:
    struct Node{
        T data;
        Node* lchild,* rchild;
        Node():data(0),lchild(nullptr),rchild(nullptr){}
        Node(T data):data(data),lchild(nullptr),rchild(nullptr){}
    };
public:
    Node* root;
    BST(){
        root=nullptr;
    }
    void show(const Node* now){
        cout<<now->data<<" ";
        if(now->lchild!=nullptr){
            show(now->lchild);
        }
        if(now->rchild!=nullptr){
            show(now->rchild);
        }
    }
    void insert(T data){
        if(!root){//未定义
            root=new Node(data);
            return;
        }
        Node* now=root;
        while(1){
            if(data<now->data){
                if(now->lchild)now=now->lchild;
                else{
                    now->lchild=new Node(data);
                    return;
                }
            }
            if(data>now->data){
                if(now->rchild)now=now->rchild;
                else{
                    now->rchild=new Node(data);
                    return;
                }
            }
        }
    }
    void del(T data){
        Node* now=root,* last=nullptr;
        while(1){
            if(data<now->data){
                last=now;
                now=now->lchild;
                continue;
            }
            if(data>now->data){
                last=now;
                now=now->rchild;
                continue;
            }
            if(!now->lchild&&!now->rchild){
                if(last->lchild==now){
                    last->lchild=nullptr;
                }
                if(last->rchild==now){
                    last->rchild=nullptr;
                }
                delete now;
                now=nullptr;
                break;
            }
            if(now->lchild&&!now->rchild){
                if(last->lchild==now){
                    last->lchild=now->lchild;
                }
                if(last->rchild==now){
                    last->rchild=now->lchild;
                }
                delete now;
                now=nullptr;
                break;
            }
            if(!now->lchild&&now->rchild){
                if(last->lchild==now){
                    last->lchild=now->rchild;
                }
                if(last->rchild==now){
                    last->rchild=now->rchild;
                }
                delete now;
                now=nullptr;
                break;
            }
            if(now->lchild&&now->rchild){
                Node* p=now->lchild;
                last=now;
                while(p->rchild){
                    last=p;
                    p=p->rchild;
                }
                now->data=p->data;
                if(p->lchild){
                    last->rchild=p->lchild;
                }
                else{
                    last->rchild=nullptr;
                }
                delete p;
                p=nullptr;
                break;
            }
        }
    }
};
int x;
int main(){
    BST<int> tree;
    while(cin>>x){
        if(x==-1)break;
        tree.insert(x);
        tree.show(tree.root);
        puts("");
    }
    cin>>x;
    tree.del(x);
    tree.show(tree.root);
    return 0;
}
/*
34 78 12 28 96 -1
34
*/