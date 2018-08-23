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
void NumPart(int n, void (*fun)(VI&, VI&, int)) {
    VI S(n+1), R(n+1);
    int d,sum,l;
    S[0]=n;
    R[0]=d=1;
    while(1) {
		int summ=0,x,s;
		fun(R, S, d);
		if (S[0]==1) break;
		sum=0;
		if(S[d-1]==1) sum+=R[--d];
		sum+=S[d-1];
		R[d-1]--;
		l=S[d-1]-1;
		if(R[d-1]) d++;
		S[d-1]=l;
		R[d-1]=sum/l;
		l=sum%l;
		if(l) {
			S[d]=l; 
			R[d++]=1;
		}
	}
}
void Display(VI& s, VI& r, int n) {
	bool ch=0;
	REP(x, n) REP(y, s[x]) {
		if (ch) cout << " + ";
		cout << r[x];
		ch = 1;
	}
	cout << endl;
}

int main() {
	NumPart(5, &Display);
	return 0;
}
