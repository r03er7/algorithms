#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

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

template<class V, class E> struct Graph {
     struct Ed : E {
          int v;
          Ed(E p, int w) : E(p), v(w) {}
     };
     struct Ve : V,vector<Ed> {};
     vector<Ve> g;
     Graph(int n=0) : g(n) {}
     void EdgeU(int b, int e, E d = E()) {
          Ed eg(d,e);
          eg.rev=SIZE(g[e])+(b==e);
          g[b].PB(eg);
          eg.rev=SIZE(g[eg.v=b])-1;
          g[e].PB(eg);
     }
     void Dfs(int e = -1) {
          VI st(SIZE(g));
          int t = -1 , i = 0, b = 0;
          e==-1 ? e=SIZE(g)-1 : b = e;
          REP(x,SIZE(g)) g[x].d = g[x].f = g[x].s = -1;

          FOR(s,b,e) if(g[s].d == -1) {

               g[st[i++] = s].d = ++t;
               g[s].f = SIZE(g[s]);

               while(i) {
                    int s = st[i-1];

                    if (!g[s].f) {
                         g[s].f = ++t;
                         --i;
                    } else {

                         if (g[s = g[s][--g[s].f].v].d == -1) {

                              g[s].s = st[i-1];
                              g[s].f = SIZE(g[s]);

                              g[st[i++] = s].d = ++t;
                         }
                    }
               }
          }
     }
     void EdgeD(int b,int e,E d=E()) {
          g[b].PB(Ed(d,e));
     }

///////do cyklów fundamentalnych
     int num,d;
     int *STOS;
     vector<vector<int> > WYNIK;
     void CYKLE(int v) {
          STOS[++d]=v;
          ++num;
          g[v].s=num;
          FOREACH(it,g[v]) {
               int u = it->v;

               if(g[u].s==-1) CYKLE(u);
               else if(u!=STOS[d-1]&& g[v].s>g[u].s ) {

                    VI cykl;
                    int i=d;
                    for(;;) {

                         cykl.PB(STOS[i]);
                         if(STOS[i]==u)break;
                         --i;
                    }
                    WYNIK.PB(cykl);

               }
          }
          --d;
     }
     bool CYKLE_ELEMENTARNE() {
          int n=SIZE(g);
          WYNIK;
          WYNIK.clear();
          REP(v,n) g[v].s=-1;
          num=0;
          STOS=new int[n+1];
          STOS[0]=-1;
          d=0;

          REP(v,n)
          if(g[v].s==-1) CYKLE(v);

          return SIZE(WYNIK);
     }
     void CWRITE() {

          if(CYKLE_ELEMENTARNE()) {

               cout<<"cykle elementarne \n";
               FOREACH(it1,WYNIK) {
                    FOREACH(it2,*it1)  cout<<*it2<< "  ";
                    cout<<"\n";
               }
          }




     }
};
struct Ve {
     int rev;
};
struct Vs {
     int s;

};


int main()
{
     int n, m, b, e;
     cin >> n >> m ;
     Graph<Vs, Ve> g(n);
     REP(x,m) {
          cin >> b >> e;
          g.EdgeU(b, e);
     }
     g.CWRITE();
     return 0;
}
