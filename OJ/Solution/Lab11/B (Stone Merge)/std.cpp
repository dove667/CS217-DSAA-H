#include <algorithm>
#include <cstring>
#include <iostream>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=510,M=5010,INF=0x3f3f3f3f;
int n,ans0=INF,ans1=-INF,s[N],f[N][N],g[N][N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>s[i],s[i+n]=s[i];
	for(int i=1;i<=2*n;i++)
		s[i]+=s[i-1];
	memset(f,0x3f,sizeof(f));
	memset(g,-0x3f,sizeof(g));
	for(int i=1;i<=2*n;i++)
		f[i][i]=g[i][i]=0;
	for(int l=2;l<=n;l++)
		for(int i=1,j=i+l-1;j<=2*n;i++,j++)
			for(int k=i;k<j;k++)
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]+s[j]-s[i-1]),
				g[i][j]=max(g[i][j],g[i][k]+g[k+1][j]+s[j]-s[i-1]);
	for(int i=1;i<=n;i++)
		ans0=min(ans0,f[i][i+n-1]),
		ans1=max(ans1,g[i][i+n-1]);
	cout<<ans0<<'\n'<<ans1<<'\n';
	return 0;
}
