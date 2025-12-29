#include<iostream>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=1000010,INF=0x3f3f3f3f;
int n,rt,top,stk[N],tr[N][10],e[N],tot;
string s;
void insert(int p,string &s){
	for(char c:s){
		if(!tr[p][c-'0'])tr[p][c-'0']=++tot;
		p=tr[p][c-'0'];
	}
	e[p]++;
}
void dfs(int p){
	if(e[p]){
		for(int i=1;i<=e[p];i++){
			for(int j=1;j<=top;j++)
				cout<<stk[j];
			cout<<'\n';
		}
	}
	for(int i=0;i<10;i++)
		if(tr[p][i])
			stk[++top]=i,dfs(tr[p][i]),top--;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;rt=++tot;
	for(int i=1;i<=n;i++){
		cin>>s;
		insert(rt,s);
	}
	top=0;
	dfs(rt);
	return 0;
}
