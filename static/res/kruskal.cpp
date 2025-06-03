#include "header.h"
using namespace std;
int n,m,ans;
int fth[200010];
struct edge{
    int x,y,len;
    bool operator<(const edge& t)const{
        return len>t.len;
    }
};
priority_queue<edge> q;
int getfth(int x){
    if(!fth[x])return x;
    return getfth(fth[x]);
}
void changefth(int x,int f){
    if(!x)return;
    changefth(fth[x],f);
    fth[x]=f;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,x,y,z;i<=m;++i){
        scanf("%d%d%d",&x,&y,&z);
        q.push({x,y,z});
    }
    fth[q.top().x]=q.top().y;
    fth[q.top().y]=0;
    ans=q.top().len;
    q.pop();
    while(n>2){
        if(getfth(q.top().x)!=getfth(q.top().y)){
            changefth(q.top().x,getfth(q.top().y));
            ans+=q.top().len;
            --n;
        }
        q.pop();
    }
    printf("%d",ans);
    return 0;
}