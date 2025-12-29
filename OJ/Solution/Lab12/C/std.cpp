#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
int T,n,m;
ll ans;
struct node{
	int l,r,id,op;
}p[N];
bool cmp1(const node &a,const node &b){
	return a.l!=b.l?a.l<b.l:a.r<b.r;
}
bool cmp2(const node &a,const node &b){
	return a.r>b.r;
}
void getans(){
	cout<<ans<<'\n';
	for(int i=1;i<=n;i++)
		if(p[i].op)cout<<p[i].id<<' ';
	sort(p+1,p+n+1,cmp2);
	for(int i=1;i<=n;i++)
		if(!p[i].op)cout<<p[i].id<<' ';
	cout<<'\n';
}
void solve(){
	cin>>n>>m;
	ans=0;
	for(int i=1;i<=n;i++){
		int l,r;
		cin>>l>>r;
		ans+=r-l;
		p[i]=(node){l,r,i,0};
	}
	sort(p+1,p+n+1,cmp1);
	int r,k=-1;
	for(int i=1;i<=n;i++)
		if(p[i].l<=m&&m<=p[i].r){
			k=i;
			break;
		}
		else if(p[i].l>=m){
			ans+=p[i].l-m;
			k=i;
			break;
		}
	if(k<0){
		getans();
		return;
	}
	r=p[k].r;
	p[k].op=1;
	for(int i=k+1;i<=n;i++){
		if(p[i].l<=r&&p[i].r>=r){
			p[i].op=1;
			r=p[i].r;
		}
		if(p[i].l>r){
			ans+=p[i].l-r;
			p[i].op=1;
			r=p[i].r;
		}
	}
	getans();
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
