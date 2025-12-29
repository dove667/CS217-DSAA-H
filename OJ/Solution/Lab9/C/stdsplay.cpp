#include <cassert>
#include <iostream>
typedef long long LL;
typedef long double LD;
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
int n,m,rt,tot,fa[N],ch[N][2],val[N],cnt[N],sz[N];
struct Splay{
	void maintain(int x){sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+cnt[x];}
	bool get(int x){return x==ch[fa[x]][1];} 
	void clear(int x){ch[x][0]=ch[x][1]=fa[x]=sz[x]=cnt[x]=val[x]=0;}
	void rotate(int x){
		int y=fa[x],z=fa[y],chk=get(x);
		ch[y][chk]=ch[x][chk^1];
		if(ch[x][chk^1])fa[ch[x][chk^1]]=y;
		ch[x][chk^1]=y;
		fa[y]=x;
		fa[x]=z;
		if(z)ch[z][y==ch[z][1]]=x;
		maintain(y);
		maintain(x);
	}
	void splay(int x){
		for(int f=fa[x];f=fa[x],f;rotate(x))
			if(fa[f])rotate(get(x)==get(f)?f:x);
		rt=x;
	}
	void ins(int k){
		if(!rt){
			val[++tot]=k;
			cnt[tot]++;
			rt=tot;
			maintain(rt);
			return;
		}
		int cur=rt,f=0;
		while(1){
			if(val[cur]==k){
				cnt[cur]++;
				maintain(cur);
				maintain(f);
				splay(cur);
				break;
			}
			f=cur;
			cur=ch[cur][val[cur]<k];
			if(!cur){
				val[++tot]=k;
				cnt[tot]++;
				fa[tot]=f;
				ch[f][val[f]<k]=tot;
				maintain(tot);
				maintain(f);
				splay(tot);
				break;
			}
		}
	}
	int rk(int k){
		int res=0,cur=rt;
		while(cur){
			if(k<val[cur])cur=ch[cur][0];
			else{
				res+=sz[ch[cur][0]];
				if(k==val[cur]){
					splay(cur);
					return res;
				}
				res+=cnt[cur];
				cur=ch[cur][1];
			}
		}
		return res;
	}
	int kth(int k){
		int cur=rt;
		++k;
		while(1){
			if(ch[cur][0]&&k<=sz[ch[cur][0]]){
				cur=ch[cur][0];
			}
			else{
				k-=cnt[cur]+sz[ch[cur][0]];
				if(k<=0){
					splay(cur);
					return val[cur];
				}
				cur=ch[cur][1];
			}
		}
	}
	int pre(){
		int cur=ch[rt][0];
		while(ch[cur][1])cur=ch[cur][1];
		splay(cur);
		return cur;
	}
	int nxt(){
		int cur=ch[rt][1];
		while(ch[cur][0])cur=ch[cur][0];
		splay(cur);
		return cur;
	}
	void del(int k){
		rk(k);
		if(cnt[rt]>1){
			cnt[rt]--;
			maintain(rt);
			return;
		}
		if(!ch[rt][0]&&!ch[rt][1]){
			clear(rt);
			rt=0;
			return;
		}
		if(!ch[rt][0]){
			int cur=rt;
			rt=ch[rt][1];
			fa[rt]=0;
			clear(cur);
			return;
		}
		if(!ch[rt][1]){
			int cur=rt;
			rt=ch[rt][0];
			fa[rt]=0;
			clear(cur);
			return;
		}
		int cur=rt,x=pre();
		fa[ch[cur][1]]=x;
		ch[x][1]=ch[cur][1];
		clear(cur);
		maintain(rt);
	}	
}tree;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>m;
	tree.ins(-INF),tree.ins(INF);
	while(m--){
		int op,x;
		cin>>op>>x;
		if(op==1)tree.ins(x);
		if(op==2)tree.del(x);
		if(op==3)cout<<tree.rk(x)<<'\n';
		if(op==4)cout<<tree.kth(x)<<'\n';
		if(op==5)tree.ins(x),cout<<val[tree.pre()]<<'\n',tree.del(x);
		if(op==6)tree.ins(x),cout<<val[tree.nxt()]<<'\n',tree.del(x);
	}
	return 0;
}
