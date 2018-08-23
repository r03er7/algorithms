#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <sstream>
#include <utility>
#include <unistd.h>
using namespace std;
typedef unsigned long long ULL;
typedef long double LD;
typedef long long LL;
const int INF = 1000000000; const LL INFLL = LL(INF) * LL(INF);
template<class T> inline int size(const T&c) { return c.size(); }
inline bool myisspace(char c) { return c>=0 && c<=' '; }
typedef vector<int> VI;
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
#include <list>

class INPUT {
  static const int BUFSIZE = 1<<16;
  static char buffer[];
  char *bufpos;
  char *bufend;
  void grabBuffer();
 public:
  INPUT() { grabBuffer(); }
  bool eof() { return bufend==buffer; }
  char nextChar() { return *bufpos; }
  inline char readChar();
  inline void skipWS();
  inline unsigned readUnsigned();
  inline int readInt();
  inline ULL readULL();
  inline LL readLL();
  inline void readString(char *p);
  inline string readString(int maxlen=100);
  inline LD readLD();
};

char INPUT::buffer[INPUT::BUFSIZE];

void INPUT::grabBuffer() {
  bufpos = buffer;
  bufend = buffer + read(0, buffer, BUFSIZE);
}

char INPUT::readChar() {
  char res = *bufpos++;
  if(bufpos==bufend) grabBuffer();
  return res;
}

void INPUT::skipWS() {
  while(!eof() && myisspace(nextChar())) readChar();
}

unsigned INPUT::readUnsigned() {
  skipWS();
  unsigned res = 0;
  while(!eof() && isdigit(nextChar())) {
    res = 10u * res + (readChar()-'0');
  }
  return res;
}

int INPUT::readInt() {
  skipWS();
  bool neg = false;
  if(!eof() && nextChar()=='-') { neg=true; readChar(); }
  int res = static_cast<int>(readUnsigned());
  if(neg) res = -res;
  return res;
}

ULL INPUT::readULL() {
  skipWS();
  ULL res = 0;
  while(!eof() && isdigit(nextChar())) {
    res = 10u * res + (readChar()-'0');
  }
  return res;
}

LL INPUT::readLL() {
  skipWS();
  bool neg = false;
  if(!eof() && nextChar()=='-') { neg=true; readChar(); }
  LL res = static_cast<LL>(readUnsigned());
  if(neg) res = -res;
  return res;
}

void INPUT::readString(char *p) {
  skipWS();
  while(!eof() && !myisspace(nextChar())) *p++ = readChar();
  *p = 0;
}

string INPUT::readString(int maxlen) {
  char buf[maxlen+1];
  readString(buf);
  return string(buf);
}

LD INPUT::readLD() {
  char buf[100];
  readString(buf);
  LD res;
  sscanf(buf,"%Lf",&res);
  return res;
}

class OUTPUT {
  static const int BUFSIZE = 1<<16;
  static char buffer[];
  char *bufpos;
  char *BUFLIMIT;
  void flushBuffer();
 public:
  OUTPUT():bufpos(buffer),BUFLIMIT(buffer+BUFSIZE-100) {}
  ~OUTPUT() { flushBuffer(); }
  inline void operator()(char c);
  inline void operator()(unsigned x);
  inline void operator()(int x);
  inline void operator()(ULL x);
  inline void operator()(LL x);
  inline void operator()(const char*s);
  void operator()(const string&s) { operator()(s.c_str()); }
  inline void print(double d, int prec);
  inline void print(LD d, int prec);
  template<class A,class B>
  void operator()(const A& a,const B& b) {
    operator()(a); operator()(b);
  }
  template<class A,class B,class C>
  void operator()(const A& a,const B& b,const C&c) {
    operator()(a); operator()(b); operator()(c);
  }
  template<class A,class B,class C,class D>
  void operator()(const A& a,const B& b,const C&c,const D&d) {
    operator()(a); operator()(b); operator()(c); operator()(d);
  }
  template<class A,class B,class C,class D,class E>
  void operator()(const A& a,const B& b,const C&c,const D&d,const E&e) {
    operator()(a); operator()(b); operator()(c); operator()(d); operator()(e);
  }
  template<class A,class B,class C,class D,class E,class F>
  void operator()(const A& a,const B& b,const C&c,const D&d,const E&e,const F&f) {
    operator()(a); operator()(b); operator()(c); operator()(d); operator()(e); operator()(f);
  }
};

char OUTPUT::buffer[OUTPUT::BUFSIZE];

