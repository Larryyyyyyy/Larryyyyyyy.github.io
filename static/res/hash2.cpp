#include "header.h"
using namespace std;
template<typename T>
class hashTable{
private:
    vector<list<T>> table;
    int capacity;
    int current_size;
    int hash(T key)const{
        return key%capacity;
    }
public:
    hashTable(int init_capacity=8):capacity(init_capacity),current_size(0){
        table.resize(capacity);
    }
    void insert(T key){
        int idx=hash(key);
        if(find(key)){
            return;
        }
        table[idx].push_back(key);
        current_size++;
        if(current_size>capacity*0.75){
            resize();
        }
    }
    bool find(T key){
        int idx=hash(key);
        for(const T& elem:table[idx]){
            if(elem==key){
                return true;
            }
        }
        return false;
    }
    void remove(T key){
        int idx=hash(key);
        auto& chain=table[idx];
        for(auto it=chain.begin();it!=chain.end();++it){
            if(*it==key){
                chain.erase(it);
                current_size--;
                return;
            }
        }
        throw out_of_range("Element not found!");
    }
    void display()const{
        for (int i=0;i<capacity;++i){
            cout<<"Index "<<i<<": ";
            if(table[i].empty()){
                cout<<"EMPTY"<<endl;
            }else{
                for(const T& elem:table[i]){
                    cout<<elem<<" ";
                }
                puts("");
            }
        }
    }
    int get_capacity()const{
        return capacity;
    }
    int size()const{
        return current_size;
    }
private:
    void resize(){
        vector<list<T>> old_table=table;
        capacity*=2;
        table.clear();
        table.resize(capacity);
        current_size=0;
        for(const auto& chain:old_table){
            for(const T& elem:chain){
                insert(elem);
            }
        }
    }
};
int main(){
    hashTable<int> ht;
    ht.insert(10);
    ht.insert(20);
    ht.insert(30);
    ht.insert(40);
    ht.insert(50);
    ht.display();
    ht.remove(20);
    ht.display();
    return 0;
}