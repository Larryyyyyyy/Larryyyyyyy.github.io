#include "header.h"
using namespace std;
template <typename T>
class seqStack{
private:
    T* data;
    int capacity;
    int size;
    //动态扩容
    void resize(int newCapacity){
        T* newData=new T[newCapacity];
        for(int i=0;i<size;++i){
            newData[i]=data[i];
        }
        delete[] data;
        data=newData;
        capacity=newCapacity;
    }
public:
    //初始化
    seqStack(int initialCapacity=10):capacity(initialCapacity),size(0){
        data=new T[capacity];
    }
    seqStack(initializer_list<T> initList):size(initList.size()),capacity(initList.size()){
        data=new T[capacity];
        int index=0;
        for(auto& item:initList){
            data[index++]=item;
        }
    }
    seqStack(seqStack&& t)noexcept:data(t.data),capacity(t.capacity),size(t.size){
        t.data=nullptr;
        t.capacity=0;
        t.size=0;
    }
    //析构
    ~seqStack(){
        delete[] data;
    }
    int getSize()const{
        return size;
    }
    int getCapacity()const{
        return capacity;
    }
    void shrink_to_fit(){
        if(capacity>size){
            resize(size);
        }
    }
    bool empty()const{
        return size==0;
    }
    void push(T element){
        if(size==capacity){
            resize(capacity*2);//扩容
        }
        data[size++]=element;
    }
    void pop(){
        --size;
        if(size>0&&size==capacity/4){
            resize(capacity/2);//缩容
        }
    }
    T top(){
        return data[size-1];
    }
    T get(int index)const{
        if(index<0||index>=size){
            throw invalid_argument("Index out of bounds");
        }
        return data[index];
    }
    void set(int index, T element){
        if(index<0||index>=size){
            throw invalid_argument("Index out of bounds");
        }
        data[index]=element;
    }
    int find(T element)const{
        for (int i=0;i<size;++i){
            if(data[i]==element){
                return i;
            }
        }
        return -1;
    }
    void print()const{
        for(int i=0;i<size;++i){
            cout<<data[i]<<" ";
        }
        puts("");
    }
    T* begin(){
        return data;
    }
    T* end(){
        return data+size;
    }
    bool operator==(const seqStack& t){
        if(size!=t.size)return false;
        for(int i=0;i<size;++i){
            if(data[i]!=t.data[i])return false;
        }
        return true;
    }
    bool operator!=(const seqStack& t){
        return !(*this==t);
    }
    bool operator<(const seqStack& t){
        if(size<t.size)return true;
        if(size>t.size)return false;
        for(int i=0;i<size;++i){
            if(data[i]<t.data[i])return true;
        }
        return false;
    }
    bool operator<=(const seqStack& t){
        if(size<t.size)return true;
        if(size>t.size)return false;
        for(int i=0;i<size;++i){
            if(data[i]<t.data[i])return true;
        }
        return true;
    }
    bool operator>(const seqStack& t){
        return !(*this<t);
    }
    bool operator>=(const seqStack& t){
        return !(*this<=t);
    }
    seqStack& operator=(seqStack& t){
        capacity=t.capacity;
        size=t.size;
        T* newData=new T[capacity];
        for(int i=0;i<size;++i){
            newData[i]=t.data[i];
        }
        delete[] data;
        this->data=newData;
        return *this;
    }
    T operator[](int index){
        if(index<0||index>=size){
            throw invalid_argument("Index out of bounds");
        }
        return data[index];
    }
};
int main(){
    return 0;
}