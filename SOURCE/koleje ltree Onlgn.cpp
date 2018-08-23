#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <stdio.h>
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
const int MX=100000;
inline int RI()
{
     int x;
     scanf("%d",&x);
     return x;
}
const int MAX  = 	100100;		/* wielkosc tablic do trzymania danych */
//const int M   =	132000;		/* offset drzewa licznikowego */
int M=1;
const int minf =-1;
int n;					/* n z zadania */
vector<int> A;
vector<int> L;
vector<int> R;
vector<short int> colors;
vector<int> w;
vector<vector<int> > listeners;//[2*M];
vector<vector<int> > vertex;//[MX];
vector<vector<int> > indexer;//[MX];
vector<int> wysokosc;
inline void addlistener(int v,int i)
{
     listeners[v].PB(A[i]);
     vertex[i].PB(v);
     indexer[i].PB(++wysokosc[v]);
}
inline void addToBucket(int a)
{

     int left=a+M-1;//-1;
     int right=L[a]+M+1;//+1;
     /* aktualizacja maksimum */
     int va = M + a;
     w[va]= A[a];
     va>>=1;
     while (va>0) {
          w[va]= max(w[va<<1],w[(va<<1)+1]);
          va>>=1;
     }

     /* dodawanie listenerow */
     /*
if(left<right){addlistener(right-1,a);//try and error
     while ((left>>1) != (right>>1)) {
          if (!(left&1))
               addlistener(left^1,a);
          if (right&1)
               addlistener(right^1,a);
          left>>=1;
          right>>=1;
     }

}*/

   /* Spacer a¿ do momentu spotkania. */
   if(left<=right){addlistener(right-1,a);
   while (left / 2 != right / 2) {
     if (left % 2 == 0) addlistener(left + 1,a); /* prawa bombka na lewej œcie¿ce */
     if (right % 2 == 1) addlistener(right - 1,a); /* lewa bombka na prawej œcie¿ce */
     left /= 2; right /= 2;
   }


}
}
/* usuwa wartosc A[k] z kubelka o numerze k */
/* aktualizuje maksimum i usuwa listenerow */
inline void deleteFromBucket(int k)
{
     /* aktualizacja maksimum */
     int va = M + k;
     w[va]= -1;
     va /= 2;
     while (va >= 1) {
          w[va]=max(w[2*va],w[2*va+1]);
          va /= 2;
     }
     /* usuwanie listenerow z wezlow */
     REP(x,SIZE(vertex[k])) {
          listeners[vertex[k][x]][indexer[k][x]]=-1;
     }
     vertex[k].clear();
     indexer[k].clear();
}
/* zwraca dowolna krawedz z k do przodu jako element do ktorego prowadzi lub minf, jesli nie ma */
int getForwardEdge(int k)
{
     int left=k+M-1;//-1;//goof
     int right=L[k]+M+1;//+1;
if(left<right)
     while ((left>>1) != (right>>1)) {
          if ((!(left&1)) && (w[left^1]>A[k]))
               return R[w[left^1]];
          if (((right&1)) && (w[right^1]>A[k]))
               return R[w[right^1]];
          left>>=1;
          right>>=1;
     }
     return -1;
}

/* zwraca dowolna krawedz z k do tylu jako element do ktorego prowadzi lub minf, jesli nie ma */
int getBackwardEdge(int k)
{
     int va=k+M;
     while (va>0) {
          if((wysokosc[va]>-1)) {
               while((listeners[va][wysokosc[va]]<0)&&((wysokosc[va]+1)<SIZE(listeners[va])))
                    ++wysokosc[va];
               if (listeners[va][wysokosc[va]]>-1) {
                    if(listeners[va][wysokosc[va]]<A[k]) {
                         return R[listeners[va][wysokosc[va]]];
                    }
               } else {
                    wysokosc[va]=-1;//zwalanianie pamieci
                    listeners[va].clear();
               }
          }
          va>>=1;
     }

     return -1;
}

void BuildA()
{
     scanf("%d",&n);
     while(M<n)M<<=1;
     A.resize(n);
     L.resize(n);
     R.resize(n,-1);
     colors.resize(n,-1);
     w.resize(2*M,-1);
     listeners.resize(2*M);
     vertex.resize(2*M);
     indexer.resize(2*M);
     wysokosc.resize(2*M,-1);
     REP(x,n) {
          scanf("%d",&A[x]);
          --A[x];
     }
}
void BuildL()
{
     //REP(x,n)R[x]=-1;
     int next=0;
     REP(i,n) {
          R[A[i]]=i;
          while((next<n)&&(R[next]!=-1)) {
               L[R[next]]=i;
               ++next;
          }
     }

}

/* buduje drzewo licznikowe */
inline void buildTree()
{
    // REP(t,n) colors[t]=-1;
    // REP(t,2*M) {
    //      wysokosc[t]=-1;
     //     w[t]=-1;
    // }
     REP(i,n)addToBucket(R[i]);
}

/* dfs kolorujacy */
void dfs(int v, int c)
{
     colors[v]=c;
     deleteFromBucket(v);
     int e;
     while ((e=getForwardEdge(v))>=0)
          dfs(e,c^1);
     while ((e=getBackwardEdge(v))>=0)
          dfs(e,c^1);
}

/* buduje przykladowe rozwiazanie */
inline void buildSolution()
{
     REP(t,n) if (colors[t]<0) dfs(t,0);
}

/* ========================== sprawdzanie rozwiazania ==================== */

int c=0;		/* jaki jest kolejny element do zdjecia */
stack<int> st[2];	/* stosy do zdejmowania */

/* zdejmuje ze stosow tyle, ile mozna */
void flush()
{
     int flag;
     for(;;) {
          flag = 1;
          REP(t,2) if (st[t].top()==c) {
               c++;
               st[t].pop();
               flag = 0;
          }
          if (flag) break;
     }
}

/* sprawdza, czy zbudowane rozwiazanie jest poprawne */
bool checkSolution()
{
     REP(i,2) st[i].push(n+2);
     REP(i,n) {
          st[colors[i]].push(A[i]);
          flush();
     }
     return (c>=n);
}

/* buduje i wypisuje odpowiedz na wyjscie */
inline void buildAnswer()
{
     if (checkSolution()) {
          printf("TAK\n");
          REP(i,n) printf("%s%d",(i)?" ":"",colors[i]+1);
          printf("\n");
     } else
          printf("NIE\n");
}

int main()
{
     BuildA();
     BuildL();
     buildTree();
     buildSolution();
     buildAnswer();


     return 0;
}
