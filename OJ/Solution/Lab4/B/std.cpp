#include <iostream>
#include <queue>
#include <string>
using namespace std;
int c,i,n,k,b[400004],m;
string t,a[400004];
priority_queue<int,vector<int>,greater<int> > s;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for(i=0;i<n;i++){
		cin>>t;
		if(t[0]=='i')cin>>c,a[k]=t,b[k++]=c,s.push(c),m++;
		else if(t[0]=='r'){
			if(m==0)a[k]="insert",b[k++]=1,s.push(1),m++;
			a[k++]=t,s.pop(),m--;
		}
		else{
			cin>>c;
			while(s.size()&&s.top()<c&&m>0)
				a[k++]="removeMin",s.pop(),m--;
			if(m==0||s.top()>c)a[k]="insert",b[k++]=c,s.push(c),m++;
			a[k]=t,b[k++]=c;
		}
	}
	cout<<k<<'\n';
	return 0;
}
