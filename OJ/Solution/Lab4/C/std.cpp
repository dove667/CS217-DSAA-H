#include<iostream>
#include<algorithm>
using namespace std;
const int N=200010,M=2000010,INF=0x3f3f3f3f;
int n,num,a[N],b[N],heap[N<<2]={INF};
void up(int p){
	while(heap[p]>heap[p>>1])
		swap(heap[p],heap[p>>1]),p>>=1;
}
void down(int p){
	int s=p<<1;
	while(s<=num){
		if(s<num&&heap[s]<heap[s+1])s++;
		if(heap[p]<heap[s])
			swap(heap[p],heap[s]),p=s,s=p<<1;
		else break;
	}
}
void ins(int x){heap[++num]=x,up(num);}
void pop(){swap(heap[1],heap[num--]),down(1);}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n,num=n;
	for(int i=1;i<=n;i++)cin>>heap[i];
	for(int i=n/2;i>=1;i--)down(i);
	for(int i=1;i<=n;i++)pop();
	for(int i=1;i<=n;i++)cout<<heap[i]<<' ';
	return 0;
}
