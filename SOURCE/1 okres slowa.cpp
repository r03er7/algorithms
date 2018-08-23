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
#define MAXN 1500
int P[MAXN];//prefikso sufiksy
int n,k;
int s[MAXN];
int w[MAXN];
void pref_suf() {
    P[1]=0;
    int t=P[1];
    FOR(i,2,n+k) { //nzm:t=P[i-1];
        while (t>0&&w[t+1]!=w[i])t=P[t];
        if(w[t+1]==w[i])++t;
        P[i]=t;
    }
}
int main() {

    s= {3,4,5,1,2,3,1,2,3,-1}; //słowo
    w= {7,1}; //wzorzec
    n=10;//dlugość slowa
    k=1;//dlugosc wzorca
//wyznaczenie prefiksowej dla slowa w#s
    w[k+1]=-1;
    REP(i,n)w[k+1+i]=s[i];
    printf("%d ",n);
    printf("%d ",k);
    printf("\n");

    REP(i,(n+k+1))printf("%d ",w[i]);
    pref_suf();
    printf("\n");

    REP(i,(n+k+1))printf("%d ",P[i]);
    return 0;

}
