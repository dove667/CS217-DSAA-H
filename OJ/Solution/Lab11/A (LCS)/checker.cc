#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;

string a,b,s,t;
int buc[30];

void check(const string &a){
	int j=0;
    for(int i=0;i<(int)a.size();i++)
    	if(a[i]==t[j])j++;
    
    quitif(j!=(int)t.size(), _wa, "The participant's answer is not a subsequence.");
}

bool same(const string &a,const string &b){
	for(char c:a)buc[c-'a']=1;
	for(char c:b)if(buc[c-'a'])return 1;
	return 0;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
	
	a=inf.readString();
	b=inf.readString();
	
	if(!same(a,b)){
		ans.readEoln();
		ouf.readEoln();
		quitf(_ok,"Correct.");
	}
	
	s=ans.readToken();
	t=ouf.readToken();
	
	for(char c:s)
		quitif(c<'a'||c>'z', _fail, "Wrong characters in jury's string.");
	
	for(char c:t)
		quitif(c<'a'||c>'z', _wa, "Wrong characters in participant's string.");
	
	quitif(s.size()!=t.size(), _wa, "The length of the string are not the same.");
    
	check(a);
	check(b);
    
    quitf(_ok,"Correct.");
}
