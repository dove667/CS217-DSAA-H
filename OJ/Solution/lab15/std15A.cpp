#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=500010,M=1000010;
const ll INF=0x3f3f3f3f3f3f3f3f;

namespace nqio{
const unsigned R=4e5,W=4e5;
char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;
bool s;
struct q{
	__attribute__((always_inline))
	void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}
	void f(){fwrite(o,1,c-o,stdout);c=o;}
	~q(){f();}
	__attribute__((always_inline))
	void w(char x){*c=x;if(++c==d)f();}
	__attribute__((always_inline))
	q&operator>>(char&x){do r(x);while(x<=32);return*this;}
	__attribute__((always_inline))
	q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}
	template<typename t>__attribute__((always_inline))
	q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}
	__attribute__((always_inline))
	q&operator<<(char x){w(x);return*this;}
	q&operator<<(char*x){while(*x)w(*x++);return*this;}
	__attribute__((always_inline))
	q&operator<<(const char*x){while(*x)w(*x++);return*this;}
	template<typename t>__attribute__((always_inline))
	q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}
}qio;
}
using nqio::qio;

int head[N],ver[M],edge[M],Next[M],tot;
int n,m,s,t,cnt,num,pre[N],ans[N];
ll d[N];
int pos[N];
pair<ll,int> heap[N<<2]={mp(-INF,0)};
static inline void up(int p){
	while(heap[p]<heap[p>>1]){
		int x=heap[p].se,y=heap[p>>1].se;
		swap(heap[p],heap[p>>1]);
		swap(pos[x],pos[y]);
		p>>=1;
	}	
}
static inline void down(int p){
	int s=p<<1;
	while(s<=num){
		if(s<num&&heap[s]>heap[s+1])++s;
		if(heap[p]>heap[s]){
			int x=heap[p].se,y=heap[s].se;
			swap(heap[p],heap[s]);
			swap(pos[x],pos[y]);
			p=s,s=p<<1;
		}
		else break;
	}
}
static inline void insert(pair<ll,int> t){
	heap[++num]=t;
	pos[t.se]=num;
	up(num);
}
static inline void pop(){
	pos[heap[num].se]=1;
	heap[1]=heap[num--];
	down(1);
}
static inline void remove(int k){
	pos[heap[num].se]=k;
	heap[k]=heap[num--];
	up(k);
	down(k);
}
static inline void update(pair<ll,int> t){
	int x=t.se;
	heap[pos[x]]=t;
	up(pos[x]);
}
static inline pair<ll,int> top(){
	return heap[1];
}
static inline void add(int x,int y,int z){
	ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}
void dijkstra(int s){
	memset(d,0x3f,sizeof(d));
	d[s]=0;
	for(int i=1;i<=n;i++){
		heap[++num]=mp(d[i],i);
		pos[i]=num;
	}
	for(int i=n;i>=1;i--)down(i);
	while(num){
		int x=top().se;pop();
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i],z=edge[i];
			if(d[y]>d[x]+z){
				d[y]=d[x]+z;
				pre[y]=x;
				update(mp(d[y],y));
			}
		}
	}
}
int main(){
	qio>>n>>m>>s>>t,s++,t++;
	for(int i=1,x,y,z;i<=m;i++){
		qio>>x>>y>>z,x++,y++;
		add(x,y,z);
	}
	dijkstra(s);
	for(int i=t;i;i=pre[i])
		ans[++cnt]=i-1;
	if(d[t]==INF)return qio<<"-1\n",0;
	qio<<d[t]<<' '<<cnt-1<<'\n';
	for(int i=cnt;i>1;i--)
		qio<<ans[i]<<' '<<ans[i-1]<<'\n';
	return 0;
}
