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
#include <bitset>
#include <iterator>
#include <set>
#include <cstring>//clr

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v, n) __typeof(n) v = (n)
#define VAL(i,v) VAR(v,n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define CLR(A,v) memset((A),v,sizeof((A)))
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
//ios_base::sync_with_stdio(0);
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PI;
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
#define MAXN 1000001

int a[MAXN];
int n,t;
void read_file()
{
    FILE *plik=fopen("mon8b.in","r");
    fscanf(plik,"%d%d",&n,&t);
    REP(i,n)fscanf(plik,"%d",&a[i]);
    ///REP(i,n)debug(a[i]);
}
void read()
{
    scanf("%d%d",&n,&t);
    REP(i,n)scanf("%d",&a[i]);
}
int solution()
{
    LL s;
    return 0;
}
void lcs()
{
    int _n=6;
    //int _n=12;
    //int A[]= {3,4,2,3,7,6,5,6,8,5,9,4};
    int A[]= {3,1,2,5,2,3};
    vector<int> v(_n,_n+1);//warstwy
    int k = 0;
    int i=0;
    REP(i,_n)printf("%d ",A[i]);
    printf("\n");
    while (_n--)
    {
        int a;
        a=A[i++];
        vector<int>::iterator end = v.begin()+k;
        vector<int>::iterator it = lower_bound(v.begin(),end,a);
        if (it==end)
            k++;
        *it = a;

        FOREACH(it,v)printf("%d ",*it);
        printf("\n");

    }
    printf("%d\n",k);
}
void plecak()
{
    const int MSIZE = 1000, PUSTO=-1;
    int plecak[MSIZE], wynik = 0; /*kolejno: tablica do metody dynamicznej, wynik*/
    int ilosc,pojemnosc,waga, wartosc; /*kolejno: ilosc przedmiotow,
pojemnosc plecaka, waga i wartoœæ przedmiotu*/


    cin >> ilosc >> pojemnosc;
    for(int j=1; j<=pojemnosc; j++) plecak[j]=PUSTO;
    plecak[0]=0;
    for(int i=0; i<ilosc; i++)
    {
        cin >> waga >> wartosc;
        for(int j=pojemnosc; j>=0; j--)
            if(plecak[j]!=PUSTO)
            {
                int nowa_waga = j + waga;
                int nowa_wartosc = plecak[j] + wartosc;
                if((nowa_waga<=pojemnosc) && (nowa_wartosc>plecak[nowa_waga]))
                    plecak[nowa_waga] = nowa_wartosc;
            }
    }
    for(int j=0; j<=pojemnosc; j++) if(plecak[j]>wynik) wynik = plecak[j];
    cout << wynik;

}
#define ILE_LICZB 9
#define PUSTE -1.0
//newton[n][k] = symbol newtona; liczba podzbiorów k-elementowych zbioru n-elementowego.
int newton [ILE_LICZB+1][ILE_LICZB+1];
//pr_sukc[k] prawdopodobienstwo sukcesu naszej strategii dla k liczb
void gen_newton () {
    FOR(i,0,ILE_LICZB) {
        newton [i][0] = 1;
        newton [i][i] = 1;
        FOR(j,1,i-1)
        newton [i][j] = newton [i - 1][j - 1] + newton [i - 1][j];
    }
}
int main()
{
    //read_file();
    //read();
    //solution();
    lcs();
    return 0;
}
