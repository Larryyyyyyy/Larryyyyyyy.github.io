#include "header.h"
using namespace std;
template <typename T>
class doublyLinkedList{
private:
    struct Node{
        T data;
        Node* prev;
        Node* next;
        Node(T value):data(value),prev(nullptr),next(nullptr){}
    };
    Node* head;
    Node* tail;
    int size;
public:
    doublyLinkedList():head(nullptr),tail(nullptr),size(0){}
    doublyLinkedList(initializer_list<T> initList):head(nullptr),tail(nullptr),size(0){
        for(auto& item:initList){
            push_back(item);
        }
    }
    doublyLinkedList(doublyLinkedList&& t)noexcept:head(t.head),tail(t.tail),size(t.size){
        t.head=nullptr;
        t.tail=nullptr;
        t.size=0;
    }
    ~doublyLinkedList(){
        while(head){
            Node* temp=head;
            head=head->next;
            delete temp;
        }
    }
    int getSize()const{
        return size;
    }
    bool empty()const{
        return size==0;
    }
    void push_front(T value){
        Node* newNode=new Node(value);
        if(empty()){
            head=tail=newNode;
        }else{
            newNode->next=head;
            head->prev=newNode;
            head=newNode;
        }
        size++;
    }
    void push_back(T value){
        Node* newNode=new Node(value);
        if(empty()){
            head=tail=newNode;
        }else{
            newNode->prev=tail;
            tail->next=newNode;
            tail=newNode;
        }
        size++;
    }
    void pop_front(){
        if(empty()){
            throw invalid_argument("List is empty,cannot remove element!");
        }
        Node* temp=head;
        head=head->next;
        if(head){
            head->prev=nullptr;
        }else{
            tail=nullptr;
        }
        delete temp;
        --size;
    }
    void pop_back(){
        if(empty()){
            throw invalid_argument("List is empty,cannot remove element!");
        }
        Node* temp=tail;
        tail=tail->prev;
        if(tail){
            tail->next=nullptr;
        }else{
            head=nullptr;
        }
        delete temp;
        --size;
    }
    void printList()const{
        Node* current=head;
        while(current){
            cout<<current->data<<" ";
            current=current->next;
        }
        puts("");
    }
    void printListReverse()const{
        Node* current=tail;
        while(current){
            cout<<current->data<<" ";
            current=current->prev;
        }
        puts("");
    }
    Node* find(T value)const{
        Node* current=head;
        while(current){
            if(current->data==value){
                return current;
            }
            current=current->next;
        }
        return nullptr;
    }
    void insertAfter(Node* node,T value){
        if(!node){
            throw invalid_argument("Invalid node!");
        }
        Node* newNode=new Node(value);
        newNode->next=node->next;
        newNode->prev=node;
        if(node->next){
            node->next->prev=newNode;
        }else{
            tail=newNode;
        }
        node->next=newNode;
        size++;
    }
    void erase(Node* node) {
        if(!node){
            throw invalid_argument("Invalid node!");
        }
        if(node->prev){
            node->prev->next=node->next;
        }else{
            head=node->next;
        }
        if(node->next){
            node->next->prev=node->prev;
        }else{
            tail=node->prev;
        }
        delete node;
        size--;
    }
    Node* begin(){
        return head;
    }
    Node* end(){
        return tail;
    }
    bool operator==(const doublyLinkedList& t){
        if(size!=t.size)return false;
        Node* p=head,* p_t=t.head;
        for(int i=0;i<size;++i){
            if(p->data!=p_t->data)return false;
            p=p->next,p_t=p_t->next;
        }
        return true;
    }
    bool operator!=(const doublyLinkedList& t){
        return !(*this==t);
    }
    bool operator<(const doublyLinkedList& t){
        if(size<t.size)return true;
        if(size>t.size)return false;
        Node* p=head,* p_t=t.head;
        for(int i=0;i<size;++i){
            if(p->data<p_t->data)return true;
            p=p->next,p_t=p_t->next;
        }
        return false;
    }
    bool operator<=(const doublyLinkedList& t){
        if(size<t.size)return true;
        if(size>t.size)return false;
        Node* p=head,* p_t=t.head;
        for(int i=0;i<size;++i){
            if(p->data<p_t->data)return true;
            p=p->next,p_t=p_t->next;
        }
        return true;
    }
    bool operator>(const doublyLinkedList& t){
        return !(*this<t);
    }
    bool operator>=(const doublyLinkedList& t){
        return !(*this<=t);
    }
    doublyLinkedList& operator=(const doublyLinkedList &t){
        while(this->head){
            Node* temp=this->head;
            this->head=this->head->next;
            delete temp;
        }
        tail=nullptr;
        size=0;
        Node* current=t.head;
        while(current){
            push_back(current->data);
            current=current->next;
        }
        return *this;
    }
};
template <typename T>
void swap(doublyLinkedList<T>& x,doublyLinkedList<T>& y) {
    doublyLinkedList<T> temp=move(x);
    x=move(y);
    y=move(temp);
}
int main(){
    
    return 0;
}