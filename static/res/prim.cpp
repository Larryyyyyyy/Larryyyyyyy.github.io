#include "header.h"
using namespace std;
int n,m,ans;
int rec[200010];
vector<vector<pair<int,int>>> v;
struct edge{
    int to,len;
    bool operator<(const edge& t)const{
        return len>t.len;
    }
};
priority_queue<edge> q;
int main(){
    int mix,miy,miz,minlen=0x7fffffff;
    scanf("%d%d",&n,&m);
    v.resize(n+1);
    for(int i=1,x,y,z;i<=m;++i){
        scanf("%d%d%d",&x,&y,&z);
        v[x].push_back({y,z});
        v[y].push_back({x,z});
        if(z<minlen)mix=x,miy=y,minlen=z;
    }
    ans=minlen;
    rec[mix]=rec[miy]=1;
    for(int i=0;i<v[mix].size();++i){
        if(!rec[v[mix][i].first]){
            q.push(edge{v[mix][i].first,v[mix][i].second});
        }
    }
    mix=miy;
    while(--n>1){
        for(int i=0;i<v[mix].size();++i){
            if(!rec[v[mix][i].first]){
                q.push(edge{v[mix][i].first,v[mix][i].second});
            }
        }
        while(rec[q.top().to])q.pop();
        rec[q.top().to]=1;
        ans+=q.top().len;
        mix=q.top().to;
        q.pop();
    }
    printf("%d",ans);
    return 0;
}