#include "header.h"
using namespace std;
class linkedString{
private:
    struct Node{
        char data;
        Node* next;
        Node(const char& value):data(value),next(nullptr){}
    };
    Node* head;
    Node* tail;
    int length;
public:
    linkedString():head(nullptr),tail(nullptr),length(0){}
    linkedString(const char* str){
        int len=strlen(str);
        head=tail=nullptr;
        for(int i=0;i<len;++i) {
            append(str[i]);
        }
    }
    linkedString(initializer_list<char> init):head(nullptr),tail(nullptr),length(0){
        for(const auto& value:init){
            append(value);
        }
    }
    linkedString(const linkedString& other):head(nullptr),tail(nullptr),length(0){
        Node* temp=other.head;
        while(temp){
            append(temp->data);
            temp=temp->next;
        }
    }
    ~linkedString(){
        Node* current=head;
        while(current){
            Node* next=current->next;
            delete current;
            current=next;
        }
    }
    int getLength()const{
        return length;
    }
    char* c_str()const{
        char* str=new char[length+1];
        Node* temp=head;
        for (int i=0;i<length;++i){
            str[i]=temp->data;
            temp=temp->next;
        }
        str[length]='\0';
        return str;
    }
    void append(const char& value){
        Node* newNode=new Node(value);
        if(tail){
            tail->next=newNode;
            tail=newNode;
        }else{
            head=tail=newNode;
        }
        ++length;
    }
    linkedString append(linkedString s){
        length+=s.length;
        while(s.head){
            tail->next=new Node(s.head->data);
            tail=tail->next;
            s.head=s.head->next;
        }
        return *this;
    }
    void remove(int pos){
        if(pos>=length)throw out_of_range("Position out of range");
        Node* current=head;
        if(pos==0){
            head=current->next;
            delete current;
        }else{
            Node* prev=nullptr;
            for(int i=0;i<pos;++i){
                prev=current;
                current=current->next;
            }
            prev->next=current->next;
            if(current==tail){
                tail=prev;
            }
            delete current;
        }
        --length;
    }
    void print()const{
        Node* temp=head;
        while(temp){
            cout<<temp->data;
            temp=temp->next;
        }
        puts("");
    }
    linkedString& operator=(const linkedString& other){
        if(this!=&other){
            while(length>0){
                remove(0);
            }
            Node* temp=other.head;
            while(temp){
                append(temp->data);
                temp=temp->next;
            }
        }
        return *this;
    }
    bool operator==(const linkedString& other)const{
        if(length!=other.length)return false;
        Node* a=head;
        Node* b=other.head;
        while(a&&b){
            if(a->data!=b->data)return false;
            a=a->next;
            b=b->next;
        }
        return true;
    }
    bool operator!=(const linkedString& other)const{
        return !(*this==other);
    }
    bool operator<(const linkedString& other)const{
        Node* a=head;
        Node* b=other.head;
        while(a&&b){
            if(a->data<b->data)return true;
            if(a->data>b->data)return false;
            a=a->next;
            b=b->next;
        }
        return length<other.length;
    }
    bool operator<=(const linkedString& other)const{
        return *this<other||*this==other;
    }
    bool operator>(const linkedString& other)const{
        return !(*this<=other);
    }
    bool operator>=(const linkedString& other)const{
        return !(*this<other);
    }
    friend void swap(linkedString& first,linkedString& second) {
        using std::swap;
        swap(first.head, second.head);
        swap(first.tail, second.tail);
        swap(first.length, second.length);
    }
    friend void operator>>(istream& in,linkedString& s){
        char c;
        while(c=getchar()){
            if(c=='\n')break;
            s.append(c);
        }
    }
    friend ostream& operator<<(ostream& out,linkedString& s){
        Node* p=s.head;
        while(p){
            out<<p->data;
            p=p->next;
        }
        return out;
    }
};
int main(){
    linkedString str1;
    cin>>str1;
    linkedString str2 = "World";
    cout<<str2;
    str1.append(str2);
    cout<<str1;
    return 0;
}