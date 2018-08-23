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
bool cycEq(const char *s1, const char *s2) {
    int n=strlen(s1),i=0,j=0,k=0;
    if (n!=strlen(s2)) return 0;
    while (i<n && j<n && k<n) {
		k=1;
		while(k<=n && s1[(i+k)%n] == s2[(j+k)%n]) k++;
		if (k<=n)
			if (s1[(i+k)%n] > s2[(j+k)%n]) i+=k; else j+=k;
    }
    return k>n;
}
int main() { 
	int n;
	cin >> n;
	vector<string> text(n);
	REP(x,n) cin >> text[x];
	REP(x, n) REP(y, x)
		cout << "Slowa " << text[x] << " i " << text[y] << 
			(cycEq(text[x].c_str(), text[y].c_str()) ? "" : " nie") << 
			" sa rownowazne cyklicznie" << endl;
	return 0;
}
