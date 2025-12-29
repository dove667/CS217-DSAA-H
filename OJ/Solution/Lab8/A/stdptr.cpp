#include <algorithm>
#include <iostream>
#include <utility>
#define fi first
#define se second
#define mp make_pair
using namespace std;
const int N=1000010,INF=0x3f3f3f3f;
int n,p[N];
pair<int,int> b[N],ans[N];
struct node{
  int key,val;
  node *pre,*nxt;
}*nodes[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1,x;i<=n;i++)
		cin>>x,b[i]=mp(x,i);
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		p[b[i].se]=i;
		nodes[i]=new node{b[i].se,b[i].fi,nullptr,nullptr};
	}
	nodes[0]=nodes[n+1]=new node{INF,INF,nullptr,nullptr};
	for(int i=1;i<=n+1;i++){
		nodes[i-1]->nxt=nodes[i];
		nodes[i]->pre=nodes[i-1];
	}
	for(int i=n;i>1;i--){
		int k=p[i],val=b[k].fi;
		node *ls=nodes[k]->pre,*rs=nodes[k]->nxt;
		int l=val-ls->val,r=rs->val-val;
		if(rs->val==INF)ans[i]=mp(l,ls->key);
		else if(ls->val==INF)ans[i]=mp(r,rs->key);
		else if(l<=r)ans[i]=mp(l,ls->key);
		else ans[i]=mp(r,rs->key);
		rs->pre=ls,ls->nxt=rs;
	}
	for(int i=2;i<=n;i++)
		cout<<ans[i].fi<<' '<<ans[i].se<<'\n';
	return 0;
}
