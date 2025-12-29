#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
int n,m,s,t,deg[N],d[N],v[N];
vector<int> g[N],h[N];
queue<int> q;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		g[x].pb(y),h[y].pb(x);
		deg[x]++;
	}
	cin>>s>>t;
	q.push(t);
	while(q.size()){
		int x=q.front();q.pop();
		for(int y:h[x]){
			deg[y]--;
			if(!v[y])v[y]=1,q.push(y);
		}
	}
	fill(v+1,v+n+1,0);
	d[s]=1;
	if(!deg[s])q.push(s);
	while(q.size()){
		int x=q.front();q.pop();
		for(int y:g[x])
			if(!deg[y]&&!d[y]){
				d[y]=d[x]+1;
				q.push(y);
			}
	}
	cout<<d[t]-1<<'\n';
	return 0;
}
