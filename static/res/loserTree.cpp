#include "header.h"
using namespace std;
template <typename T>
struct LoserTree{
    vector<int> losers;
    vector<vector<T>> segments;
    explicit LoserTree(int k):losers(k,-1),segments(k){}
    void adjust(int s){
        int t=(losers.size()+s)/2;
        int current=s;
        while(t>0){
            if(losers[t]==-1){
                losers[t]=current;
                break;
            }else{
                T a=segments[current].empty()?numeric_limits<T>::max():segments[current].front();
                T b=segments[losers[t]].empty()?numeric_limits<T>::max():segments[losers[t]].front();
                if(a>b){
                    swap(current,losers[t]);
                }
            }
            t/=2;
        }
        losers[0]=current;
    }
    void multiwayMerge(){
        while(true){
            int winner=losers[0];
            if(segments[winner].empty()){
                break;
            }
            cout<<segments[winner].front()<<" ";
            segments[winner].erase(segments[winner].begin());
            adjust(winner);
        }
        cout<<endl;
    }
    void printTree()const{
        for(size_t i=0;i<segments.size();++i){
            cout<<"Segment "<<i<<": ";
            for(const auto &elem:segments[i]){
                cout<<elem<<" ";
            }
            cout << "\n";
        }
    }
};
void runTest(const vector<vector<int>> &data){
    int k=(int)data.size();
    LoserTree<int> tree(k);
    for(int i=0;i<k;++i){
        tree.segments[i]=data[i];
    }
    for(int i=k-1;i>=0;--i){
        tree.adjust(i);
    }
    tree.multiwayMerge();
}
int n;
int main(){
    cin>>n;
    vector<vector<int>>data(n);
    for(int i=0;i<n;++i){
        int m;
        cin >> m;
        data[i].resize(m);
        for(int j=0;j<m;++j)cin>>data[i][j];
    }
    runTest(data);
    return 0;
}
/*
3
3 1 2 3
4 4 5 6 7
3 8 9 10
*/