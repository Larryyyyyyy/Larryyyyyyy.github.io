#include "header.h"
using namespace std;
template <typename T>
struct TreeNode{
    T data;
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;
    TreeNode(T value):data(value),left(nullptr),right(nullptr){}
};
template<typename T>
class BinaryTree{
public:
    BinaryTree():root(nullptr){}
    void insert(T value){
        root=insertRec(root,value);
    }
    void preOrder()const{
        preorderRec(root);
        puts("");
    }
    bool find(T value)const{
        return findRec(root, value);
    }
private:
    shared_ptr<TreeNode<T>> root;
    shared_ptr<TreeNode<T>> insertRec(shared_ptr<TreeNode<T>> node,T value){
        if(node==nullptr){
            return make_shared<TreeNode<T>>(value);
        }
        if(value<node->data){
            node->left=insertRec(node->left,value);
        }else{
            node->right=insertRec(node->right,value);
        }
        return node;
    }
    void preorderRec(shared_ptr<TreeNode<T>> node)const{
        if(node!=nullptr){
            cout<<node->data<<" ";
            preorderRec(node->left);
            preorderRec(node->right);
        }
    }
    void inorderRec(shared_ptr<TreeNode<T>> node)const{
        if (node != nullptr) {
            inorderRec(node->left);
            cout<<node->data<<" ";
            inorderRec(node->right);
        }
    }
    void postorderRec(shared_ptr<TreeNode<T>> node)const{
        if(node!=nullptr){
            postorderRec(node->left);
            postorderRec(node->right);
            cout<<node->data<<" ";
        }
    }
    bool findRec(shared_ptr<TreeNode<T>> node,T value)const{
        if(node==nullptr){
            return false;
        }
        if(node->data==value){
            return true;
        }else if(value<node->data){
            return findRec(node->left,value);
        }else{
            return findRec(node->right,value);
        }
    }
};
int main() {
    BinaryTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);
    tree.preOrder();
    cout<<(tree.find(7)?"Found":"Not Found")<<endl;
    cout<<(tree.find(20)?"Found":"Not Found")<<endl;
    return 0;
}
