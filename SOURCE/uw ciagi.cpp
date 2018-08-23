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
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
//__builtin_ctz  -  podaje numer najm³odszego zapalonego bitu (skrót od count trailing zeros)
//__builtin_clz  -  podaje iloœæ zer wiod¹cych, co po odjêciu od d³ugoœci reprezentacji (32 lub 64 bity), daje nam pozycjê najstarszego zapalonego bitu (skrót od count leading zeros)
//__builtin_popcount  -  podaje iloœæ zapalonych bitów liczby, moc zbiotu
//REP(0,2^n-1) iteracja po maskach zbiotu n elementowego

inline int RI()
{
     int x;
     scanf("%d",&x);
     return x;
}
int findfirs(int n,int x,int* A)
{
     int l,p,s;
     l=0;
     p=n-1;
     while (l < p) {
          s=(l+p)/2;
          if (x > A[s])l=s+1;
          else p=s;
     }
     if (A[l]==x)  return l;
     else return -1;
}
int findlast(int n,int x,int* A)
{
     int l,p,s;
     l=0;
     p=n-1;
     while (l < p) {
          s=(l+p+1)/2;
          if (x < A[s])p=s-1;
          else l=s;
     }
     if (A[l]==x)  return l;
     else return -1;
}
int pierwszywiekszy(int x,int l,int p,int* A)
{
     int s;
     while (l < p) {
          s=(l+p+1)/2;
          if (x < A[s])p=s-1;
          else l=s;
     }
     if (A[l]<=x)  return ++l;
     else return l;
}
int liczbawystapin(int n,int x,int* A)
{
     int p,l;
     l=findfirs(n,x,A);
     p=findlast(n,x,A);
     if (l>=0) return (p-l+1);
     else return -1;
}
int wartoscrowanindexowi(int n,int x,int* A)
{
     int p,l,s;
     l=0;
     p=n-1;
     while (l < p) {
          s=(l+p)/2;
          if (s > A[s])l=s+1;
          else p=s;
     }
     if (A[l]==l)  return l;
     else return -1;
}
int maxniemalejacy(int n,int x,int* A)
{
     int ia,ib,z;
     int* B=new int[n];
     REP(x,n)B[x]=0;
//vector<int> B(n,0);
     ia=0;
     B[ib]=A[0];
     for(ia=1; ia<n; ++ia) {
          if (A[ia] >= B[ib]) {
               ++ib;
               B[ib]=A[ia];
          } else {
               z=pierwszywiekszy(A[ia],1,ib,B);
               B[z]=A[ia];
          }
     }
     return ib;

}
  int Slider(int *a,int n){

    int lider = -1;
    REP(k,n)
    {
      /* a[k] - kandydat na lidera */
      int ile = 0;
      for (int i = 0; i < n; i++)
        if (a[i] == a[k])
          ile++;
      if (ile > n / 2)
        lider = a[k];
    }
    if (lider >= 0)
     return lider;
   else
    return -1;
  }


vector<int> spojne, przetwarzane, liczniki;
int n,m,ile;
//FU spojne przetwarzane
vector<int> patent,rank;
void Makeset(int n){
REP(x,n){
parent[x]= x;
 rank[x]=-1;
}
}
int find(int a)
{
     if (parent[a] == a)
          return a;
     else
          return parent[a] = find(parent[a]);
}
void unin(int a, int b)
{
     a = find(a);//znajduje reprezentanta a
     b = find(b);//znajduje reprezentanta b
     if (a!=b) {//ten sam reprezentant sa juz union
          if (spojne[a] > spojne[b])//jesli moc spojnej reprezentanta b jest wieksza(-1)
               swap(a,b);
          spojne[a]+=spojne[b];//sumowanie mocy
          spojne[b] = a;//0 mniejszej ilcznosci wzkazuje teraz na reprezentanta
     }
}
int main()
{

}
