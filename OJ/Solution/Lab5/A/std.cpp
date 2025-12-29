#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=500010,M=5000010,INF=0x3f3f3f3f;
int n,a[N];
int partition(int l,int r){
	int mid=(l+r)>>1,p=a[mid];
	int i=l-1,j=r+1;
	while(1){
		while(i<r){
			i++;
			if(a[i]>=p)break;
		}
		while(j>l){
			j--;
			if(a[j]<=p)break;
		}
		if(i>=j)return j;
		swap(a[i],a[j]);
	}
}
void qsort(int l,int r){
	if(l<0||r<0||l>=r)return;
	int mid=partition(l,r);
	qsort(l,mid);
	qsort(mid+1,r);
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	qsort(1,n);
	for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
	return 0;
}
