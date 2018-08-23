#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <queue>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
#define MP make_pair
#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define FORD(v,p,k) for(int v=p;v>=k;--v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define SIZE(x) (int)x.size()
#define ALL(c) c.begin(),c.end()
const int INF = 1000000001;
const int MaxK=20;
const int MaxN=20000;
const int M=16;
//__builtin_ctz  -  podaje numer najm³odszego zapalonego bitu (skrót od count trailing zeros)
//__builtin_clz  -  podaje iloœæ zer wiod¹cych, co po odjêciu od d³ugoœci reprezentacji (32 lub 64 bity), daje nam pozycjê najstarszego zapalonego bitu (skrót od count leading zeros)
//__builtin_popcount  -  podaje iloœæ zapalonych bitów liczby, moc zbiotu
//REP(0,2^n-1) iteracja po maskach zbiotu n elementowego
int load[2*M];

void insert(int x, int v)
{
while(x < M)
{
load[x] += v;
x+=((x^(x-1))+1)/2;
}
}
int sum(int x)
{
int res = 0;
while(x > 0)
{
res += load[x];
x-=((x^(x-1))+1)/2;
}
return res;
}
int query(int a, int b)
{
return sum(b) - sum(a-1);
}
int main()
{REP(x,2*M)load[x]=0;
insert(0,1);
REP(x,2*M)cout<<load[x]<<"  "<<x<<endl;
return 0;
}
