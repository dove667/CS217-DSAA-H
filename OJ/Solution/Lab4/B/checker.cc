#include "testlib.h"

#include <queue>
#include <vector>

using namespace std;
vector<pair<string,int> > inv,ouv;
priority_queue<int,vector<int>,greater<int> > q;

bool isValidOperation(vector<pair<string,int> > &vec, string &command, int ff) {
    if (command == "insert") {
        int x = ff ? ouf.readInt(-1e9,1e9) : inf.readInt(-1e9,1e9);
        vec.push_back(make_pair(command,x));
        return true;
    } else if (command == "getMin") {
        int x = ff ? ouf.readInt(-1e9,1e9) : inf.readInt(-1e9,1e9);
		vec.push_back(make_pair(command,x));
        return true;
    } else if (command == "removeMin") {
    	vec.push_back(make_pair(command,-1));
        return true;
    } else {
        return false;
    }
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(1,1e5);
    int m = ouf.readInt(1,1e6);
    int res = ans.readInt(1,1e6);
    
    if (m!=res){
    	quitf(_wa, "answer is not correct.");
	}
    
    if (m < n) {
        quitf(_fail, "ouf has fewer lines than inf.");
    }
	
    for (int i = 0; i < n; ++i) {
        string s = inf.readToken();
        if (!isValidOperation(inv, s, 0)) {
            quitf(_fail, "Invalid operation in inf: %s.", inv[i].first.c_str());
        }
    }
    for (int i = 0; i < m; ++i) {
        string s = ouf.readToken();
        if (!isValidOperation(ouv, s, 1)) {
            quitf(_wa, "Invalid operation in ouf: %s.", ouv[i].first.c_str());
        }
    }
    int idx = 0;
    
    for (int i = 0; i < m; ++i) {
        if (idx < n && ouv[i] == inv[idx]) {
            idx++;
        }
    }
    if (idx != n) {
        quitf(_wa, "inf is not a subsequence of ouf.");
    }
    
    for(pair<string, int> t:ouv){
    	string s=t.first;
    	int x=t.second;
    	if(s=="insert"){
    		q.push(x); 
		}
		if(s=="getMin"){
			while(q.size()&&q.top()>x)q.pop();
			quitif(!q.size()||q.top()!=x,_wa,"Invalid getMin operation.");
		}
		if(s=="removeMin"){
			quitif(!q.size(),_wa,"Invalid removeMin operation.");
			q.pop();
		}
	}
    
    quitf(_ok,"Correct.");
}
