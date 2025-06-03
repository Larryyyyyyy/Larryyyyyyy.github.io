#include "header.h"
using namespace std;
template<typename T>
class seqBinaryTree{
private:
    vector<T> tree;
public:
    seqBinaryTree():tree(){}
    seqBinaryTree(const vector<T>& elements):tree(elements){}
    T getRoot()const{
        if(tree.empty()){
            throw runtime_error("Tree is empty!");
        }
        return tree[0];
    }
    T getLeftChild(int index)const{
        int leftIndex=2*index+1;
        if (leftIndex>=tree.size()){
            throw runtime_error("No left child for the node.");
        }
        return tree[leftIndex];
    }
    T getRightChild(int index)const{
        int rightIndex=2*index+2;
        if(rightIndex>=tree.size()){
            throw runtime_error("No right child for the node.");
        }
        return tree[rightIndex];
    }
    T getParent(int index)const{
        if(index==0){
            throw runtime_error("Root node has no parent.");
        }
        int parentIndex=(index-1)/2;
        return tree[parentIndex];
    }
    void addNode(const T& value){
        tree.push_back(value);
    }
    void printPreOrder(int index=0)const{
        if(index>=tree.size())return;
        cout<<tree[index]<<" ";
        printPreOrder(2*index+1);
        printPreOrder(2*index+2);
    }
    int size()const{
        return tree.size();
    }
};
int main(){
    seqBinaryTree<int> tree;
    tree.addNode(1);
    tree.addNode(2);
    tree.addNode(3);
    tree.addNode(4);
    tree.addNode(5);
    tree.addNode(6);
    tree.addNode(7);
    tree.printPreOrder();
    puts("");
    return 0;
}
