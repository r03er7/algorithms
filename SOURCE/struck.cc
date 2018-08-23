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
#define debug(x) cerr << #x << " = " << x << "\n";
#define debugv(x) cerr << #x << " = "; FOREACH(it,(x)) cerr << *it << ","; cerr << "\n";
#define MAXN 1000001
///8hetmanow
#include <algorithm> //pozwala korzystaæ z funkcji abs, która zwraca wartoœæ bezw
int het[9]; //pozycje hetmanów w kolejnych wierszach
void wypisz()  //wypisuje bie¿¹ce ustawienie
{
    for(int i=1; i<=8; i++)
    {
        for(int j=1; j<=8; j++)
            printf(het[i] == j ? "X" : "O");
        printf("\n");
    }
    printf("\n");
}
int backtrack(int n)  //n-liczba ju¿ rozstawionych hetmanów
{
    if(n == 8)
    {
        wypisz();
    }
    else
    {
        for(het[n+1]=1; het[n+1]<=8; het[n+1]++) //próbuj ustawiæ (n+1)-szego hetman
        {
            bool ok=true; //czy w tym ustawieniu hetmany siê nie atakuj¹?
            for(int j=1; j<=n; j++)
                if(het[j] == het[n+1] || abs(het[n+1]-het[j]) == (n+1)-j) //jeœli j-t
                {
                    ok=false;    //...hetmany siê atakuj¹, to to zapisz
                    break;
                }
            if(ok)
                backtrack(n+1);
        }
    }
}
...
backtrack(0);
///8hetmanoow end
///euler furego
vector<int> cykl; //cykl Eulera w odwrotnej kolejnoœci
void go(int v)  //aby odwiedziæ v:
{
    while(!kraw[v].empty())  //dopóki istnieje krawêdŸ z v
    {
        int w=kraw[v].back(); //zapamiêtaj dok¹d ona prowadzi
        kraw[v].pop_back(); //usuñ j¹
        go(w); //i odwiedŸ wierzcho³ek, do którego prowadzi³a
        cykl.push_back(v); //a nastêpnie dodaj v do cyklu
    }
}
...
go(1); //zaczynamy z dowolnego wierzcho³ka
for(int i=cykl.size()-1; i>=0; i--) //wypisujemy zawartoœæ cykl
    printf("%d ",cykl[i]); //...w odwrotnej kolejnoœci
///euler flury end
//belman
for(int i=1; i<=n; i++) dis[i]=INF;
dis[s]=0;
for(int q=1; q<=n-1; q++) //powtórz (n-1)-krotnie
    for(int v=1; v<=n; v++) //dla ka¿dego wierzcho³ka
        for(int i=0; i<kraw[v].size(); i++) //dla ka¿dej krawêdzi
        {
            int w=kraw[v][i];
            int k=waga[v][i];
//relaksacja krawêdzi v->w o koszcie k:
            if(dis[v] + k < dis[w])
            {
                dis[w]=dis[v]+k;
                ojc[w]=v;
            }
        }
