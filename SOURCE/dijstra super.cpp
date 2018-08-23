#include<iostream>
#include<vector>
#include<set>
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

int const INF = 1000000000; // uwaga na limit

int n,m;
vector< pair<int,int> > adj[100000];
vector<int> waga;
vector<int> distree;
struct cmp
{
    // czy a jest mniejsze od b
    bool operator() (const int &a, const int &b)
    {
        if (waga[a] < waga[b]) return true;
        if (waga[a] > waga[b]) return false;
        return a<b;
    }
};
set<int, cmp> kopiec; // ;-)
void dijkstra(int s)
{
    int v, u, c;
    waga.clear(); // kasuje wektor
    waga.resize(n, INF); //
    distree.resize(n,-1);
    waga[s] = 0;
    kopiec.clear();
    REP(i,n) kopiec.insert(i);
    while( !kopiec.empty() )
    {
        u = *(kopiec.begin());
        kopiec.erase(kopiec.begin());

        REP(i,SIZE(adj[u]))
        {
            v = adj[u][i].first;
            c = adj[u][i].second;
            if (waga[u]+c < waga[v])
            {
                // uaktualniamy wagê wierzcho³ka v
                kopiec.erase(kopiec.find(v));
                waga[v] = waga[u]+c;
                kopiec.insert(v);
                distree[v]=u;
            }
        }
    }


}
void buildG(){
cin >> n >> m;
   REP(i,m)
    {int a,b,c;
        cin >> a >> b >> c; // c = koszt krawêdzi od a do b
        adj[a].push_back( pair<int,int>(b,c) );
    }

}
int main(void)
{
    int s,t;
    buildG();
cin >> s >> t;
    dijkstra(s);
    cout << waga[t]<<endl;
    REP(i,n)cout<<distree[i]<<" ";
    return 0;
}
