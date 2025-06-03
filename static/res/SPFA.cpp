#include "header.h"
#define N 200010
using namespace std;
int n,m,s;
struct edge{
    int v,w;
};
vector<edge> e[N];
int dis[N],cnt[N],vis[N];
queue<int> q;
constexpr int INF=0x3f3f3f3f;
bool spfa(int n,int s){
    memset(dis,0x3f,(n+1)*sizeof(int));
    dis[s]=0,vis[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop(),vis[u]=0;
        for(auto ed:e[u]){
            int v=ed.v,w=ed.w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                cnt[v]=cnt[u]+1;
                if(cnt[v]>=n)return false;
                if(!vis[v])q.push(v),vis[v]=1;
            }
        }
    }
    return true;
}
int main(){
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1,x,y,z;i<=m;++i){
        scanf("%d%d%d",&x,&y,&z);
        e[x].push_back({y,z});
    }
    spfa(n,s);
    for(int i=1;i<=n;++i)printf("%d ",dis[i]);
    return 0;
}