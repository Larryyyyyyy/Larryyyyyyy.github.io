#include "header.h"
using namespace std;
int pre[]={1,2,3,4,5,6,7,8};
int in[]={4,3,5,2,7,6,8,1};
void post(int root,int start,int end){
    if(start>end)return;
    int i=start;
    while(i<end&&in[i]!=pre[root])i++;
    post(root+1,start,i-1);
    post(root+1+i-start,i+1,end);
    printf("%d ",pre[root]);
}
int main() {
    post(0,0,7);
    return 0;
}