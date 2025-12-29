#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=1000010,INF=0x3f3f3f3f;
int n,m,tot,col,s[N],v[N],bl[N];
vector<int> g[N],h[N];
string p,cnf;
int get(int x){return n+x+(x<0);}
void add(int x,int y){
	g[get(-x)].pb(get(y)),g[get(-y)].pb(get(x));
	h[get(y)].pb(get(-x)),h[get(x)].pb(get(-y));
}
void dfs1(int x){
	v[x]=0;
	for(int y:g[x])
		if(v[y])dfs1(y);
	s[++tot]=x;
}
void dfs2(int x){
	v[x]=0,bl[x]=col;
	for(int y:h[x])
		if(v[y])dfs2(y);
}
void kosaraju(){
	fill(bl+1,bl+col+1,0);
	fill(v+1,v+2*n+1,1);
	tot=col=0;
	for(int i=1;i<=2*n;i++)
		if(v[i])dfs1(i);
	fill(v+1,v+2*n+1,1);
	for(int i=2*n;i;i--)
		if(v[s[i]])col++,dfs2(s[i]);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>p>>cnf>>n>>m;
	for(int i=1,x,y,z;i<=m;i++)
		cin>>x>>y>>z,add(x,y);
	kosaraju();
	for(int i=1;i<=n;i++)
		if(bl[get(i)]==bl[get(-i)])
			return cout<<"s UNSATISFIABLE\n",0;
	cout<<"s SATISFIABLE\nv ";
	for(int i=1;i<=n;i++)
		cout<<(bl[get(i)]>bl[get(-i)]?i:-i)<<' ';
	cout<<"0\n";
	return 0;
}
