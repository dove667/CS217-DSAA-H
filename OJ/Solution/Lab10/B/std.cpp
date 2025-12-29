#include <algorithm>
#include <cstdlib>
#include <iostream>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;

unsigned int ans,cnt;

struct node{
	node *l,*r;
	int val,cnt;
	int h,sz;
};

class AVL{
private:
	node *rt;
public:
	AVL(){
		rt=new node;
		rt->h=0;
		rt->sz=0;
		rt->l=rt;
		rt->r=rt;
	}
	bool insert(int x){
		bool op=0;
		ins(rt->l,x,op);
		return op;
	}
	bool erase(int x){
		bool op=0;
		del(rt->l,x,op);
		return op;
	}
	node *find(int x){
		node *res;
		fnd(rt->l,x,res);
		return res;
	}
	int rnk(int k){
		return rk(rt->l,k);
	}
	int kth(int k){
		return kt(rt->l,k);
	}
	int pre(int k){
		return kt(rt->l,rk(rt->l,k)-1);
	}
	int nxt(int k){
		return kt(rt->l,rk(rt->l,k+1));
	}
	void preorder(){
		dfs(rt->l);
	}
private:
	void build(node *&p,int val){
		p=new node;
		p->val=val;
		p->cnt=1;
		p->h=1;
		p->sz=0;
		p->l=rt;
		p->r=rt;
	}
	void maintain(node *&p){
		if(p==rt)return;
		p->h=max(p->l->h,p->r->h)+1;
		p->sz=p->l->sz+p->r->sz+p->cnt;
	}
	int bf(node *&p){
		if(p==rt)return 0;
		return p->l->h-p->r->h;
	}
	void zag(node *&p){
		node *q=p->r;
		p->r=q->l,q->l=p;
		p=q;
		maintain(p->l);
		maintain(p);
	}
	void zig(node *&p){
		node *q=p->l;
		p->l=q->r,q->r=p;
		p=q;
		maintain(p->r);
		maintain(p);
	}
	void rotate(node *&p){
		int f=bf(p);
		if(f>1){
			if(bf(p->l)<0)zag(p->l);
			zig(p);
		}
		if(f<-1){
			if(bf(p->r)>0)zig(p->r);
			zag(p);
		}
		maintain(p);
	}
	node *get(node *&p,node *&fa){
		node *res;
		if(p->l==rt){
			res=p;
			fa->l=p->r;
		}
		else{
			res=get(p->l,p);
            rotate(p);
		}
		return res;
	}
	void ins(node *&p,int k,bool &op){
		if(p==rt||p==nullptr){
			build(p,k);
			op=1;
		}
		else if(k==p->val){
			p->cnt++;
			op=1;
		}
		else if(k<p->val)ins(p->l,k,op);
		else if(k>p->val)ins(p->r,k,op);
		op?rotate(p):maintain(p);
	}
	void del(node *&p,int k,bool &op){
		if(p==rt||p==nullptr){
			op=0;
			return;
		}
		else if(k==p->val){
			if(p->cnt>1){
				p->cnt--;
				op=0;
				maintain(p);
				return;
			}
			node *tmp=p,*ls=p->l,*rs=p->r;
			if(ls!=rt&&rs!=rt){
				p=get(rs,rs);
				if(p!=rs)
					p->r=rs;
				p->l=ls;
			}
			else if(ls==rt)p=rs;
			else if(rs==rt)p=ls;
			op=1;
			delete tmp;
		}
		else if(k<p->val)del(p->l,k,op);
		else if(k>p->val)del(p->r,k,op);
		op?rotate(p):maintain(p);
	}
	void fnd(node *&p,int k,node *&res){
		if(p==rt||p==nullptr){
			res=nullptr;
			return;
		}
		else if(k==p->val){
			res=p;
			return;
		}
		else if(k<p->val)fnd(p->l,k,res);
		else if(k>p->val)fnd(p->r,k,res);
	}
	int rk(node *p,int k){
		if(p==rt||p==nullptr)return 1;
		if(k==p->val)return p->l->sz+1;
		if(k<p->val)return rk(p->l,k);
		return p->l->sz+p->cnt+rk(p->r,k);
	}
	int kt(node *p,int k){
		if(p==rt||p==nullptr)return -1;
		if(p->l->sz<k&&k<=p->l->sz+p->cnt)return p->val;
		if(k<=p->l->sz)return kt(p->l,k);
		return kt(p->r,k-p->l->sz-p->cnt);
	}
	void dfs(node *p){
		if(p==rt||p==nullptr)return;
		ans+=(++cnt)^abs(p->val);
		dfs(p->l);
		dfs(p->r);
	}
};

int m;

AVL tree;

int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>m;
	while(m--){
		int op,x;
		cin>>op>>x;
		if(op==1)tree.insert(x);
		if(op==2)tree.erase(x);
		if(op==3)cout<<tree.rnk(x)<<'\n';
		if(op==4)cout<<tree.kth(x)<<'\n';
		if(op==5)cout<<tree.pre(x)<<'\n';
		if(op==6)cout<<tree.nxt(x)<<'\n';
	}
	tree.preorder();
	cout<<ans<<'\n';
	return 0;
}
