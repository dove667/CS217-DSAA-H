#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define p2 pair<int,int>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
int n,m0,m1,ans,res[2][N];
p2 b[2][N];
priority_queue<p2,vector<p2>,greater<p2> > p;
priority_queue<int,vector<int>,greater<int> > q;
void solve(int op,int m){
	while(p.size())p.pop();
	while(q.size())q.pop();
	for(int i=1;i<=n;i++)q.push(i);
	for(int i=1;i<=m;i++){
		while(p.size()&&p.top().fi<=b[op][i].fi)
			q.push(p.top().se),p.pop();
		if(!q.size())continue;
		res[op][q.top()]++;
		p.push(mp(b[op][i].se,q.top()));
		q.pop();
	}
	for(int i=1;i<=n;i++)
		res[op][i]+=res[op][i-1];
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m0>>m1;
	for(int i=1;i<=m0;i++)
		cin>>b[0][i].fi>>b[0][i].se;
	for(int i=1;i<=m1;i++)
		cin>>b[1][i].fi>>b[1][i].se;
	sort(b[0]+1,b[0]+m0+1);
	sort(b[1]+1,b[1]+m1+1);
	solve(0,m0),solve(1,m1);
	for(int i=0;i<=n;i++)
		ans=max(ans,res[0][i]+res[1][n-i]);
	cout<<ans<<'\n';
	return 0;
}
