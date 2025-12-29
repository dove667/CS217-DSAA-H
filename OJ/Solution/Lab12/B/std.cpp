#include <iostream>
#include <map>
#define fi first
#define se second
#define int ll
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,INF=0x3f3f3f3f;
int T,n,k,res,ans;
map<int,int> t;
void solve(){
	cin>>n>>k;
	ans=res=0,t.clear();
	for(int i=1,c,w,f;i<=n;i++)
		cin>>c>>w>>f,t[f]+=w*c,res+=w*c;
	if(res%k)t[0]+=k-res%k;
	res=0;
	for(pair<int,int> z:t){
		if(res+z.se>=k)
			ans+=z.fi,z.se-=k-res,res=0;
		ans+=(z.se/k)*z.fi,res+=z.se%k;
	}
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
