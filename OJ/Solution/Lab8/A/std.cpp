#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int N=1000010,INF=0x3f3f3f3f;
int n,p[N],pre[N],nxt[N];
pair<int,int> b[N],ans[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=n;i++)
		cin>>x,b[i]=mp(x,i);
	sort(b+1,b+n+1);
	for(int i=1;i<n;i++)
		assert(b[i].fi^b[i+1].fi);
	for(int i=1;i<=n;i++)
		p[b[i].se]=i,pre[i]=i-1,nxt[i]=i+1;
	for(int i=n;i>1;i--){
		int k=p[i],ls=pre[k],rs=nxt[k],val=b[k].fi;
		int l=val-b[ls].fi,r=b[rs].fi-val;
		if(rs>n)ans[i]=mp(l,b[ls].se);
		else if(!ls)ans[i]=mp(r,b[rs].se);
		else if(l<=r)ans[i]=mp(l,b[ls].se);
		else ans[i]=mp(r,b[rs].se);
		pre[rs]=ls,nxt[ls]=rs; 
	}
	for(int i=2;i<=n;i++)
		cout<<ans[i].fi<<' '<<ans[i].se<<'\n';
	return 0;
}
