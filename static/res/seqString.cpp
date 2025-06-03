#include "header.h"
using namespace std;
class seqString{
private:
    char* data;
    int length;
    int capacity;
public:
    seqString():data(new char[1]),length(0),capacity(1){
        data[0]='\0';
    }
    seqString(const char* str){
        length=strlen(str);
        capacity=length+1;
        data=new char[capacity];
        strcpy(data,str);
    }
    seqString(initializer_list<char> init):length(init.size()),capacity(init.size()+1){
        data=new char[capacity];
        int i=0;
        for(const auto& val:init) {
            data[i++]=val;
        }
        data[length]='\0';
    }
    seqString(const seqString& other):length(other.length),capacity(other.capacity){
        data=new char[capacity];
        strcpy(data,other.data);
    }
    ~seqString(){
        delete[] data;
    }
    int get_length()const{
        return length;
    }
    int size()const{
        return length;
    }
    int get_capacity()const{
        return capacity;
    }
    const char* c_str()const{
        return data;
    }
    void append(const seqString& other){
        int newLength=length+other.length;
        if(newLength>=capacity){
            capacity=newLength+1;
            char* newData=new char[capacity];
            strcpy(newData,data);
            strcat(newData,other.data);
            delete[] data;
            data=newData;
        }else{
            strcat(data,other.data);
        }
        length=newLength;
    }
    void remove(int pos){
        if(pos>=length)throw out_of_range("Position out of range");
        for (int i=pos;i<length-1;++i) {
            data[i]=data[i+1];
        }
        data[length-1]='\0';
        --length;
    }
    void print()const{
        cout<<data<<endl;
    }
    friend void swap(seqString& first,seqString& second){
        using std::swap;
        swap(first.data,second.data);
        swap(first.length,second.length);
        swap(first.capacity,second.capacity);
    }
    friend void operator>>(istream& in,seqString& s){
        char c;
        vector<char> q;
        while(c=getchar()){
            if(c=='\n')break;
            q.push_back(c);
        }
        s.capacity=q.size()+1;
        s.length=s.capacity-1;
        s.data=new char[s.capacity];
        for(int i=0;i<q.size();++i){
            s.data[i]=q[i];
        }
        s.data[s.length]='\0';
    }
    friend ostream& operator<<(ostream& out,seqString& s){
        for(int i=0;i<s.length;++i){
            out<<s.data[i];
        }
        return out;
    }
    seqString& operator=(const seqString& other){
        if(this!=&other){
            delete[] data;
            length=other.length;
            capacity=other.capacity;
            data=new char[capacity];
            strcpy(data,other.data);
        }
        return *this;
    }
    bool operator==(const seqString& other)const{
        return strcmp(data,other.data)==0;
    }
    bool operator!=(const seqString& other)const{
        return !(*this==other);
    }
    bool operator<(const seqString& other)const{
        return strcmp(data,other.data)<0;
    }
    bool operator<=(const seqString& other)const{
        return *this<other||*this==other;
    }
    bool operator>(const seqString& other)const{
        return !(*this<=other);
    }
    bool operator>=(const seqString& other)const{
        return !(*this<other);
    }
    char& operator[](int index){
        if(index>=length)throw out_of_range("Index out of range");
        return data[index];
    }
    const char& operator[](int index)const{
        if(index>=length)throw out_of_range("Index out of range");
        return data[index];
    }
};

int main(){
    seqString s;
    cin>>s;
    cout<<s;
    return 0;
}