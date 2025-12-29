#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=2000010;
const ll INF=0x3f3f3f3f3f3f3f3f;
int n,m,k,c,cnt,out[N],vis[N];
ll dis[N],v[N],w[N];
vector<pair<int,ll> > g[N],h[N];
vector<int> d[N];
priority_queue<pair<ll,int> > q;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>c>>n>>m>>k,cnt=n;
	for(int i=2;i<=k;i++)cin>>v[i];
	for(int i=2;i<=k;i++)cin>>w[i];
	for(int i=1;i<=n;i++){
		cin>>out[i],d[i].pb(i);
		for(int j=1,y,z;j<=out[i];j++){
			cin>>y>>z;
			g[i].pb(mp(y,z));
			++cnt;
			h[d[i].back()].pb(mp(cnt,v[j]));
			h[cnt].pb(mp(d[i].back(),w[j]));
			d[i].pb(cnt);
		}
	}
	for(int i=2;i<=k;i++)w[i]+=w[i-1];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=out[i];j++){
			int y=g[i][j-1].fi,z=g[i][j-1].se;
			int u=d[i][j],v=d[y][min(j,out[y])];
			if(j<=out[y])h[u].pb(mp(v,z));
			if(j>out[y]){
				++cnt;
				h[u].pb(mp(cnt,z));
				h[cnt].pb(mp(v,w[j]-w[out[y]]));
				d[y].pb(cnt);
			}
		}
	fill(dis+1,dis+cnt+1,INF);
	dis[1]=0;
	q.push(mp(0,1));
	while(q.size()){
		int x=q.top().se;q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(pair<int,ll> t:h[x]){
			int y=t.fi;ll z=t.se;
			if(dis[y]>dis[x]+z)
				dis[y]=dis[x]+z,q.push(mp(-dis[y],y));
		}
	}
	for(int i=1;i<=n;i++){
		for(int x:d[i])
			dis[i]=min(dis[i],dis[x]);
		cout<<(dis[i]^INF?dis[i]:-1)<<' ';
	}
	return 0;
}
