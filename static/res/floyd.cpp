#include "header.h"
using namespace std;
int n,m;
int a[1010][1010];
int main(){
    scanf("%d%d",&n,&m);
    memset(a,0x7f,sizeof(a));
    for(int i=1,x,y,z;i<=m;++i){
        scanf("%d%d%d",&x,&y,&z);
        a[x][y]=z;
    }
    for(int k=1;k<=n;++k){
        for(int i=1;i<=n;++i){
            for(int j=1;j<=n;++j){
                a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
            }
        }
    }
    return 0;
}