void OUTPUT::flushBuffer() {
  char *p = buffer;
  while(p < bufpos) {
    p += write(1, p, bufpos-p);
  }
  bufpos = buffer;
}

void OUTPUT::operator()(char c) {
  *bufpos = c;
  ++bufpos;
  if(bufpos >= BUFLIMIT) flushBuffer();
}

void OUTPUT::operator()(unsigned x) {
  char *old = bufpos;
  do {
    *bufpos = char('0' + x % 10u);
    x /= 10u;
    ++bufpos;
  } while(x);
  reverse(old, bufpos);
  if(bufpos >= BUFLIMIT) flushBuffer();
}

void OUTPUT::operator()(int x) {
  if(x<0) { operator()('-'); x = -x; }
  operator()(static_cast<unsigned>(x));
}

void OUTPUT::operator()(ULL x) {
  char *old = bufpos;
  do {
    *bufpos = char('0' + x % 10u);
    x /= 10u;
    ++bufpos;
  } while(x);
  reverse(old, bufpos);
  if(bufpos >= BUFLIMIT) flushBuffer();
}

void OUTPUT::operator()(LL x) {
  if(x<0) { operator()('-'); x = -x; }
  operator()(static_cast<ULL>(x));
}

void OUTPUT::operator()(const char*s) {
  while(*s) operator()(*s++);
}

void OUTPUT::print(double d, int prec) {
  char buf[100];
  sprintf(buf, "%.*f", prec, d);
  operator()(buf);
}

void OUTPUT::print(LD d, int prec) {
  char buf[100];
  sprintf(buf, "%.*Lf", prec, d);
  operator()(buf);
}

INPUT input;
OUTPUT output;

















template<class V, class E> struct Graph {
// Typ krawedzi (Ed) dziedziczy po typie zawierajacym dodatkowe informacje zwiazane z krawedzia (E). Zawiera on rowniez pole v, okreslajace numer wierzcholka, do ktorego prowadzi krawedz. Zaimplementowany konstruktor pozwala na skrocenie zapisu wielu funkcji korzystajacych ze struktury grafu.
	struct Ed : E {
		int v;
		Ed(E p, int w) : E(p), v(w) {}
	};
// Typ wierzcholka (Ve) dziedziczy po typie zawierajacym dodatkowe informacje z nim zwiazane (V) oraz po wektorze krawedzi. To drugie dziedziczenie moze wydawac sie na pierwszy rzut oka stosunkowo dziwne, lecz jest ono przydatne - umozliwia latwe iterowanie po wszystkich krawedziach wychodzacych z wierzcholka v: FOREACH(it, g[v])
	struct Ve : V,vector<Ed> {};
// Wektor wierzcholkow w grafie
	vector<Ve> g;
// Konstruktor grafu - przyjmuje jako parametr liczbe wierzcholkow
	Graph(int n=0) : g(n) {}
// Funkcja dodajaca do grafu nowa krawedz nieskierowana, laczaca wierzcholki b i e oraz zawierajaca dodatkowe informacje okreslone przez zmienna d. Krawedz nieskierowana jest reprezentowana przez dwie krawedzie skierowane - jedna prowadzaca z wierzcholka b do wierzcholka e, oraz druga z wierzcholka e do b. Struktura E w grafach nieskierowanych musi dodatkowo zawierac element int rev. Dla danej krawedzi skierowanej $(b,e)$, pole to przechowuje pozycje krawedzi $(e,b)$ na liscie incydencji wierzcholka $e$. Dzieki temu, dla dowolnej krawedzi w grafie w czasie stalym mozna znalezc krawedz o przeciwnym zwrocie.
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
  void Dfs(int e = -1) {
	VI st(SIZE(g));
	int t = -1 , i = 0, b = 0;
	e==-1 ? e=SIZE(g)-1 : b = e;
	REP(x,SIZE(g)) g[x].d = g[x].f = g[x].s = -1;
// Dla wszystkich wierzcholkow z przedzialu [b..e], jesli wierzcholek nie byl jeszcze odwiedzony...
	FOR(s,b,e) if(g[s].d == -1) {
// Wstaw wierzcholek na stos i ustaw dla niego odpowiedni czas wejscia. Zmienna f wierzcholka sluzy tymczasowo jako licznik nieprzetworzonych krawedzi wychodzacych z wierzcholka.
		g[st[i++] = s].d = ++t; g[s].f = SIZE(g[s]);
// Dopoki stos jest niepusty...
		while(i) {
			int s = st[i-1];
// Przetworz kolejna krawedz wychodzaca z aktualnego wierzcholka, lub usuñ go ze stosu (gdy nie ma juz wiecej krawedzi)
			if (!g[s].f) {g[s].f = ++t; --i;} else {
// Jesli wierzcholek, do ktorego prowadzi krawedz nie byl jeszcze odwiedzony, to...
				if (g[s = g[s][--g[s].f].v].d == -1) {
// Ustaw numer wierzcholka-ojca w drzewie DFS oraz ustaw liczbe nieprzetworzonych krawedzi wychodzacych z wierzcholka
					g[s].s = st[i-1];
					g[s].f = SIZE(g[s]);
// Wstaw wierzcholek na stos i ustaw czas wejscia
					g[st[i++] = s].d = ++t;
				}
			}
		}
	}
}
};
struct Ve {int rev;};
// Wzbogacenie struktury wierzcholkow w grafie zawiera dodatkowe elementy wymagane przez algorytm DFS, oraz liste l uzywana przez algorytm LCA, sluzacego do wyznaczania najwczesniejszego wspolnego przodka dwoch wierzcholkow w drzewie
struct Vs {
	int d, f, s;
	VI l;
};

