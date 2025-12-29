#include <iostream>
#include <queue>
#include <string>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=1010,M=1000010,INF=0x3f3f3f3f;
int n,m,c[13];
string s[N],t[N];
void out(string &s){
	for(char c:s)
		if(c^'.')cout<<c;
	cout<<'\n';
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>s[i],m=max(m,(int)s[i].size());
	for(int i=1;i<=n;i++)
		while((int)s[i].size()<m)
			s[i].pb('.');
	for(int k=m-1;~k;k--){
		for(int i=0;i<13;i++)c[i]=0;
		for(int i=n;i;i--)c[s[i][k]-'.']++;
		for(int i=0;i<13;i++)c[i]+=c[i-1];
		for(int i=n;i;i--)t[c[s[i][k]-'.']--]=s[i];
		for(int i=n;i;i--)s[i]=t[i];
	}
	for(int i=1;i<=n;i++)
		out(s[i]);
	return 0;
}
