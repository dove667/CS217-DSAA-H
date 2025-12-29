#include <algorithm>
#include <cstdio>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=500010,M=5000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int T,n,ans,a[N];
struct SegmentTree{
	int l,r;
	int dat,tag;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
	#define dat(x) tree[x].dat
	#define tag(x) tree[x].tag
}tree[N<<2];
void pushup(int x){
	dat(x)=max(dat(x<<1),dat(x<<1|1));
	tag(x)=min(tag(x<<1),tag(x<<1|1));
}
void build(int x,int l,int r){
	l(x)=l,r(x)=r;dat(x)=tag(x)=0;
	if(l==r){dat(x)=tag(x)=a[l];return;}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void insert(int x,int pos,int val){
	int l=l(x),r=r(x);
	if(l==r){dat(x)=tag(x)=val;return;}
	int mid=(l+r)>>1;
	if(pos<=mid)insert(x<<1,pos,val);
	if(pos>mid)insert(x<<1|1,pos,val);
	pushup(x);
}
int query1(int x,int L,int R,int val){
	int l=l(x),r=r(x);
	if(dat(x)<val)return 0;
	if(l==r)return l;
	if(L<=l&&r<=R){
		int res=query1(x<<1,L,R,val);
		if(res)return res;
		return query1(x<<1|1,L,R,val);
	}
	if(L<=r(x<<1)){
		int res=query1(x<<1,L,R,val);
		if(res)return res;
	}
	return query1(x<<1|1,L,R,val);
}
int	query2(int x,int L,int R,int val){
	int l=l(x),r=r(x);
	if(tag(x)>val)return 0;
	if(l==r)return l;
	if(L<=l&&r<=R){
		int res=query2(x<<1|1,L,R,val);
		if(res)return res;
		return query2(x<<1,L,R,val);
	}
	if(l(x<<1|1)<=R){
		int res=query2(x<<1|1,L,R,val);
		if(res)return res;
	}
	return query2(x<<1,L,R,val);
}
int partition(int l,int r){
	int mid=(l+r)>>1,p=a[mid];
	int i=l-1,j=r+1;
	while(1){
		i=query1(1,i+1,n,p);
		j=query2(1,1,j-1,p);
		if(i>=j)return j;
		insert(1,i,a[j]);
		insert(1,j,a[i]);
		swap(a[i],a[j]);
		ans++;
	}
}
void qsort(int l,int r){
	if(l<0||r<0||l>=r)return;
	int p=partition(l,r);
	qsort(l,p);
	qsort(p+1,r);
}
void solve(){
	scanf("%d",&n);ans=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	qsort(1,n);
	printf("%d\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--)solve();
	return 0;
}
