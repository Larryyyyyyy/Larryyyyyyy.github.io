#include "header.h"
using namespace std;
template <typename T>
class hashTable{
private:
    struct Entry{
        T key;
        bool occupied;
        Entry():occupied(false){}
        Entry(T key):key(key),occupied(true){}
    };
    vector<Entry> table;
    int current_size;
    int capacity;
    int hash(T key)const{
        return key%capacity;
    }
    int probe(T key){
        int idx=hash(key);
        int original_idx=idx;
        while(table[idx].occupied&&table[idx].key!=key){
            idx=(idx+1)%capacity;
            if(idx==original_idx){
                throw overflow_error("Hash table is full!");
            }
        }
        return idx;
    }
    void resize(){
        vector<Entry> old_table=table;
        capacity*=2;
        table.clear();
        table.resize(capacity);
        current_size=0;
        for(const auto& entry:old_table){
            if(entry.occupied){
                insert(entry.key);
            }
        }
    }
public:
    hashTable(int init_capacity=8):capacity(init_capacity),current_size(0){
        table.resize(capacity);
    }
    void insert(T key){
        if(current_size>=capacity/2){
            resize();
        }
        int idx=probe(key);
        if(!table[idx].occupied){
            current_size++;
        }
        table[idx]=Entry(key);
    }
    bool find(T key){
        int idx=probe(key);
        return table[idx].occupied;
    }
    void remove(T key){
        int idx=probe(key);
        if(!table[idx].occupied){
            throw out_of_range("Key not found!");
        }
        table[idx].occupied=false;
        current_size--;
    }
    void display()const{
        for(int i=0;i<capacity;i++){
            if(table[i].occupied){
                cout<<"Index "<<i<<": "<<table[i].key<<endl;
            }else{
                cout<<"Index "<<i<<": empty"<<endl;
            }
        }
    }
    int size()const{
        return current_size;
    }
    int get_capacity()const{
        return capacity;
    }
};
int main(){
    hashTable<int> ht;
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(15);
    ht.display();
    ht.remove(20);
    ht.display();
    return 0;
}
