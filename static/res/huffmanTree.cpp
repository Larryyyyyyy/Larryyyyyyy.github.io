#include "header.h"
using namespace std;
template<typename T>
struct huffmanNode{
    T data;
    int frequency;
    shared_ptr<huffmanNode<T>> left,right;
    huffmanNode(T value,int freq):data(value),frequency(freq),left(nullptr),right(nullptr){}
    bool operator<(const huffmanNode<T>& other)const{
        return frequency<other.frequency;
    }
};
template<typename T>
struct compareHuffmanNode{
    bool operator()(const shared_ptr<huffmanNode<T>>& a,const shared_ptr<huffmanNode<T>>& b)const{
        return a->frequency>b->frequency;
    }
};
template<typename T>
class huffmanTree{
public:
    void buildhuffmanTree(const unordered_map<T,int>& frequencies){
        priority_queue<shared_ptr<huffmanNode<T>>,vector<shared_ptr<huffmanNode<T>>>,compareHuffmanNode<T>>minHeap;
        for(const auto& entry:frequencies){
            minHeap.push(make_shared<huffmanNode<T>>(entry.first,entry.second));
        }
        while(minHeap.size()>1){
            shared_ptr<huffmanNode<T>> left=minHeap.top();
            cout<<left->frequency<<endl;
            minHeap.pop();
            shared_ptr<huffmanNode<T>> right=minHeap.top();
            cout<<right->frequency<<endl;
            minHeap.pop();
            shared_ptr<huffmanNode<T>> newNode=make_shared<huffmanNode<T>>(T(),left->frequency+right->frequency);
            newNode->left=left;
            newNode->right=right;
            minHeap.push(newNode);
        }
        root=minHeap.top();
        generateCodes(root,"");
    }
    void printCodes()const{
        for (const auto& entry:huffmanCodes){
            cout<<entry.first<<": "<<entry.second<<endl;
        }
    }
private:
    shared_ptr<huffmanNode<T>> root;
    unordered_map<T,string> huffmanCodes;
    void generateCodes(shared_ptr<huffmanNode<T>> node,const string& code){
        if(!node)return;
        if(!node->left&&!node->right){
            huffmanCodes[node->data]=code;
        }
        generateCodes(node->left,code+"0");
        generateCodes(node->right,code+"1");
    }
};
int main(){
    unordered_map<char,int>frequencies={
        {'a', 5},
        {'b', 9},
        {'c', 12},
        {'d', 13},
        {'e', 16},
        {'f', 45}
    };
    huffmanTree<char> huffmanTree;
    huffmanTree.buildhuffmanTree(frequencies);
    cout<<"Huffman Codes:"<<endl;
    huffmanTree.printCodes();
    return 0;
}
/*
   
 p     p
c b  p   p
    f e d a
*/
