#include <iostream>
#include <queue>
#include <string>
using namespace std;
const int N=1e6+10;
struct node
{
	string c;
	int x;
}a[N];
priority_queue<int> q;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,len=0;
	cin>>n;
	while(n--)
	{
		string s;
		int x;
		cin>>s;
		if(s=="insert")
		{
			cin>>x;
			q.push(-x);
			a[++len].c=s,a[len].x=x;
		}
		else if(s=="removeMin")
		{
			if(q.empty())
			{
				q.push({1000000000});
				a[++len].c="insert",a[len].x=-1000000000;
			}
			a[++len].c="removeMin";
			q.pop();
		}
		else
		{
			cin>>x;
			int flag=0;
			while(!q.empty())
			{
				if((0-q.top())==x) 
				{
					flag=1;
					break;
				}
				if((0-q.top())>x)
				{
					q.push(-x);
					a[++len].c="insert",a[len].x=x;
					flag=1;
					break;
				}
				q.pop();
				a[++len].c="removeMin";
			}
			if(flag==0)
			{
				q.push(-x);
				a[++len].c="insert",a[len].x=x;
			}
			a[++len].c="getMin",a[len].x=x;
		}
	}
	cout<<len<<'\n';
	for(int i=1;i<=len;i++)
	{
		if(a[i].c=="removeMin") cout<<a[i].c<<'\n';
		else cout<<a[i].c<<" "<<a[i].x<<'\n';
	}
	return 0;
}
