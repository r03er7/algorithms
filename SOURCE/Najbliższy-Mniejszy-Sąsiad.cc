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
int lewy[MAXN];

int Najblizszy_Mniejszy_Sasiad(int x) {
    FOR(i,1n) {
        j=i-1;
        while(A[j]>=A[i])j=lewy[j];
        lewy[i]=j;
    }
}
int main() {
    Najblizszy_Mniejszy_Sasiad(1);
    return 0;
}
