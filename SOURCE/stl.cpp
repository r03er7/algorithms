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
bool porownanie( const int & a, const int & b)
{
if (a % 2 == b % 2)
return a <= b;
else
return (a % 2 == 1);
}
void sorotowniezporownanie(int* liczby,int n){
random_shuffle(liczby,liczby+n);
sort( liczby , liczby + n,porownanie);
}
void pemutacje(){//od cigu posortowaniego do ostanie leksykograficznie permutacji
vector < int > vec ;
vec . push_back (3) ;
vec . push_back (5) ;
vec . push_back (7) ;
do
{FOREACH(it,vec)cout<<*it<<"  ";cout<<endl;
for ( int i = 0; i < vec . size (); i ++)
vec [i]; // −> ( p a t r z n i z e j )
} while ( next_permutation ( vec . begin () ,vec . end ()));

}

struct event
{
int x; /* współrzędna, na której występuje zdarzenie */
/* Typ zdarzenia: *
/* 1 - początek odcinka poziomego *
* -1 - koniec odcinka poziomego *
* 0 - odcinek pionowy */
int type;
int y1, y2; /* dolna i górna współrzędna y *
* (dla odcinków poziomych y1 = y2) */
int operator<(const event& e) const
{
if(x == e.x)
return type > e.type;
else
return x < e.x;
}
};

int w[2*MaxN];
vector<event> events(MaxN);
void init(){
REP(x,MaxN)w[x]=0;
}

inline void insert(int a, int c) {
 int va=MaxN+a;
  w[va] += c;
  while (va != 1) {
    w[va] += c;
    va /= 2;

  }
}
inline int query(int a, int b) {
  int va = MaxN + a, vb = MaxN + b;

  /* W drugim przebiegu wyznaczamy wynik na podstawie wynikow dla przedzialow
   * bazowych z rozkladu [a,b]. */
  int wynik =w[va];
  if(va!=vb)wynik+=w[vb];
  while (va / 2 != vb / 2) {
    if (va % 2 == 0) wynik +=w[va + 1];
    if (vb % 2 == 1) wynik +=w[vb - 1];
    va /= 2; vb /= 2;
  }
  return wynik;
}
// events - kontener typu vector<event> przechowujący zdarzenia
// sortujemy zdarzenia zgodnie ze zdefiniowanym porządkiem

void zamiatanie(){
sort(events.begin(), events.end());
// zmienna zliczająca znalezione przecięcia
long long inter = 0;
for(int i=0; i<(int)events.size(); i++)
{
if(events[i].type == 0) //odcinek pionowy
inter += query(events[i].y1, events[i].y2);
else
insert(events[i].y1, events[i].type);
}


}
int main()
{
    pemutacje();
return 0;
}
