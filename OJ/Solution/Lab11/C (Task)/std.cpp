#include <algorithm>
#include <cstring>
#include <iostream>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define int ll
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=10010,M=100010,INF=0x3f3f3f3f;
int n,s,t[N],c[N],f[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>s;
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++){
		cin>>t[i]>>c[i];
		t[i]+=t[i-1];
		c[i]+=c[i-1];
	}
	f[0]=s*c[n];
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++)
			f[i]=min(f[i],f[j]+t[i]*(c[i]-c[j])+s*(c[n]-c[i]));
	cout<<f[n]<<'\n';
	return 0;
}
