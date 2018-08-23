#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <windows.h>
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
struct Graph
{
    struct Ed
    {
        int v;
        int rev;//wzkaŸnik w neskierowanym grafie
        Ed(int w) :  v(w) {}
    };
    struct Ve :vector<Ed>
    {
        int s,t;

    };
    vector<Ve> g;
    Graph(int n=0) : g(n) {}

    void EdgeU(int b, int e)
    {
        Ed eg(e);
        eg.rev=SIZE(g[e])+(b==e);
        g[b].PB(eg);
        eg.rev=SIZE(g[eg.v=b])-1;
        g[e].PB(eg);
    }
    void Bfs(int s)
    {

        FOREACH(it, g) it->t=it->s=-1;
        g[s].t=0;
        int qu[SIZE(g)],b,e;
        qu[b=e=0]=s;
        while(b<=e)
        {
            s=qu[b++];
            FOREACH(it, g[s]) if (g[it->v].t==-1)
            {
                g[qu[++e]=it->v].t=g[s].t+1;
                g[it->v].s=s;
            }
        }
    }
    void Write()
    {
        REP(x,SIZE(g))
        {
            cout<<x<<" : ";
            FOREACH(it,g[x])cout<<" "<<it->v;
            cout<<endl;
        }


    }
    void EdgeD(int b,int e)
    {
        g[b].PB(Ed(e));

    }

 void DEdgeD(int b,int e)
    {
        FOREACH(it,g[b]){
        if ((it->v)==e){
            //g[it->v].v=g[b].back());
            swap(it,g[b].back());
       g[b].erase(it);
            }
        }
    }
};
int main()
{
   /* int n, m, s, b, e;
    cin >> n >> m;
    Graph g(n);
    REP(x,m)
    {
        cin >> b >> e;
        g.EdgeU(b, e);
    }
    g.Write();
    //g.Bfs(s);
    g.DEdgeD(1,2);
    g.Write();
    REP(x, n) cout << "Wierzcholek " << x << ": czas = " << g.g[x].t <<
                   ", ojciec w lesie BFS = " << g.g[x].s << endl;*/
                   int a=1<<31-1;

                   unsigned b=30000000000;
                   cout<<a<<" "<<b;
                string strKomunikat="przyk³adowy";
                   MessageBox(NULL,strKomunikat.c_str(),"Komunikat",MB_OK);

    return 0;
}
