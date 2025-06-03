#include "header.h"
using namespace std;
template<typename T>
class seqDeque{
private:
    T* data;
    int size;
    int capacity;
    void resize(){
        capacity*=2;
        T* new_data=new T[capacity];
        copy(data,data + size,new_data);
        delete[] data;
        data=new_data;
    }
public:
    seqDeque():size(0),capacity(2){
        data=new T[capacity];
    }
    seqDeque(initializer_list<T> init):size(init.size()),capacity(init.size()*2) {
        data=new T[capacity];
        copy(init.begin(),init.end(),data);
    }
    ~seqDeque() {
        delete[] data;
    }
    seqDeque(const seqDeque& other):size(other.size),capacity(other.capacity){
        data=new T[capacity];
        copy(other.data,other.data + size,data);
    }
    void push_back(const T& value){
        if(size==capacity){
            resize();
        }
        data[size++]=value;
    }
    void push_front(const T& value){
        if(size==capacity){
            resize();
        }
        for(int i=size;i>0;--i){
            data[i]=data[i-1];
        }
        data[0]=value;
        ++size;
    }
    void pop_back(){
        if(size==0)throw out_of_range("seqDeque is empty");
        --size;
    }
    void pop_front(){
        if(size==0)throw out_of_range("seqDeque is empty");
        for (int i=0;i<size-1;++i) {
            data[i]=data[i+1];
        }
        --size;
    }
    int get_size()const{
        return size;
    }
    bool empty()const{
        return (size==0);
    }
    T* begin(){
        return data;
    }
    T* end(){
        return data+size;
    }
    seqDeque& operator=(const seqDeque& other){
        if(this!=&other){
            delete[] data;
            size=other.size;
            capacity=other.capacity;
            data=new T[capacity];
            copy(other.data,other.data+size,data);
        }
        return *this;
    }
    bool operator==(const seqDeque& other)const{
        if(size!=other.size)return false;
        for(int i=0;i<size;++i){
            if(data[i]!=other.data[i])return false;
        }
        return true;
    }
    bool operator!=(const seqDeque& other)const{
        return !(*this==other);
    }
    bool operator<(const seqDeque& other)const{
        if(size<other.size)return true;
        if(size>other.size)return false;
        for (int i=0;i<size;++i) {
            if (data[i]<other.data[i])return true;
            if (data[i]>other.data[i])return false;
        }
        return false;
    }
    bool operator<=(const seqDeque& other)const{
        return (*this<other||*this==other);
    }
    bool operator>(const seqDeque& other)const{
        return !(*this<=other);
    }
    bool operator>=(const seqDeque& other)const{
        return !(*this<other);
    }
    T& operator[](int index){
        if (index>=size)throw out_of_range("Index out of range");
        return data[index];
    }
    const T& operator[](int index)const{
        if (index>=size)throw out_of_range("Index out of range");
        return data[index];
    }
    template<typename U>
    friend void swap(seqDeque<U>& first,seqDeque<U>& second){
        using std::swap;
        swap(first.data,second.data);
        swap(first.size,second.size);
        swap(first.capacity,second.capacity);
    }
    void print()const{
        for(int i=0;i<size;++i){
            cout<<data[i]<<" ";
        }
        puts("");
    }
};
int main(){
    seqDeque<int> dq={1,1,4,5,1,4};
    dq.push_back(6);
    dq.push_front(0);
    sort(dq.begin(),dq.end());
    dq.print();
    dq.pop_back();
    dq.pop_front();
    dq.print();
    seqDeque<int> dq2={1,9,1,9,8,1,0};
    cout<<(dq==dq2)<<endl;
    seqDeque<int> dq3={10,20,30};
    swap(dq, dq3);
    dq.print();
    dq3.print();
    return 0;
}