/*
USER: robert
DATE: 25 10 2014
*/

//#pragma warning (disable: 4786)
//#pragma comment (linker, "/STACK:0x800000")
//#define _CRT_SECURE_NO_WARNINGS 1

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

#include <cassert>//arab
#include <climits>
#include <iomanip>
#include <list>
#include <ctime>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v, n) __typeof(n) v = (n)
#define VAL(i,v) VAR(v,n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define CLR(A,v) memset((A),v,sizeof((A))) //p o size p
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
//ios_base::sync_with_stdio(0);
using namespace std;

template< class T > T _abs(T n) {
    return (n < 0 ? -n : n);
}
template< class T > T _max(T a, T b) {
    return (!(a < b) ? a : b);
}
template< class T > T _min(T a, T b) {
    return (a < b ? a : b);
}
template< class T > T sq(T x) {
    return x * x;
}

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PI;
const int INF = 1000000000;
const LL INFLL = LL(INF) * LL(INF);
const double EPS=1e-9;
template<class T> inline int size(const T&c) {
    return c.size();
}
template<class T> T parse(string s) {
    istringstream i(s);
    T x;
    i>>x;
    return x;
}
template<class T> string show(T x) {
    ostringstream o;
    o<<x;
    return o.str();
}
VS split(string s, string del=" ") {
    string w;
    VS res;
    s += del[0];
    FOREACH(it,s) {
        if(find(ALL(del),*it)==del.end()) w += *it;
        else if (w!="") {
            res.push_back(w);
            w="";
        }
    }
    return res;
}
VI s2vi(string s, string del=" ") {
    VS v = split(s,del);
    VI res;
    FOREACH(it,v) res.push_back(parse<int>(*it));
    return res;
}
string mergeStrings(VS v) {
    string s;
    FOREACH(it,v) s += *it;
    return s;
}

#define debug(x) cerr << #x << " = " << x << "\n";
#define debugv(x) cerr << #x << " = "; FOREACH(it,(x)) cerr << *it << ","; cerr << "\n";
#define MAXN 1000001

int a[MAXN];
int n,t;
void read_file() {
    FILE *plik=fopen("mon8b.in","r");
    fscanf(plik,"%d%d",&n,&t);
    REP(i,n)fscanf(plik,"%d",&a[i]);
    ///REP(i,n)debug(a[i]);
}
void read() {
    scanf("%d%d",&n,&t);
    REP(i,n)scanf("%d",&a[i]);
}
int solution() {
    LL s;
    return 0;
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
void podzial(int k,int n) {
    VI aa;
    REP(i,n)aa.PB(i+1);
    VI vec(6,0);
    FOR(i,k,n)vec[i]=1;
    int c=-1;
    do {
        printf("\n%d\t",++c);
        ///FOREACH(it,vec)
        REP(i,SIZE(vec))
        if(vec[i])printf(" %d",aa[i]);
    } while(next_permutation(ALL(vec)));
}
/*
In gcc/g++ fread_unlocked() is even faster.
Can be made faster in non-object-oriented fashion with macros instead of functions.
In contest, who cares dynamic allocation?
*/

struct FastRead {
    char *buff, *ptr;
    FastRead(int size) {
        buff = new char[size];
        ptr = buff;
        fread(buff, 1, size, stdin);
    }
    ~FastRead() {
        delete[] buff;
    }
    int nextInt() {
        int ret = 0;
        while(*ptr < '0' || *ptr > '9') ptr++;
        do {
            ret = ret * 10 + *ptr++ - '0';
        } while(*ptr >= '0' && *ptr <= '9');
        return ret;
    }
};
/*
Usage: Just create an instance of it at the start of the block of
which you want to measure running time. Reliable up to millisecond
scale. You don't need to do anything else, even works with freopen.
*/

class TimeTracker {
    clock_t start, end;
public:
    TimeTracker() {
        start = clock();
    }
    ~TimeTracker() {
        end = clock();
        fprintf(stderr, "%.3lf s\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
};


#define READ(f) freopen(f, "r", stdin)
#define WRITE(f) freopen(f, "w", stdout)
int main() {
    READ("in.txt");
    WRITE("out.txt");
    //FastRead sth(1000);
    //int a=sth.nextInt();
    {
        TimeTracker sth;

        REP(i,1000000) {
            printf("%d ",i);


        }
    }
    //podzial(4,6);
    return 0;
}
