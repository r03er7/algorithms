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
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v, n) __typeof(n) v = (n)
#define VAL(i,v) __typeof(v) i=(v)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
const int INF = 1000000000;
const LL INFLL = LL(INF) * LL(INF);
template<class T> inline int size(const T&c)
{
    return c.size();
}
template<class T> T parse(string s)
{
    istringstream i(s);
    T x;
    i>>x;
    return x;
}
template<class T> string show(T x)
{
    ostringstream o;
    o<<x;
    return o.str();
}
VS split(string s, string del=" ")
{
    string w;
    VS res;
    s += del[0];
    FOREACH(it,s)
    {
        if(find(ALL(del),*it)==del.end()) w += *it;
        else if (w!="")
        {
            res.push_back(w);
            w="";
        }
    }
    return res;
}
VI s2vi(string s, string del=" ")
{
    VS v = split(s,del);
    VI res;
    FOREACH(it,v) res.push_back(parse<int>(*it));
    return res;
}
string mergeStrings(VS v)
{
    string s;
    FOREACH(it,v) s += *it;
    return s;
}
#define debug(x) cerr << #x << " = " << x << "\n";
#define debugv(x) cerr << #x << " = "; FOREACH(it,(x)) cerr << *it << ","; cerr << "\n";
#define MAXN 1000000
int a[MAXN];
int n,k;
void read_file()
{
    FILE *plik=fopen("mon8b.in","r");
    fscanf(plik,"%d%d",&n,&k);
    char c;
    fscanf(plik,"%c",&c);
    REP(i,n)
    {
        fscanf(plik,"%c",&c);
        a[i]=c%2;
    }
    //REP(i,n)debug(a[i]);
}
void read()
{
    scanf("%d%d",&n,&k);
    char c;
    scanf("%c",&c);
    REP(i,n)
    {
        scanf("%c",&c);
        a[i]=c%2;
    }
}
void solution()
{
    LL ss=0;
    map<LL,int>m;//mapa indeksow
    m[ss]=-1;
    int res=0;
    REP(i,n)
    {
        if(a[i])--ss;//orzel
        else ss+=k;//reszka
        int size=SIZE(m);
        if((m[ss]==0)||(size!=SIZE(m)))m[ss]=i;
        else res=max(res,i-m[ss]);
    }
    printf("%d\n",res);
}
int t[MAXN];
void solution_hash()
{
    LL ss=0;
    t[ss]=-1;
    int res=0;
    REP(i,n+1)
    {
        if(a[i])--ss;//orzel
        else ss+=k;//reszka
        if(!t[ss%n])t[ss%n]=i;
        else res=max(res,i-t[ss%n]);
    }
    printf("%d",res);
}
int main()
{
    //read_file();
    read();
    solution();
    //map<int,int> cotam;
    //printf("\n%d",SIZE(cotam));
    //cotam[0];
    //printf("\n%d",SIZE(cotam));
    //solution_hash();
    return 0;
}
