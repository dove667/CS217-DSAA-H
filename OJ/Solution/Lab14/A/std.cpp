#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef __int128 i128;
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=100010,M=1000010,INF=0x3f3f3f3f;
vector<int> h[N];
struct frac{
	i128 p,q,op;
	frac(i128 pp=0,i128 qq=1){if(qq<0)pp=-pp,qq=-qq;p=pp,q=qq;op=p<0;}
	ld val(){return (ld)p/q;}
	bool operator ==(const frac &a)const{return op==a.op&&p*a.q==q*a.p;}
	bool operator !=(const frac &a)const{return op!=a.op||p*a.q!=q*a.p;}
	bool operator <(const frac &a)const{return op!=a.op?op>a.op:p*a.q<q*a.p;}
	bool operator >(const frac &a)const{return op!=a.op?op<a.op:p*a.q>q*a.p;}
	bool operator <=(const frac& a)const{return (*this<a)||(*this==a);}
	bool operator >=(const frac& a)const{return (*this>a)||(*this==a);}
	friend istream &operator >>(istream &is,frac &a){ll p;is>>p,a=frac(p);return is;}
	friend ostream &operator <<(ostream &os,frac &a){return os<<fixed<<setprecision(0)<<(ld)a.p<<' '<<(ld)a.q;}
}f[N];
frac operator +(const frac &a,const frac &b){
	i128 p=a.p*b.q+a.q*b.p,q=a.q*b.q,g=__gcd(p,q);
	return frac(p/g,q/g);
}
frac operator *(const frac &a,const frac &b){
	i128 p=a.p*b.p,q=a.q*b.q,g=__gcd(p,q);
	return frac(p/g,q/g);
}
int n,m,cnt,d[N],g[N],deg[N];
queue<int> q;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1,x,y;i<=n;i++){
		cin>>x,d[i]=x;
		while(x--)cin>>y,h[i].pb(y),deg[y]++;
	}
	for(int i=1;i<=m;i++)
		f[i]=1,q.push(i);
	while(q.size()){
		int x=q.front();q.pop();
		g[++cnt]=x;
		for(int y:h[x])
			if(--deg[y],!deg[y])q.push(y);
	}
	for(int i=1;i<=n;i++)
		for(int y:h[g[i]])
			f[y]=f[y]+f[g[i]]*frac(1,d[g[i]]);
	for(int i=1;i<=n;i++)
		if(!d[i])cout<<f[i]<<'\n';
	return 0;
}
