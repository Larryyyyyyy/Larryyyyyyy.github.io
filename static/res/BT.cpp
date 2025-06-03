#include "header.h"
using namespace std;
template<class T=int>
class BTree{
private:
    struct BTreeNode{
        vector<T> keys;
        vector<BTreeNode*> children;
        bool isLeaf;
        BTreeNode(bool leaf):isLeaf(leaf){}
    };
    BTreeNode* root;
    int M;
    void traverse(BTreeNode* node){
        int i=0;
        while(i<node->keys.size()){
            if(!node->isLeaf){
                traverse(node->children[i]);
            }
            cout<<node->keys[i]<<" ";
            i++;
        }
        if(!node->isLeaf){
            traverse(node->children[i]);
        }
    }
    void insertNonFull(BTreeNode* node,T key){
        int i=node->keys.size()-1;
        if(node->isLeaf){
            while(i>=0&&key<node->keys[i]){
                i--;
            }
            node->keys.insert(node->keys.begin()+i+1,key);
        }else{
            while(i>=0&&key<node->keys[i]){
                i--;
            }
            i++;
            insertNonFull(node->children[i],key);
            if(node->children[i]->keys.size()==M){
                splitChild(node,i);
                if (key>node->keys[i]){
                    i++;
                }
            }
        }
    }
    void splitChild(BTreeNode* parent,int index){
        BTreeNode* fullChild=parent->children[index];
        BTreeNode* newChild=new BTreeNode(fullChild->isLeaf);
        int midKey=fullChild->keys[M/2];
        parent->keys.insert(parent->keys.begin()+index,midKey);
        parent->children.insert(parent->children.begin()+index+1,newChild);
        newChild->keys=vector<int>(fullChild->keys.begin()+M/2+1,fullChild->keys.end());
        if(!fullChild->isLeaf){
            newChild->children=vector<BTreeNode*>(fullChild->children.begin()+M/2+1,fullChild->children.end());
        }
        fullChild->keys.resize(M/2);
        fullChild->children.resize(M/2+1);
    }
    void del(BTreeNode* node,T key){
        int idx=findKey(node,key);
        if(idx<node->keys.size()&&node->keys[idx]==key){
            if(node->isLeaf){
                node->keys.erase(node->keys.begin()+idx);
            }else{
                if(node->children[idx]->keys.size()>=M/2){
                    int pred=getPred(node,idx);
                    node->keys[idx]=pred;
                    del(node->children[idx],pred);
                }else if(node->children[idx+1]->keys.size()>=M/2){
                    int succ=getSucc(node,idx);
                    node->keys[idx]=succ;
                    del(node->children[idx+1],succ);
                }else{
                    merge(node,idx);
                    del(node->children[idx],key);
                }
            }
        }else{
            if(node->isLeaf){
                return;
            }
            bool flag=((idx==node->keys.size())?true:false);
            if(node->children[idx]->keys.size()<M/2){
                fill(node,idx);
            }
            if(flag&&idx>node->keys.size()){
                del(node->children[idx-1],key);
            }else{
                del(node->children[idx],key);
            }
        }
    }
    void fill(BTreeNode* node,int idx){
        if(idx!=0&&node->children[idx-1]->keys.size()>=M/2){
            borrowFromPrev(node,idx);
        }else if(idx!=node->keys.size()&&node->children[idx+1]->keys.size()>=M/2){
            borrowFromNext(node,idx);
        }else{
            if(idx==node->keys.size()){
                merge(node,idx-1);
            }else{
                merge(node,idx);
            }
        }
    }
    void borrowFromPrev(BTreeNode* node,int idx){
        BTreeNode* child=node->children[idx];
        BTreeNode* sibling=node->children[idx-1];
        child->keys.insert(child->keys.begin(),node->keys[idx-1]);
        if(!child->isLeaf){
            child->children.insert(child->children.begin(), sibling->children.back());
            sibling->children.pop_back();
        }
        node->keys[idx-1]=sibling->keys.back();
        sibling->keys.pop_back();
    }
    void borrowFromNext(BTreeNode* node,int idx){
        BTreeNode* child=node->children[idx];
        BTreeNode* sibling=node->children[idx+1];
        child->keys.push_back(node->keys[idx]);
        if(!child->isLeaf){
            child->children.push_back(sibling->children.front());
            sibling->children.erase(sibling->children.begin());
        }
        node->keys[idx]=sibling->keys.front();
        sibling->keys.erase(sibling->keys.begin());
    }
    void merge(BTreeNode* node,int idx){
        BTreeNode* child=node->children[idx];
        BTreeNode* sibling=node->children[idx+1];
        child->keys.push_back(node->keys[idx]);
        for(int i=0;i<sibling->keys.size();i++){
            child->keys.push_back(sibling->keys[i]);
        }
        if(!child->isLeaf){
            for(int i=0;i<sibling->children.size();i++){
                child->children.push_back(sibling->children[i]);
            }
        }
        node->keys.erase(node->keys.begin()+idx);
        node->children.erase(node->children.begin()+idx+1);
        delete sibling;
    }
    int findKey(BTreeNode* node,T key){
        int idx=0;
        while(idx<node->keys.size()&&node->keys[idx]<key){
            idx++;
        }
        return idx;
    }
    int getPred(BTreeNode* node,int idx){
        BTreeNode* cur=node->children[idx];
        while(!cur->isLeaf){
            cur=cur->children[cur->keys.size()];
        }
        return cur->keys[cur->keys.size()-1];
    }
    int getSucc(BTreeNode* node,int idx){
        BTreeNode* cur=node->children[idx+1];
        while(!cur->isLeaf){
            cur=cur->children[0];
        }
        return cur->keys[0];
    }
public:
    BTree(int level):M(level){
        root=new BTreeNode(true);
    }
    void insert(T key){
        insertNonFull(root, key);
        if(root->keys.size()==M){
            BTreeNode* newNode=new BTreeNode(false);
            newNode->children.push_back(root);
            splitChild(newNode,0);
            root=newNode;
        }
    }
    void del(T key){
        del(root,key);
        if(root->keys.size()==0){
            BTreeNode* tmp=root;
            if(root->isLeaf){
                root=nullptr;
            }else{
                root=root->children[0];
            }
            delete tmp;
        }
    }
    void traverse(){
        traverse(root);
        puts("");
    }
    bool search(T key){
        BTreeNode* node=root;
        while(node!=nullptr){
            int i=0;
            while(i<node->keys.size()&&key>node->keys[i]){
                i++;
            }
            if(i<node->keys.size()&&key==node->keys[i]){
                return true;
            }
            if(node->isLeaf){
                break;
            }else{
                node=node->children[i];
            }
        }
        return false;
    }
};
int x;
int main(){
    BTree<int> tree(5);
    while(1){
        cin>>x;
        if(x==-1)break;
        tree.insert(x);
    }
    tree.traverse();
    return 0;
}
/*
1 2 6 7 11 4 8 13 10 5 17 9 16 20 3 12 14 18 19 15
*/