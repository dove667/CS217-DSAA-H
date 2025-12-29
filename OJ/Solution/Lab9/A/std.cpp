#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=1000010,INF=0x3f3f3f3f;
int T,rt,g[N],tag[N];
string s,t;
vector<int> s1,s2;
bool imply(bool a,bool b){
	return !a||b;
}
struct node{
    int l,r;
    #define l(x) tree[x].l
    #define r(x) tree[x].r
}tree[N];
void create_node(int op){
	if(s1.size())tag[s1.back()]^=op;
    if(s1.size()>=2&&s2.size()>0&&t[s2.back()]!='('){
    	int p=s2.back();
	    s2.pop_back();
        r(p)=s1.back();
        s1.pop_back();
        l(p)=s1.back();
        s1.pop_back();
        s1.pb(p);
    }
}
void build(){
    for(int i=0;i<(int)t.size();i++){
        if('0'<=t[i]&&t[i]<='1'){
            s1.pb(i);
            create_node(g[i]);
        }
        else if(t[i]==')'){
            s2.pop_back();
            create_node(g[i]);
        }
        else s2.pb(i);
    }
    rt=s1.back();
    s1.pop_back();
}
bool dfs(int p){
	if('0'<=t[p]&&t[p]<='1')return (t[p]=='1')^tag[p];
	if(t[p]=='&')return (dfs(l(p))&dfs(r(p)))^tag[p];
	if(t[p]=='|')return (dfs(l(p))|dfs(r(p)))^tag[p];
	if(t[p]=='^')return (dfs(l(p))^dfs(r(p)))^tag[p];
	return imply(dfs(l(p)),dfs(r(p)))^tag[p];
}
void solve(){
	cin>>s;
	t.clear();
	s1.clear();
	for(int i=0;i<(int)s.size();i++){
		g[i]=tag[i]=0;
		if(s[i]=='-')continue;
		if(s[i]=='!'){
			s1.pop_back(),s1.pb(1);
			continue;
		}
		t.pb(s[i]);
		if(s[i]=='(')s1.pb(0);
		if(s[i]==')'){
			g[t.size()-1]=s1.back();
			s1.pop_back();
		}
	}
    s1.clear();
    s2.clear();
    build();
    cout<<dfs(rt)<<'\n';
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)solve();
	return 0;
}
