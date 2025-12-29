#include <iostream>
#include <utility>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=500010,M=5000010,INF=0x3f3f3f3f;
int n,a[N];
pair<int,int> partition(int l,int r){
	int i=l-1,j=l,k=r;
	for(;j<k;j++){
		if(a[j]<a[r]){
			i++;
			swap(a[i],a[j]);
		}
		else if(a[j]==a[r]){
			k--;
			swap(a[j],a[k]);
			j--;
		}
	}
	for(int p=r;p>=r-k+i+1+1;p--)
		swap(a[p],a[p-r+k-1]);
	return mp(i+1,i+r-k+1);
}
void qsort(int l,int r){
	if(l>=r)return;
	pair<int,int> t=partition(l,r);
	int p=t.fi,q=t.se;
	qsort(l,p-1);
	qsort(q+1,r);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	qsort(1,n);
	for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	cout<<'\n';
	return 0;
}
