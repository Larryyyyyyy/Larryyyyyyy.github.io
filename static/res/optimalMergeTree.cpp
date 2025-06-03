#include "header.h"
using namespace std;
template<typename T>
class optimalMergeTree{
private:
    int m,k;
    struct Node{
        T data;
        vector<Node> children;
        Node():data(0){}
        Node(T data):data(data){}
        bool operator<(const Node& t)const{
            return data>t.data;
        }
    };
    priority_queue<Node> q;
    T WPL(Node p,T dis){
        T res=0;
        if(!p.children.empty())
        for(int i=0;i<p.children.size();++i){
            res+=WPL(p.children[i],dis+1);
        }
        else{
            return p.data*dis;
        }
        return res;
    }
public:
    optimalMergeTree(int m,int k):m(m),k(k){}
    void insert(int key){
        q.push(Node(key));
    }
    void merge(){
        while(q.size()>=k){
            Node p;
            int res=0,cnt=0;
            while(!q.empty()){
                ++cnt;
                res+=q.top().data;
                p.children.push_back(q.top());
                q.pop();
                if(cnt==3)break;
            }
            p.data=res;
            q.push(p);
        }
    }
    T calWPL(){
        merge();
        T res=0;
        for(int i=0;i<q.top().children.size();++i){
            res+=WPL(q.top().children[i],1);
        }
        return res;
    }
};
int n,k;
int main(){
    cin>>n>>k;
    optimalMergeTree<int> tree(n,k);
    if((n-1)%(k-1)){
        for(int i=1;i<=k-1-(n-1)%(k-1);++i){
            tree.insert(0);
        }
    }
    for(int i=0,x;i<n;++i){
        cin>>x;
        tree.insert(x);
    }
    cout<<tree.calWPL();
    return 0;
}
/*
11 3
1 3 5 7 9 13 16 20 24 30 38
*/