//lord end
///kmp
P[0] = 0;
P[1] = 0;
j=0;
for(i = 2; i <= m; i++)
{
    while( (j > 0) && (s[j+1] != s[i]) )
        j = P[j];
    if(s[j+1] == s[i])
        j++;
    P[i] = j;
}
//wzorzec
j=0;
for(i = 1; i <= n; i++)
{
    while(j > 0 && s[j+1] != t[i])
        j = P[j];
    if(s[j+1] == t[i])
        j++;
    if(j==m)
    {
        printf("Wyst¹pienie wzorca w s³owie na pozycjach od %d do %d.\n",i-m+1,i)
        j = P[j];
    }
}
///kmp end
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
///heap
#define MAXN 1000000
int heap[MAXN+1];
int size=0; //liczba elementów w kopcu
//elementy w kopcu to heap[1],heap[2],...,heap[size]
void heapUp(int x)  //kopcuje w górê element na pozycji x
{
    while(heap[x/2] > heap[x])
    {
        swap(heap[x], heap[x/2]); //zamienia wartoœci w obu wêz³ach
        x/=2;
    }
}
void insert(int x)  //dodaje x do kopca
{
    heap[++size]=x;
    heapUp(size);
}
int minimum()  //zwraca minimum
{
    return heap[1];
}
void heapDown(int x)  //kopcuje w dó³ element na pozycji x
{
    while(2*x <= size)  //dopóki x ma chocia¿ jednego syna
    {
        int son=2*x;
        if(2*x+1 <= size && heap[2*x+1] < heap[2*x])
            son=2*x+1;
//zmienna son zawiera teraz indeks syna x o mniejszej wartoœci
        if(heap[son] >= heap[x]) break;
        swap(heap[x], heap[son]); //zamienia wartoœci w obu wêz³ach
        x=son;
    }
}
void eraseRoot()  //usuwa korzeñ (czyli minimum)
{
    heap[1]=heap[size--];
    heapDown(1);
}
//heap
//zamiatanie
struct event
{
    int x; /* wspó³rzêdna, na której wystêpuje zdarzenie */
    /* Typ zdarzenia: *
    /* 1 - pocz¹tek odcinka poziomego *
    * -1 - koniec odcinka poziomego *
    * 0 - odcinek pionowy */
    int type;
    int y1, y2; /* dolna i górna wspó³rzêdna y *
* (dla odcinków poziomych y1 = y2) */
    int operator<(const event& e) const
    {
        if(x == e.x)
            return type > e.type;
        else
            return x < e.x;
    }
};
// events - kontener typu vector<event> przechowuj¹cy zdarzenia
// sortujemy zdarzenia zgodnie ze zdefiniowanym porz¹dkiem
sort(events.begin(), events.end());
// zmienna zliczaj¹ca znalezione przeciêcia
long long inter = 0;
for(int i=0; i<(int)events.size(); i++)
{
    if(events[i].type == 0) //odcinek pionowy
        inter += query(events[i].y1, events[i].y2);
    else
        insert(events[i].y1, events[i].type);
}
//zamiatanie
double atan2(double y, double x);
long double atan2l(long double y, long double x);
//trie
#define ALPH 26 // rozmiar alfabetu
struct TrieNode // wêze³ drzewa TRIE
{
// konstruktor ustawiaj¹cy ojca i znak na krawêdzi prowadz¹cej od ojca
    TrieNode(TrieNode *_parent, char _last)
    {
        for(int i = 0; i < ALPH; ++i)
            links[i] = NULL;
        parent = _parent;
        last = _last;
        in_dict = false;
    }
    TrieNode *links[ALPH]; // tablica potomków
    TrieNode *parent; // wskaŸnik do ojca
    char last; // znak na krawêdzi prowadz¹cej od ojca
    bool in_dict; // czy s³owo jest w drzewie
};
struct Trie
{
    Trie() // konstruktor tworz¹cy korzeñ drzewa
    {
        root = new TrieNode(NULL, ’-’);
    }
    void insert(string &word)
    {
        TrieNode *v = root; // wskaŸnik na aktualny wêze³
        for(int i = 0; i < (int)word.size(); ++i)
        {
            if(v->links[word[i] - ’a’] == NULL)
// jeœli nie ma jeszcze krawêdzi z dan¹ liter¹
// to utwórz nowego potomka
                v->links[word[i] - ’a’] = new TrieNode(v, word[i]);
            v = v->links[word[i] - ’a’];
        }
        v->in_dict = true;
    }
    bool search(string &word)
    {
        TrieNode *v = root; // wskaŸnik na aktualny wêze³
        for(int i = 0; i < (int)word.size(); ++i)
        {
            if(v->links[word[i] - ’a’] == NULL)
// jeœli nie ma krawêdzi z dan¹ liter¹ to zwróæ fa³sz
                return false;
            else // jeœli jest to przejdŸ po niej
                v = v->links[word[i] - ’a’];
        }
        return v->in_dict;
    }
    TrieNode *root;
};//trie
//aho
void create_links(Trie &trie)
{
// przechodzimy drzewo algorytmem BFS
    queue<TrieNode*> Q;
// wstawiamy korzeñ do kolejki
    Q.push(trie.root);
    trie.root->suf_link = trie.root->dict_link = NULL;
    while(!Q.empty())
    {
        TrieNode *v = Q.front();
        Q.pop();
        if(v != trie.root) // wêze³ nie jest korzeniem
        {
// postêpujemy tak jak w KMP - cofamy siê po kolejnych suf_linkach
// dopóki nie natrafimy na krawêdŸ o odpowiedniej etykiecie
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
void aho_corasick(Trie &trie, string &text)
{
    TrieNode *v = trie.root, *tmp;
    for(int i = 0; i < (int)text.size(); ++i)
    {
        while(v && v->links[text[i] - ’a’] == NULL)
            v = v->suf_link;
        if(v == NULL)
            v = trie.root;
        else v = v->links[text[i] - ’a’];
// sprawdzamy, czy s¹ jakieœ dopasowania
        if(v->in_dict)
            tmp=v;
        else tmp = v->dict_link;
        while(tmp)
        {
            printf("Znaleziono wystapienie wzorca numer %d.\n", tmp->id);
            tmp = tmp->dict_link;
        }
    }
}//aho
//maska
bool odp = false;
/* Maski odpowiadaj¹ce wszystkim podzbiorom zbioru *
* n-elementowego to po prostu liczby od 0 do (1 << n)-1 */
int ogr = 1 << n;
for (int maska = 0; maska < ogr; maska++)
{
    int suma = 0;
    /* sprawdzamy, które elementy s¹ w sprawdzanym podzbiorze */
    for (int i = 0; i<n; i++)
        if ((maska & (1<<i)) != 0)
            suma += a[i];
    if (suma == S)
    {
        odp = true;
        break;
    }
}
/* Wynik: w zmiennej odp */
t[mask][a] - maksymalne zadowolenie zbioru przedszkolaków (przechowywanego w masce
        mask) w ustawieniu gdzie dziecko o numerze a jest na koñcu.
for (int maska = 1; maska < (1 << n); maska++)
    for (int i = 0,a=1; i<n; i++, a <<= 1)
        /* ustalamy ostatnie dziecko z danego zbioru */
        if (a & maska)
        {
            if ((a ^ maska) == 0)
            {
                /* przypadek samotnego dziecka */
                t[maska][i] = 0;
                continue;
            }
            int nw = 0;
            for (int j = 0,b=1; j<n; j++, b <<= 1)
            {
                /* sprawdzamy wszystkie mo¿liwe przedostatnie przedszkolaki, *
                * ró¿ne od ostatniego i bêd¹ce w przetwarzanym zbiorze */
                if (j != i && (b & maska))
                    /* t[maska ^ a][j] to wynik dla zbioru bez ostatniego dziecka *
                    * z j-tym dzieckiem na koñcu */
                    if (t[maska ^ a][j] + w[i][j] > nw)
                        nw = t[maska ^ a][j] + w[i][j];
            }
            t[maska][i] = nw;
        }
int main()
{
    //read_file();
    //read();
    //solution();
    lcs();
    return 0;
}
