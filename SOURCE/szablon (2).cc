#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define VAR(v, n) __typeof(n) v = (n)
#define VAL(i,v) __typeof(v) i=(v)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define debug(x) cerr << #x << " = " << x << "\n";
#define debugv(x) cerr << #x << " = "; FOREACH(it,(x)) cerr << *it << ","; cerr << "\n";
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
#define MAXN 1505
#define M 200005
typedef long long LL;
typedef long double ld;
typedef vector<int> VI;
typedef vector<string> VS;
const int INF = 1000000000;
const LL INFLL = LL(INF) * LL(INF);
template<class T> inline int size(const T&c) {
    return c.size();
}
typedef long double LD;
const LD EPS=1E-9;
inline bool IsZero(LD x) {
    return x>=-EPS&&x<=EPS;
}
//IsZero(a-b)zamiast a==b
struct POINT {
    LD x,y;
    POINT(LD wx=0,LD wy=0):x(wx),y(wy) {}
};
inline LD skal(POINT &a,POINT &b,POINT &c) { //referencje szybciej nie ma kopowania
    return (b.x-a.x)*(c.x-a.x)+(b.y-a.y)*(c.y-a.y);
}
inline LD dist(POINT &a,POINT &b) {
    return sqrtl(skal(a,b,b));
}
inline LD dlrzutu(POINT &a,POINT &b,POINT &c) { //ze znakiem
    return skal(a,b,c)/dist(a,b);
}
inline POINT rzut(POINT &a,POINT &b,POINT &c) {
    LD f=skal(a,b,c)/skal(a,b,b);
    return POINT(a.x+f*(b.x-a.x),a.y+f*(b.y-a.y));
}
inline LD det(POINT &a,POINT &b,POINT &c) { //referencje szybciej nie ma kopowania
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
inline LD sgn (LD x) {
    return x<-EPS?-1:(x>EPS?1:0);
}
inline LD strona_lewa(POINT &a,POINT &b,POINT &c) { //referencje szybciej nie ma kopowania
    return sgn(det(a,b,c));
}
inline LD pole(POINT &a,POINT &b,POINT &c) { //referencje szybciej nie ma kopowania
    return fabsl(det(a,b,c))/2;
}
inline LD dist_pupr(POINT &a,POINT &b,POINT &c) { //referencje szybciej nie ma kopowania
    return fabsl(det(a,b,c))/dist(a,b);
}
inline LD f(POINT &a,POINT &b,POINT &c) { //referencje szybciej nie ma kopowania
    if(skal(a,b,c)>0&&skal(b,a,c)>0)
        return dist_pupr(a,b,c);
    return min(dist(a,c),dist(b,c));
}
inline POINT symsr(POINT &s,POINT &a) {
    return  POINT(2*s.x-a.x,2*s.y-a.y);
}
int main() {
    VI perm;
    int n=4;
    int xx=1;
    FOR(i,1,n)xx*=i;
    REP(i,n)perm.PB(i);
   // perm[0]=0;
   // perm[1]=0;
   // perm[3]=1;
   // perm[2]=1;
    FOREACH(it,perm)printf("%d ",*it);
    REP(j,xx+1) {
        printf("\n%d\t",j);
        FOREACH(it,perm)printf("%d ",*it);
        next_permutation(perm.begin(),perm.end());
    }
    return 0;
}
