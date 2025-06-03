#include "header.h"
using namespace std;
template <typename T>
class seqQueue{
private:
    T* data;
    int capacity,size;
    int front,rear;
public:
    seqQueue(int initialCapacity=10):capacity(initialCapacity),size(0){
        data=new T[capacity];
        front=rear=0;
    }
    ~seqQueue(){
        delete[] data;
    }
    bool empty(){
        return front==rear;
    }
    bool full(){
        return rear==capacity;
    }
    void push(T value){
        if(full()){
            throw invalid_argument("The queue is full!");
        }
        data[rear++]=value;
    }
    void pop(){
        if(empty()){
            throw invalid_argument("The queue is empty!");
        }
        front++;
    }
    int getSize(){
        return size;
    }
    T getFront(){
        if(empty()){
            throw invalid_argument("The queue is empty!");
        }
        return data[front];
    }
    T getBack(){
        if(empty()){
            throw invalid_argument("The queue is empty!");
        }
        return data[rear];
    }
    void printQueue(){
        for(int i=front;i<rear;++i){
            cout<<data[i]<<" ";
        }
        puts("");
    }
};
int main() {
    seqQueue<int> q(5);
    q.push(1);
    q.push(2);
    q.push(3);
    q.printQueue();
    q.pop();
    q.printQueue();
    return 0;
}