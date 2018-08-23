#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef vector<int> VI;
typedef long long LL;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) __typeof(n) v = (n)
#define VAL(i,v) __typeof(v) i=(v)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
#define MAXN 1505
#define M 200005
int n=5;
int A[MAXN];
int najd_prawy[MAXN];
int pozycja[MAXN];

void Najdalszy_Prawy_Mniejszy_Sasiad() {
    int min=1;
    FOR(i,1,n) {
        pozycja[A[i]]=i;
        while(min<=n&&pozycja[min]!=0) {
            najd_prawy[pozycja[min]]=i;
            ++min;
        }
    }
}
int main() {
    Najdalszy_Prawy_Mniejszy_Sasiad();
    return 0;
}
