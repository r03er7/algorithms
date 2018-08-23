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
	struct Ed : E {
		int v;
		Ed(E p, int w) : E(p), v(w) {}
	};
	struct Ve : V,vector<Ed> {};
	vector<Ve> g;
	Graph(int n=0) : g(n) {}
	void EdgeU(int b, int e, E d = E()) {
	    Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	    eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
	}
	void EdgeD(int b, int e, E d = E()) {g[b].PB(Ed(d,e));}
  void Dfs(int e = -1) {
	VI st(SIZE(g));
	int t = -1 , i = 0, b = 0;
	e==-1 ? e=SIZE(g)-1 : b = e;
	REP(x,SIZE(g)) g[x].d = g[x].f = g[x].s = -1;
	FOR(s,b,e) if(g[s].d == -1) {
		g[st[i++] = s].d = ++t; g[s].f = SIZE(g[s]);
		while(i) {
			int s = st[i-1];
			if (!g[s].f) {g[s].f = ++t; --i;} else {
				if (g[s = g[s][--g[s].f].v].d == -1) {
					g[s].s = st[i-1];
					g[s].f = SIZE(g[s]);
					g[st[i++] = s].d = ++t;
				}
			}
		}
	}
}
  VI vis;
  Graph<V,E> *sccRes;

 void SccDfs(int v,int nr, bool phase){
   g[v].t = 1;
// Jesli wykonywana jest druga faza przeszukiwania, to ustaw dla wierzcholka numer silnie spojnej skladowej
	if(!phase) vis[v] = nr;
// Odwiedz kolejne wierzcholki oraz (jesli wykonywana jest druga faza) dodaj krawedz do konstruowanego grafu silnie spojnych skladowych
    FOREACH(it, g[v]) if (g[it->v].t == -1)
		SccDfs(it->v, nr, phase); else
		if(!phase && nr > vis[it->v])
		sccRes->EdgeD(g[it->v].t, vis[it->v]=nr);
// Jesli wykonywana jest pierwsza faza, to wstaw wierzcholek do listy, jesli natomiast druga, to zaktualizuj jego czas
	if(phase) vis.PB(v); else g[v].t = nr;
  }
// Funkcja wyznaczajaca silnie spojne skladowe w grafie
  Graph<V,E> Scc() {
// Graf gt to graf transponowany, natomiast res to konstruowany graf silnie spojnych skladowych
    Graph<V,E> gt(SIZE(g)),res(SIZE(g)),*tab[]={this, & gt};
    gt.sccRes=&res; gt.vis.resize(SIZE(g), -1); vis.clear();
// Budowa grafu transponowanego
    REP(i,SIZE(g)) FOREACH(it,g[i]) gt.EdgeD(it->v,i);
// Przeprowadz dwie fazy algorytmu DFS...
    REP(i,2){
// Zaznacz wierzcholki jako nieodwiedzone
      FOREACH(it,tab[i]->g) it->t = -1;
      int comp=0,v;
// Dla kolejnych, nieodwiedzonych wierzcholkow, wykonaj przeszukiwanie
      FORD(j,SIZE(g)-1,0)
        if (tab[i]->g[v=(i?vis[j]:j)].t == -1) tab[i]->SccDfs(v,comp++,1-i);
      if (i) res.g.resize(comp);
    }
    REP(i,SIZE(g)) g[i].t=gt.g[i].t;
    return res;
  }
};
struct Ve {int rev;};

struct Vs {
	int d, f, s,t;
	bool c,n;
	 Vs(){c=n=false;}
};


int main() {
	int n, m, b, e;
// Wczytaj opis drzewa, po ktorym podrozuje Bajtazar
	cin >> n;
	//n=input.readInt();
	Graph<Vs, Ve> g(2*n);
	cin>>m;
	REP(x, m) {
		cin >> b >> e;
		if(b%2)--b;
		else ++b;
		//b=input.readInt();
		//e=input.readInt();
		g.EdgeU(b-1, e-1);
	}
	g.Scc();


//	m=input.readInt();
//	b=input.readInt();


//	output(res, '\n');
	return 0;
}
