#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <cassert>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=1000010,INF=0x3f3f3f3f;
int n,m,cnt,ans,top,a[N],stk[N];
char s[N],t[N];
vector<int> s1,s2;
struct node{
    int l,r,tag;
    #define l(x) tree[x].l
    #define r(x) tree[x].r
    #define tag(x) tree[x].tag
}tree[N];
int dfs(int p){
	if(p<=n)return a[p];
	if(t[p]=='!')return !dfs(l(p));
	int ls,rs;
	ls=dfs(l(p));
	rs=dfs(r(p));
	if(t[p]=='|'){
		if(ls)tag(r(p))=1;
		if(rs)tag(l(p))=1;
		return ls||rs;
	}
	if(t[p]=='&'){
		if(!ls)tag(r(p))=1;
		if(!rs)tag(l(p))=1;
		return ls&&rs;
	}
	return assert(false),-1;
}
void psh(int p){
	if(p<=n)return;
	tag(l(p))|=tag(p);
	tag(r(p))|=tag(p);
	psh(l(p));
	psh(r(p));
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin.getline(s,1e6);
	cin>>n,cnt=n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=0;s[i];i+=2){
		if(s[i]=='x'){
			int x=0;
			while(s[++i]!=' ')x=(x<<3)+(x<<1)+s[i]-'0';
			stk[++top]=x;
			--i;
		}
		if(s[i]=='&'){
			t[++cnt]='&';
			r(cnt)=stk[top--];
			l(cnt)=stk[top--];
			stk[++top]=cnt;
		}
		if(s[i]=='|'){
			t[++cnt]='|';
			r(cnt)=stk[top--];
			l(cnt)=stk[top--];
			stk[++top]=cnt;
		}
		if(s[i]=='!'){
			t[++cnt]='!';
			l(cnt)=stk[top--];
			stk[++top]=cnt;
		}
	}
	ans=dfs(cnt);
	psh(cnt);
	cin>>m;
	while(m--){
		int x;
		cin>>x;
		cout<<(tag(x)?ans:!ans)<<'\n';
	}
	return 0;
}
