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

//template<class T> inline int size(const T&c) {
//    return c.size();
//}
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
int heap[MAXN+1];
int size=0; //liczba elementów w kopcu
//elementy w kopcu to heap[1],heap[2],...,heap[size]
void heapUp(int x) { //kopcuje w górę element na pozycji x
    while(heap[x/2] > heap[x]) {
        swap(heap[x], heap[x/2]); //zamienia wartości w obu węzłach
        x/=2;
    }
}
void insert(int x) { //dodaje x do kopca
    heap[++size]=x;
    heapUp(size);
}
int minimum() { //zwraca minimum
    return heap[1];
}
void heapDown(int x) { //kopcuje w dół element na pozycji x
    while(2*x <= size) { //dopóki x ma chociaż jednego syna
        int son=2*x;
        if(2*x+1 <= size && heap[2*x+1] < heap[2*x])
            son=2*x+1;
//zmienna son zawiera teraz indeks syna x o mniejszej wartości
        if(heap[son] >= heap[x]) break;
        swap(heap[x], heap[son]); //zamienia wartości w obu węzłach
        x=son;
    }
}
void eraseRoot() { //usuwa korzeń (czyli minimum)
    heap[1]=heap[size--];
    heapDown(1);
}
int FIND(int x) {
    if (father[x] == x) return x;
    father[x] = FIND(father[x]);
    return father[x];
}
///zamiatanie
struct event {
    int x; /* współrzędna, na której występuje zdarzenie */
    /* Typ zdarzenia: *
    /* 1 - początek odcinka poziomego *
    * -1 - koniec odcinka poziomego *
    * 0 - odcinek pionowy */
    int type;
    int y1, y2; /* dolna i górna współrzędna y *
* (dla odcinków poziomych y1 = y2) */
    int operator<(const event& e) const {
        if(x == e.x)
            return type > e.type;
        else
            return x < e.x;
    }
};
// events - kontener typu vector<event> przechowujący zdarzenia
// sortujemy zdarzenia zgodnie ze zdefiniowanym porządkiem
sort(events.begin(), events.end());
// zmienna zliczająca znalezione przecięcia
long long inter = 0;
for(int i=0; i<(int)events.size(); i++) {
    if(events[i].type == 0) //odcinek pionowy
        inter += query(events[i].y1, events[i].y2);
    else
        insert(events[i].y1, events[i].type);
}

double atan2(double y, double x);
long double atan2l(long double y, long double x);

bool odp = false;
/* Maski odpowiadające wszystkim podzbiorom zbioru *
* n-elementowego to po prostu liczby od 0 do (1 << n)-1 */
int ogr = 1 << n;
for (int maska = 0; maska < ogr; maska++) {
    int suma = 0;
    /* sprawdzamy, które elementy są w sprawdzanym podzbiorze */
    for (int i = 0; i<n; i++)
        if ((maska & (1<<i)) != 0)
            suma += a[i];
    if (suma == S) {
        odp = true;
        break;
    }
}
/* Wynik: w zmiennej odp */

///ahiciri
void create_links(Trie &trie) {
// przechodzimy drzewo algorytmem BFS
    queue<TrieNode*> Q;
// wstawiamy korzeń do kolejki
    Q.push(trie.root);
    trie.root->suf_link = trie.root->dict_link = NULL;
    while(!Q.empty()) {
        TrieNode *v = Q.front();
        Q.pop();
        if(v != trie.root) { // węzeł nie jest korzeniem
// postępujemy tak jak w KMP - cofamy się po kolejnych suf_linkach
// dopóki nie natrafimy na krawędź o odpowiedniej etykiecie
            TrieNode *j = v->parent->suf_link;
            while(j && j->links[v->last - ’a’] == NULL)
                j = j->suf_link;
            if(j == NULL)
                v->suf_link = trie.root;
            else v->suf_link = j->links[v->last - ’a’];
            if(v->suf_link->in_dict) // ustawiamy dict_link
                v->dict_link = v->suf_link;
            else v->dict_link = v->suf_link->dict_link;
        }
// wstawiamy wszystkich potomków v do kolejki
        for(int i = 0; i < ALPH; ++i)
            if(v->links[i] != NULL)
                Q.push(v->links[i]);
    }
}
void aho_corasick(Trie &trie, string &text) {
    TrieNode *v = trie.root, *tmp;
    for(int i = 0; i < (int)text.size(); ++i) {
        while(v && v->links[text[i] - ’a’] == NULL)
            v = v->suf_link;
        if(v == NULL)
            v = trie.root;
        else v = v->links[text[i] - ’a’];
// sprawdzamy, czy są jakieś dopasowania
        if(v->in_dict)
            tmp=v;
        else tmp = v->dict_link;
        while(tmp) {
            printf("Znaleziono wystapienie wzorca numer %d.\n", tmp->id);
            tmp = tmp->dict_link;
        }
    }
}




t[mask][a];
for (int maska = 1; maska < (1 << n); maska++)
    for (int i = 0,a=1; i<n; i++, a <<= 1)
        /* ustalamy ostatnie dziecko z danego zbioru */
        if (a & maska) {
            if ((a ^ maska) == 0) {
                /* przypadek samotnego dziecka */
                t[maska][i] = 0;
                continue;
            }
            int nw = 0;
            for (int j = 0,b=1; j<n; j++, b <<= 1) {
                /* sprawdzamy wszystkie możliwe przedostatnie przedszkolaki, *
                * różne od ostatniego i będące w przetwarzanym zbiorze */
                if (j != i && (b & maska))
                    /* t[maska ^ a][j] to wynik dla zbioru bez ostatniego dziecka *
                    * z j-tym dzieckiem na końcu */
                    if (t[maska ^ a][j] + w[i][j] > nw)
                        nw = t[maska ^ a][j] + w[i][j];
            }
            t[maska][i] = nw;
        }










int main() {
    //read_file();
    //read();
    //solution();
    //podzial(4,6);
    set<int> zb;
    multiset<int> mzb;
    zb.insert(6);
    zb.erase(7);
    if (zb.find(4) != zb.end()) {
// 4 jest w zbiorze zb
    }
    return 0;
}
