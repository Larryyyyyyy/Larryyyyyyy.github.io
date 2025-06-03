#include "header.h"
using namespace std;
template<typename T>
class generalizedTable{
public:
    enum generalizedTableType{ATOM,LIST};
    generalizedTable(generalizedTableType _type):element_type(_type){}
    virtual ~generalizedTable()=default;
    generalizedTableType type(){return element_type;}
    bool equal_type(const generalizedTable<T> &a){return this->type()==a.type();}
    virtual T& data()=0;
protected:
    generalizedTableType element_type;
};
template<typename T>
class GAtom:public generalizedTable<T>{
private:
public:
    T element;
    GAtom():generalizedTable<T>(generalizedTable<T>::ATOM){}
    GAtom(const T &e):generalizedTable<T>(generalizedTable<T>::ATOM),element(e){}
    ~GAtom(){};
    GAtom &operator=(const T &val){element=val;return *this;}
    T& data(){return element;}
};
template<typename T>
class GList:public generalizedTable<T>{
    struct node{
        generalizedTable<T>* element_ptr;
        node* next;
        node* prior;
        node():element_ptr(nullptr),next(this),prior(this){};
        node(generalizedTable<T>* _ptr,node* _n=nullptr,node* _p=nullptr):element_ptr(_ptr),next(_n),prior(_p){};
        ~node(){delete element_ptr;}
    };
    node* head;
public:
    GList():generalizedTable<T>(generalizedTable<T>::LIST){head=new node();}
    GList(const GList &glist):generalizedTable<T>(generalizedTable<T>::LIST){
        head=new node();
        generalizedTable<T>* item_ptr=nullptr;
        for(auto item:glist){
            switch(item->type()){
            case generalizedTable<T>::ATOM:
                item_ptr=new GAtom<T>(*dynamic_cast<GAtom<T>*>(item));break;
            case generalizedTable<T>::LIST:
                item_ptr=new GList<T>(*dynamic_cast<GList<T>*>(item));break;
            }
            auto last=head->prior;
            auto new_node=new node(item_ptr,head,last);
            last->next=new_node;
            head->prior=new_node;
        }
    } 
    ~GList(){
        auto node_ptr=head->next;
        while(node_ptr!=head){
            auto tmp=node_ptr;
            node_ptr=node_ptr->next;
            delete tmp;
        }
        delete head;
    }
    T& data(){return head->next->element_ptr->data();}
    class iterator{
        node* the_node;
    friend class iterator;
    public:
        iterator(const GList &glist){
            the_node=(glist.head)->next;
        }
        iterator(node * _node):the_node(_node){}
        iterator &operator++(){
            the_node=the_node->next; 
            return *this;
        }
        iterator operator++(int){
            auto tmp=*this;
            the_node=the_node->next;
            return tmp;
        }
        bool operator==(const iterator &rhs){
            return the_node==rhs.the_node||(the_node->element_ptr==nullptr&&rhs.the_node->element_ptr==nullptr);
        }
        bool operator!=(const iterator &rhs){return the_node!=rhs.the_node;}
        generalizedTable<T>* operator*(){return (the_node->element_ptr);}
    };
    iterator end()const{return iterator(head);};
    iterator begin()const{return iterator(*this);};
    void push_back(const T &item){
        generalizedTable<T>* item_ptr=nullptr;
        item_ptr=new GAtom<T>(item);
        auto last=head->prior;
        auto new_node=new node(item_ptr,head,last);
        last->next=new_node;
        head->prior=new_node;
    }
    void push_back(const GList<T> &item){
        generalizedTable<T>* item_ptr=nullptr;
        item_ptr=new GList<T>(item);
        auto last=head->prior;
        auto new_node=new node(item_ptr,head,last);
        last->next=new_node;
        head->prior=new_node;
    }
    void push_back(const GAtom<T> &item){
        generalizedTable<T>* item_ptr=nullptr;
        item_ptr=new GAtom<T>(item.element);
        auto last=head->prior;
        auto new_node=new node(item_ptr,head,last);
        last->next=new_node;
        head->prior=new_node;
    }
    int depth(){
        int depth=0;
        for(auto i:*this){
            if(i->type()==generalizedTable<T>::LIST){
                auto sublist_ptr=dynamic_cast<GList<T>*>(i);
                auto t=sublist_ptr->depth();
                if(t>depth)depth=t;
            }
        }
        return depth+1;
    }
    void print(){
        for(auto i:*this){
            if(i->type()==generalizedTable<T>::LIST){
                auto sublist_ptr=dynamic_cast<GList<T>*>(i);
                sublist_ptr->print();
            }
            else{
                cout<<i->data()<<" ";
            }
        }
    }
};
int main(){
    GAtom<int> v1(114514),v2(1919810);
    GList<int> p1,p2;
    p1.push_back(v1);
    p1.push_back(v2);
    p2.push_back(v1);
    p2.push_back(p1);
    cout<<p2.depth()<<endl;
    p2.print();
    return 0;
}