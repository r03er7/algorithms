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
#include <tr1/unordered_set>
#include <tr1/unordered_map>
struct MyHasher {
    LL operator()(const LL& a) const {
        return 1L; //obliczenia
    }
    ///int H=1000000007
    ///h( LL a ) = a%H, h( a, b) = (a*10^9  + b)%H.
};
using namespace tr1;
unordered_map<LL,LL, MyHasher> UM;
UM[10]++;
int main() {
    //read_file();
    //read();
    //solution();
    return 0;
}
stack<int> stos;
size()
push(v)
pop()
top()

list<int> lista;
size()
push back(v)
pop back()
back()
push front(v)
pop front()
front()
erase(i)
insert(i, v)

queue<int> kolejka;
size()
push(v)
pop()
front()
back()

vector<int>;
size()
push back(v)
pop back()
back()
[k]

deque<int>
size()
push back(v)
pop back()
back()
push front(v)
pop front()
front()
[k]

priority queue
size()
push(v)
pop()
top()

set
size()
insert(v)
find(v)
erase(v)
erase(i)
lower bound(v)
upper bound(v)

map //prawie jak set< pair<x,y> >
size()
[k] = v
      [k]
      find(k)
      erase(k)
      erase(i)
      lower bound(k)
      upper bound(k)

      swpa
      min
      max
      abs()
      pow ( 2,x );
bool cmp_parz ( const int & a, const int & b) {
    if (a % 2 == b % 2)
        return a <= b;
    else
        return (a % 2 == 1);
}
int liczby [] = { 5, 8, 3, 6, 1, 2, 7 };
sort ( liczby , liczby + 7, cmp_parz );
sort ( liczby , liczby + 7);
stable sort
nth element
nth_element(liczby,liczby+(n-1)/2,liczby+n);//mediana
liczby[(n-1)/2];
reverse
VI vec;
vec.PB(3);
vec.PB(5);
vec.PB(7);
while(next_permutation(ALL(v)));
random_shuffle (array , array + n);
