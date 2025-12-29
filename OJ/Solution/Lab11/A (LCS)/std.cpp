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
const int N=3010,M=30010,INF=0x3f3f3f3f;
int n,m,f[2][N],g[2][N];
string s,t;
bool cmax(int &x,int y){
	if(y>=x){x=y;return 1;}
	return 0;
}
void dp(int ux,int uy,int dx,int dy){
	if(dx==ux+1){
		for(int i=uy+1;i<=dy;i++)
			if(s[dx]==t[i]){cout<<t[i];break;}
		return;
	}
	int mid=(ux+dx)>>1;
	for(int i=uy;i<=dy;i++)
		f[0][i]=f[1][i]=g[0][i]=g[1][i]=0;
	int _i=1,_j=1;
	for(int i=ux+1;i<=mid;i++,_i^=1)
		for(int j=uy+1;j<=dy;j++){
			if(s[i]==t[j])cmax(f[_i][j],f[_i^1][j-1]+1);
			cmax(f[_i][j],max(f[_i^1][j],f[_i][j-1]));
		}
	for(int i=dx-1;i>=mid;i--,_j^=1)
		for(int j=dy-1;j>=uy;j--){
			if(s[i+1]==t[j+1])cmax(g[_j][j],g[_j^1][j+1]+1);
			cmax(g[_j][j],max(g[_j^1][j],g[_j][j+1]));
		}
	_i^=1,_j^=1;
	int pos=-1,res=0;
	for(int i=uy;i<=dy;i++)
		if(cmax(res,f[_i][i]+g[_j][i]))pos=i;
	dp(ux,uy,mid,pos);
	dp(mid,pos,dx,dy);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>s>>t;
	n=s.size(),m=t.size();
	s=" "+s,t=" "+t;
	dp(0,0,n,m);
	return 0;
}
