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
#include <map>
#include <stack>
#include <queue>
#include <bitset>
#include <iterator>
#include <set>
#include <cstring>//clr
#include <complex>
#include <list>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v, n) __typeof(n) v = (n)
#define VAL(i,v) VAR(v,n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define CLR(A,v) memset((A),v,sizeof((A)))
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
//ios_base::sync_with_stdio(0);
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PI;
const int INF = 1000000000;
const LL INFLL = LL(INF) * LL(INF);

template<class T> inline int size(const T&c) {
    return c.size();
}
int foo()
{
     static int r;
     ++r;
     return r;
}
int** mnozenie(int**a,int**b,int n)
{
     int**c=new int*[n];
     REP(i,n)c[i]=new int[n];
     REP(i,n)REP(j,n)c[i][j]=0;
     REP(i,n)REP(k,n)REP(j,n) c[i][j]+=(a[i][k]+b[k][j]);
     return c;
}
int** potegowanie(int**A,int n,int r)
{
     int**W=new int*[n];
     REP(i,n)W[i]=new int[n];
     REP(i,n)REP(j,n)W[i][j]=0;
     while(r) {
          if(r%2)W=mnozenie(A,W,n);
          A=mnozenie(A,A,n);
          r/=2;
     }
     return W;
}
void write(int**A,int n)
{

     REP(i,n)REP(j,n) {
          cout<<A[i][j]<<" ";
          if((j+1)%n==0)cout<<"\n";
     }


}
int main()
{
     int n;
     cin>>n;
     int**A=new int*[n];
     int**B=new int*[n];
     REP(i,n) {
          A[i]=new int[n];
          B[i]=new int[n];
     }

     REP(i,n)REP(j,n)cin>>A[i][j];

     write(A,n);
     int r;
     write(mnozenie(A,A,n),n);

     return 0;
}
