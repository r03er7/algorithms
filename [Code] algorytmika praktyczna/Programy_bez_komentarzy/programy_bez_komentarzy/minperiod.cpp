#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef long long LL;

#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second
int MinPeriod(const char* s) {
    int p[strlen(s--)+1],k=0,q;
    p[1]=0;
    for(q=2;s[q];q++) {
	while(k>0 && s[k+1] != s[q]) k=p[k]; 
	if(s[k+1] == s[q]) k++;
	p[q]=k;
    }
    return q-p[q-1]-1;
}
int main() { 
	string text;
	while(cin >> text) {
		cout << "MinPeriod(" << text << ") = " << "(" << 
			text.substr(0,MinPeriod(text.c_str())) << ")" << endl;
	}
	return 0;
}
