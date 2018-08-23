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
int minLexCyc(const char *x) {
  int i=0,j=1,k=1,p=1,a,b,l=strlen(x);
  while(j+k <= (l<<1)) {
    if ((a=x[(i+k-1)%l])>(b=x[(j+k-1)%l])) {i=j++;k=p=1;}
    else if (a<b) {j+=k; k=1; p=j-i;}
    else if (a==b && k!=p) k++;
    else {j+=p; k=1;}
  }
  return i;
}
int main() {
	string text;
	while(cin >> text) {
		int res = minLexCyc(text.c_str());
		cout << "Minimalna rownowaznosc cykliczna " << text << 
			" = " << text.substr(res, text.length()-res) << 
			text.substr(0, res) << endl;
	}
	return 0;
}
