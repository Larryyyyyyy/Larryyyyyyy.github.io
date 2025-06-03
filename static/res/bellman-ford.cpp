#include "header.h"
#define N 200010
using namespace std;
int n,m,s;
struct Edge{
  int u,v,w;
};
vector<Edge> edge;
int dis[N],u,v,w;
constexpr int INF=0x3f3f3f3f;
bool bellmanford(int n,int s){
    memset(dis,0x3f,(n+1)*sizeof(int));
    dis[s]=0;
    bool flag=false;
    for(int i=1;i<=n;i++){
        flag=false;
        for(int j=0;j<edge.size();j++){
            u=edge[j].u,v=edge[j].v,w=edge[j].w;
            if(dis[u]==INF)continue;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                flag=true;
            }
        }
        if(!flag){
            break;
        }
    }
    return flag;
}
int main(){
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1,x,y,z;i<=m;++i){
        scanf("%d%d%d",&x,&y,&z);
        edge.push_back({x,y,z});
    }
    bellmanford(n,s);
    for(int i=1;i<=n;++i)printf("%d ",dis[i]);
    return 0;
}