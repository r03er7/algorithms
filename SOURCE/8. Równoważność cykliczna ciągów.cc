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
int n=5,R;
int u[MAXN];
int v[MAXN];
int najd_prawy[MAXN];
int pozycja[MAXN];

bool  Rownowaznosc_Cykliczna() {
    int i=-1,j=-1,k;
    while(1) {
        if((i>n-1)||(j>n-1)) return 0;
        k=1;
        while(u[(i+k)%n]=v[(j+k)%n]&&k<=n)++k;
        if(k>n)return 1;
        if(u[(i+k)%n]>v[(j+k)%n])i+=k;
        else j+=k;
    }
}
int main() {
    Rownowaznosc_Cykliczna();
    return 0;
}
