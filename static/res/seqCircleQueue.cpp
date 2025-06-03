#include "header.h"
using namespace std;
template<typename T>
class seqCircleQueue{
private:
    T* data;
    int front,rear;
    int size,capacity;
public:
    seqCircleQueue():size(0),front(0),rear(0),capacity(2){
        data=new T[capacity];
    }
    seqCircleQueue(initializer_list<T> init):front(0),rear(init.size()),size(init.size()),capacity(init.size()*2){
        data=new T[capacity];
        copy(init.begin(),init.end(),data);
    }
    seqCircleQueue(const seqCircleQueue& other):size(other.size),front(other.front),rear(other.rear),capacity(other.capacity){
        data=new T[capacity];
        copy(other.data,other.data+size,data);
    }
    ~seqCircleQueue(){
        delete[] data;
    }
    T& operator[](int index){
        if(index>=size)throw out_of_range("Index out of range");
        return data[(front+index)%capacity];
    }
    const T& operator[](int index)const{
        if(index>=size)throw out_of_range("Index out of range");
        return data[(front+index)%capacity];
    }
    void push(const T&value){
        if(size==capacity){
            resize();
        }
        data[rear]=value;
        rear=(rear+1)%capacity;
        ++size;
    }
    void pop(){
        if(size==0)throw out_of_range("Queue is empty");
        front=(front+1)%capacity;
        --size;
    }
    int get_size()const{
        return size;
    }
    template <typename U>
    friend void swap(seqCircleQueue<U>& first,seqCircleQueue<U>& second){
        using std::swap;
        swap(first.data, second.data);
        swap(first.size, second.size);
        swap(first.front, second.front);
        swap(first.rear, second.rear);
        swap(first.capacity, second.capacity);
    }
    void print()const{
        if(size==0)throw out_of_range("Queue is empty");
        for (int i=0;i<size;++i){
            cout<<data[(front+i)%capacity]<<" ";
        }
        puts("");
    }
    seqCircleQueue& operator=(const seqCircleQueue& other){
        if(this!=&other){
            delete[] data;
            front=other.front;
            rear=other.rear;
            size=other.size;
            capacity=other.capacity;
            data=new T[capacity];
            copy(other.data,other.data+size,data);
        }
        return *this;
    }
    bool operator==(const seqCircleQueue& other)const{
        if (size != other.size) return false;
        for (int i=0;i<size;++i){
            if(data[(front+i)%capacity]!=other.data[(other.front+i)%other.capacity])return false;
        }
        return true;
    }
    bool operator!=(const seqCircleQueue& other)const{
        return !(*this==other);
    }
    bool operator<(const seqCircleQueue& other)const{
        if(size<other.size)return ture;
        if(size>other.size)return false;
        for (int i=0;i<size;++i){
            if(data[(front+i)%capacity]<other.data[(other.front+i)%other.capacity])return true;
            if(data[(front+i)%capacity]>other.data[(other.front+i)%other.capacity])return false;
        }
        return false;
    }
    bool operator<=(const seqCircleQueue& other)const{
        return *this<other||*this==other;
    }
    bool operator>(const seqCircleQueue& other)const{
        return !(*this<=other);
    }
    bool operator>=(const seqCircleQueue& other)const{
        return !(*this<other);
    }
private:
    void resize(){
        capacity*=2;
        T* new_data=new T[capacity];
        for (int i=0;i<size;++i){
            new_data[i]=data[(front+i)%capacity];
        }
        delete[] data;
        data=new_data;
        front=0;
        rear=size;
    }
};
int main() {
    seqCircleQueue<int> cq={1,1,4,5,1,4};
    cq.push(6);
    cq.push(7);
    cq.print();
    cq.pop();
    cq.pop();
    cq.print();
    seqCircleQueue<int> cq2={3, 4, 5, 6, 7};
    cout<<(cq==cq2)<<endl;
    seqCircleQueue<int> cq3={10,20,30};
    swap(cq,cq3);
    cq.print();
    cq3.print();
    return 0;
}