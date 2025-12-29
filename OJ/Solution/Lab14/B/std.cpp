#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <algorithm>
#include <bitset>
#include <iostream>
#include <string>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=310,M=4010,INF=0x3f3f3f3f;
int n,m,k,tot,col,ans,s[N],sz[N];
bitset<N> g[N],h[N],b,v;
void dfs1(int x){
	v[x]=0;
	for(;b=g[x]&v,b.any();)
		dfs1(b._Find_first());
	s[tot++]=x;
}
void dfs2(int x){
	v[x]=0,sz[col]++;
	for(;b=h[x]&v,b.any();)
		dfs2(b._Find_first());
}
void kosaraju(){
	fill(sz+1,sz+col+1,0);
	tot=col=0;
	for(int i=0;i<n;i++)v[i]=1;
	for(int i=0;i<n;i++)
		if(v[i])dfs1(i);
	for(int i=0;i<n;i++)v[i]=1;
	for(int i=n-1;~i;i--)
		if(v[s[i]])col++,dfs2(s[i]);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		for(int j=0;j<n;j++)
			g[i][j]=h[j][i]=(s[j]=='1');
	}
	while(m--){
		cin>>k;
		for(int i=1,x,y;i<=k;i++){
			cin>>x>>y,x--,y--;
			g[x].flip(y);
			h[y].flip(x);
		}
		kosaraju();
		ans=0;
		for(int i=1;i<=col;i++)
			ans+=sz[i]*(sz[i]-1)>>1;
		cout<<ans<<'\n';
	}
	return 0;
}
