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
int B[MAXN];
bool Szukanie_Sumy(int x) {
   int i,j=n;
   while(i<=n&&j>0){
   if(A[i]+B[j]==x)return true;
   else if(A[i]+B[j]<x)++i;
   else j-=1;
   }
   return false;
}
int main() {
Szukanie_Sumy(1);
    return 0;
}
