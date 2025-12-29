#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#include <cassert>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
const ld a=0.7;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int m,rt,num,tot,ans,p[N],ch[N][2],val[N],cnt[N],sz[N],s1[N],s2[N];
void maintain(int x){
	sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];
	s1[x]=s1[ch[x][0]]+s1[ch[x][1]]+(cnt[x]>0);
	s2[x]=s2[ch[x][0]]+s2[ch[x][1]]+1;
}
int build(int l,int r){
	if(l>r)return 0;
	if(l==r){ch[p[l]][0]=ch[p[l]][1]=0;maintain(p[l]);return p[l];}
	int mid=(l+r)>>1;
	ch[p[mid]][0]=build(l,mid-1);
	ch[p[mid]][1]=build(mid+1,r);
	maintain(p[mid]);
	return p[mid];
}
void get(int x){
	if(!x)return;
	get(ch[x][0]);
	p[++num]=x;
	get(ch[x][1]);
}
bool bad(int x){return sz[x]&&(a*s2[x]<=max(s2[ch[x][0]],s2[ch[x][1]])||a*s2[x]>=s1[x]);}
void rebuild(int &x){num=0;get(x);x=build(1,num);}
void ins(int &x,int k){
	if(!x){
		x=++tot;val[x]=k;cnt[x]=1;
		maintain(x);
		return;
	}
	if(k==val[x])++cnt[x];
	else if(k<val[x])ins(ch[x][0],k);
	else ins(ch[x][1],k);
	maintain(x);
	if(bad(x))rebuild(x);
}
void del(int &x,int k){
	if(k==val[x])assert(cnt[x]),--cnt[x];
	else if(k<val[x])del(ch[x][0],k);
	else del(ch[x][1],k);
	maintain(x);
	if(bad(x))rebuild(x);
}
int rk(int x,int k){
	if(!x)return 1;
	if(k==val[x])return sz[ch[x][0]]+1;
	if(k<val[x])return rk(ch[x][0],k);
	return sz[ch[x][0]]+cnt[x]+rk(ch[x][1],k);
}
int kth(int x,int k){
	if(!x)return -1;
	if(sz[ch[x][0]]<k&&k<=sz[ch[x][0]]+cnt[x])return val[x];
	if(k<=sz[ch[x][0]])return kth(ch[x][0],k);
	return kth(ch[x][1],k-sz[ch[x][0]]-cnt[x]);
}
int pre(int k){return kth(rt,rk(rt,k)-1);}
int nxt(int k){return kth(rt,rk(rt,k+1));}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>m;
	while(m--){
		int opts,x;
		cin>>opts>>x;
		if(opts==1){ins(rt,x);}
		if(opts==2){del(rt,x);}
		if(opts==3){ans=rk(rt,x);cout<<ans<<'\n';}
		if(opts==4){ans=kth(rt,x);cout<<ans<<'\n';}
		if(opts==5){ans=pre(x);cout<<ans<<'\n';}
		if(opts==6){ans=nxt(x);cout<<ans<<'\n';}
	}
	return 0;
}
