#include "header.h"
using namespace std;
template<typename T>
class linkedQueue{
private:
    struct Node{
        T data;
        Node* next;
        Node(const T& value):data(value),next(nullptr){}
    };
    Node* front;
    Node* rear;
    int size;
public:
    linkedQueue():front(nullptr),rear(nullptr),size(0){}
    linkedQueue(initializer_list<T> init):front(nullptr),rear(nullptr),size(0){
        for(const auto& value:init)push(value);
    }
    ~linkedQueue(){
        while(!empty())pop();
    }
    linkedQueue(const linkedQueue& other):front(nullptr),rear(nullptr),size(0){
        Node* temp=other.front;
        while(temp){
            push(temp->data);
            temp=temp->next;
        }
    }
    bool empty()const{
        return size==0;
    }
    int getSize() const {
        return size;
    }
    void push(const T& value){
        Node* newNode=new Node(value);
        if(empty()){
            front=rear=newNode;
        }else{
            rear->next=newNode;
            rear=newNode;
        }
        ++size;
    }
    void pop(){
        if(empty())throw out_of_range("Queue is empty");
        Node* temp=front;
        front=front->next;
        delete temp;
        --size;
        if(empty())rear=nullptr;
    }
    T& peek(){
        if(empty())throw out_of_range("Queue is empty");
        return front->data;
    }
    void print()const{
        Node* temp=front;
        while(temp){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        puts("");
    }
    template<typename U>
    friend void swap(linkedQueue<U>& first,linkedQueue<U>& second){
        using std::swap;
        swap(first.front,second.front);
        swap(first.rear,second.rear);
        swap(first.size,second.size);
    }
    linkedQueue& operator=(const linkedQueue& other){
        if(this!=&other){
            while(!empty())pop();
            Node* temp=other.front;
            while(temp){
                push(temp->data);
                temp=temp->next;
            }
        }
        return *this;
    }
    bool operator==(const linkedQueue& other)const{
        if (size!=other.size)return false;
        Node* a=front,*b=other.front;
        while(a&&b){
            if(a->data!=b->data)return false;
            a=a->next;
            b=b->next;
        }
        return true;
    }
    bool operator!=(const linkedQueue& other)const{
        return !(*this==other);
    }
    bool operator<(const linkedQueue& other)const{
        Node* a=front,*b=other.front;
        while(a&&b){
            if(a->data<b->data)return true;
            if(a->data>b->data)return false;
            a=a->next;
            b=b->next;
        }
        return size<other.size;
    }
    bool operator<=(const linkedQueue& other)const{
        return *this<other||*this==other;
    }
    bool operator>(const linkedQueue& other)const{
        return !(*this<=other);
    }
    bool operator>=(const linkedQueue& other)const{
        return !(*this<other);
    }
};
int main(){
    linkedQueue<int> q={1,1,4,5,1,4};
    q.print();
    q.push(6);
    q.push(7);
    q.print();
    q.pop();
    q.print();
    linkedQueue<int> q2={1,9,1,9,8,1,0};
    cout<<(q==q2)<<endl;
    linkedQueue<int> q3={10,20,30};
    swap(q, q3);
    q.print();
    q3.print();
    return 0;
}