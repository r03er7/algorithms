#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <stack>
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
vector<vector<int> > krawedzie;
vector<int> spojne, przetwarzane, liczniki;
int n,m,ile;
//FU spojne przetwarzane
int find(int a)
{
     if (spojne[a] < 0)
          return a;
     else
          return spojne[a] = find(spojne[a]);
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
void buildG()
{
    // scanf("%d %d",&n,&m);
     n=6;m==4;
     int krak[]={0,1,1,3,0,3,2,4};
     krawedzie.resize(n);
     REP(i,m) {
          int a,b;
          //scanf("%d %d",&a, &b);
          //--a;
         // --b;
         a=krak[m];
         b=krak[++m];
          krawedzie[a].push_back(b);
          krawedzie[b].push_back(a);
     }
}
void buildSS()
{
     spojne.resize(n);//moc spojnej
     przetwarzane.resize(n);//spojen
     liczniki.resize(n);//ai
     ile = n;//liczba spojnych
     REP(i,n) {
          spojne[i] = -1;//na starcie moc 1
          przetwarzane[i] = i;
     }

     REP(i,n) {//dla karzdego wierzcholka

          REP(j,ile)liczniki[przetwarzane[j]]=0;//zerowanie licznika
          FOREACH(it,krawedzie[i]) ++liczniki[find(*it)]; //find znajduje SJ do ktorego nalerzy u


          REP(j,ile) {
               if (liczniki[przetwarzane[j]] != -spojne[przetwarzane[j]])//istnieje wierzcho³ek do ktorego nei dochodzi krawde z i w G
                    unin(i,przetwarzane[j]);//spujen[j] przestawione na peprezentanta
          }


          for(int j=0; j<ile;) {
               if (spojne[przetwarzane[j]] < 0)
                    ++j;
               else {
                    przetwarzane[j] = przetwarzane[--ile];


               }
          }
     }
}
void buiildAns()
{
     for(int i=0; i< ile; ++i)
          liczniki[i]=-spojne[przetwarzane[i]];
     sort(liczniki.begin(), liczniki.begin()+ile);

     printf("%d\n",ile);
     for(int i=0; i<ile; ++i)
          printf("%d ",liczniki[i]);
     printf("\n");
}

int main()
{
     buildG();
     buildSS();
     buiildAns();
}
