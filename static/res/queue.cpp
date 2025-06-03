#include "header.h"
using namespace std;
template <typename T=int>
class myQueue{
friend T;
private:
    struct Node{
        T data;
        Node* next;
        Node(T x):data(x),next(nullptr){}
    };
    Node* head;
    Node* tail;
    size_t siz;
public:
    myQueue():head(nullptr),tail(nullptr),siz(0){

    }
    ~myQueue(){
        while(head!=nullptr){
            Node* temp=head;
            head=head->next;
            delete temp;
        }
    }
    T front()const{
        if(siz==0){
            throw runtime_error("Queue is empty");
        }
        return head->data;
    }
    T back()const{
        if(siz==0){
            throw runtime_error("Queue is empty");
        }
        return tail->data;
    }
    void push(T x){
        Node* newNode=new Node(x);
        if(tail!=nullptr) {
            tail->next=newNode;
        }
        tail=newNode;
        if(head==nullptr){
            head=tail;
        }
        ++siz;
    }
    void pop(){
        if(siz==0){
            throw runtime_error("Queue is empty");
        }
        Node* temp=head;
        head=head->next;
        delete temp;
        --siz;
        if(siz==0){
            tail=nullptr;
        }
    }
    size_t size()const{
        return siz;
    }
    bool empty()const{
        return siz==0;
    }
    void swap(myQueue &q){
        if(typeid(q)!=typeid(*this)){
            throw runtime_error("Type is not the same");
        }
        swap(siz,q.siz);
        swap(head,q.head);
        swap(tail,q.tail);
    }
    void operator=(const myQueue &q){
        Node* temp=q.head,* now=head;
        while(!empty()){
            pop();
        }
        while(temp!=nullptr){
            push(temp->data);
            temp=temp->next;
        }
        siz=q.siz;
        delete temp;
        delete now;
    }
    bool operator==(const myQueue &q){
        if(siz!=q.siz)return false;
        Node* temp=q.head,* now=head;
        while(temp!=nullptr){
            if(temp->data!=now->data){
                delete temp;
                delete now;
                return false;
            }
            temp=temp->next;
            now=now->next;
        }
        delete temp;
        delete now;
        return true;
    }
};
int main(){
    myQueue<int> p,g;
    return 0;
}