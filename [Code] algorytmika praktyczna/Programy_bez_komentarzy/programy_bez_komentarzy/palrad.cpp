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
VI PalRad(const char *x, bool p) 
{
	int n = strlen(x), i = 1, j = 0, k;
	VI r(n, 0);
	while(i < n) {
		while(i + j + p < n && i > j && x[i - j - 1] == x[ i + j + p]) j++;
		for(r[i] = j, k = 0; ++k <= j && r[i - k] != j - k;) 
			r[i + k] = min(r[i - k], j - k);
		j = max(0, j - k);
		i += k;
	}
	return r;
}
int main() {
	string text;
	cin >> text;
	cout << "Analizowany tekst: " << text << endl;
	VI res = PalRad(text.c_str(), 0);
	cout << "Palindromy parzyste: ";
	FOREACH(it, res) cout << " " << (*it);
	cout << endl;
	res = PalRad(text.c_str(), 1);
	cout << "Palindromy nieparzyste: ";
	FOREACH(it, res) cout << " " << (*it);
	cout << endl;
	return 0;
}
