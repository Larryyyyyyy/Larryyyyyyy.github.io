#include "header.h"
#define ll long long
#define N 800010
using namespace std;
ll n,m,s,dis[N];
bool f[N];
vector<ll> v[N];
vector<ll> len[N];
struct node{
	ll x,y;
	const bool operator<(const node& n2)const{
		return x>n2.x;
	}
};
priority_queue<node,vector<node>,less<node>>q;
ll read(){
	char c=getchar();
	ll x=0,f=1;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-48,c=getchar();}
	return x*f;
}
int main(){
	n=read(),m=read(),s=read();
	for(ll i=1,x,y,z;i<=m;++i){
		x=read(),y=read(),z=read();
		v[x].push_back(y);
		len[x].push_back(z);
	}
	memset(dis,0x7f,sizeof(dis));
	dis[s]=0;
	node t;
	t.x=dis[s],t.y=s;
	q.push(t);
	while(!q.empty()){
		t=q.top();
		q.pop();
		ll now=t.y;
		if(f[t.y])continue;
		f[now]=1;
		for (ll i=0;i<v[now].size();++i){
			if(dis[v[now][i]]>dis[now]+len[now][i]){
				dis[v[now][i]]=dis[now]+len[now][i];
				if(!f[v[now][i]]){
					t.x=dis[v[now][i]],t.y=v[now][i];
					q.push(t);
				}
			}
		}
	}
	for (ll i=1;i<=n;++i){
		printf("%lld ",dis[i]);
	}
	return 0;
}