// Makro Desc zwraca prawde, jesli wierzcholek n jest przodkiem wierzcholka m w drzewie g
#define Desc(n,m) (g->g[n].d <= g->g[m].d && g->g[n].f >= g->g[m].f)
// Funkcja LCA zwraca odleglosc wierzcholka b od sciezki prowadzacej miedzy wierzcholkiem e, a korzeniem drzewa g
int LCA(Graph<Vs, Ve> *g, int b, int e) {
	int res = 0, p = SIZE(g->g[b].l)-1;
// Dopoki wierzcholek b nie jest przodkiem wierzcholka e...
	while(!Desc(b, e)) {
// Wykorzystujac wyznaczone wartosci przodkow z tablicy LCA, przesuwamy sie w gore drzewa, wykonujac za kazdym razem krok o wielkosci bedacej potega dwojki
		p = min(p, SIZE(g->g[b].l)-1);
		while(p>0 && Desc(g->g[b].l[p], e)) p--;
// Zwieksz wyznaczona odleglosc o wielkosc wykonywanego kroku oraz wykonaj ten krok
		res += (1<<p);
		b = g->g[b].l[p];
	}
	return res;
}

// Funkcja wyznacza wartosci tablic l dla wszystkich wierzcholkow drzewa. Dla ustalonego wierzcholka v, kolejne elementy tablicy l reprezentuja numery wierzcholkow o odleglosci 1, 2, 4 ... od wierzcholka v w kierunku korzenia drzewa (wierzcholek numer 0)
void GenLCA(Graph<Vs, Ve> *g, int v) {
	if (v != 0 && !SIZE(g->g[v].l)) {
		int c = g->g[v].s;
// Wyznacz liste l dla ojca wierzcholka v
		GenLCA(g, c);
// Wstaw na liste l wierzcholka v jego ojca jako pierwszy element
		g->g[v].l.PB(c);
// Wykorzystaj tablice LCA przodkow do wyznaczenia wyniku dla wierzcholka v
		while(SIZE(g->g[c].l) >= SIZE(g->g[v].l)) {
			c = g->g[c].l[SIZE(g->g[v].l)-1];
			g->g[v].l.PB(c);
		}
	}
}

int main() {
	int n, m, b, e;
// Wczytaj opis drzewa, po ktorym podrozuje Bajtazar
	//cin >> n;
	n=input.readInt();
	Graph<Vs, Ve> gr(n);
	REP(x, n-1) {
		//cin >> b >> e;
		b=input.readInt();
		e=input.readInt();
		gr.EdgeU(b-1, e-1);
	}
// Wykonaj algorytm DFS, a nastepnie wylicz wartosci list LCA wierzcholkow
	gr.Dfs(0);
	FOR(x,1,n-1) GenLCA(&gr, x);
// Wczytaj dlugosc trasy Bajtazara oraz miejsce startowe
	//cin >> m;
	//cin >> b;
	m=input.readInt();
	b=input.readInt();
	int res = 0;
// Dla kolejnej trasy, wyznacz jej dlugosc oraz zwieksz wynik
	REP(x, m-1) {
		//cin >> e;
		e=input.readInt();
		res += LCA(&gr, b-1, e-1) + LCA(&gr, e-1, b-1);
		b = e;
	}
// Wypisz wynik
	output(res, '\n');
	return 0;
}
