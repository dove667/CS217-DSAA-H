#include <cassert>
#include <cctype>
#include <iostream>
#include <string>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=1000010,INF=0x3f3f3f3f;
int T,n,top,stk[N];
void solve(){
	cin>>n,top=0;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		if(isdigit(s[0]))stk[++top]=stoi(s);
		else if(s[0]=='+')stk[top-1]+=stk[top],top--;
		else if(s[0]=='-')stk[top-1]-=stk[top],top--;
		else if(s[0]=='*')stk[top-1]*=stk[top],top--;
	}
	assert(top==1);
	cout<<stk[top]<<'\n';
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
