#include <iostream>
#include <algorithm>
#include <numeric>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ptz __builtin_popcount
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=10010,M=1000010;
ll INF=0x3f3f3f3f3f3f3f3f;
int n,m,k,cnt,c[11],fa[N],sz[N];
ll ans=INF;
struct edge{
	int x,y,z,op;
	bool operator <(const edge &a)const{return z<a.z;}
}e[M],t[N];
int get(int x){return x==fa[x]?x:fa[x]=get(fa[x]);}
int merge(int x,int y){
	x=get(x),y=get(y);
	if(x==y)return 0;
	if(sz[x]>sz[y])swap(x,y);
	return fa[x]=y,sz[y]+=sz[x],1;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
		cin>>e[i].x>>e[i].y>>e[i].z;
	sort(e+1,e+m+1);
	iota(fa+1,fa+n+1,1);
	fill(sz+1,sz+n+1,1);
	for(int i=1;i<=m;i++){
		int x=e[i].x,y=e[i].y;
		if(!merge(x,y))continue;
		t[++cnt]=e[i];
		if(cnt==n-1)break;
	}
	for(int i=1;i<=k;i++){
		cin>>c[i-1];
		for(int j=1,z;j<=n;j++)
			cin>>z,t[++cnt]={i+n,j,z,i};
	}
	sort(t+1,t+cnt+1);
	for(int S=0;S<1<<k;S++){
		iota(fa+1,fa+n+k+1,1);
		fill(sz+1,sz+n+k+1,1);
		ll res=0,tot=0,del=ptz(S);
		for(int i=0;i<k;i++)
			if((S>>i)&1)res+=c[i];
		for(int i=1;i<=cnt;i++){
			int x=t[i].x,y=t[i].y,z=t[i].z,op=t[i].op;
			if(op&&!((S>>(op-1))&1))continue;
			if(!merge(x,y))continue;
			res+=z,++tot;
			if(tot==n+del-1)break;
		}
		ans=min(ans,res);
	}
	cout<<ans<<'\n';
	return 0;
}
