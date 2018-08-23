#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Dwa z najczesciej uzywanych typow o dlugich nazwach - ich skrocenie jest bardzo istotne
typedef vector<int> VI;
typedef long long LL;

// W programach bardzo rzadko mozna znalezc w pelni zapisana instrukcje petli. Zamiast niej, wykorzystywane sa trzy nastepujace makra:
// FOR - petla zwiekszajaca zmienna x od b do e wlacznie
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
// FORD - petla zmniejszajaca zmienna x od b do e wlacznie
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
// REP - petla zwiekszajaca zmienna x od 0 do n. Jest ona bardzo czesto wykorzystywana do konstruowania i przegladania struktur danych
#define REP(x, n) for(int x = 0; x < (n); ++x)
// Makro VAR(v,n) deklaruje nowa zmienna o nazwie v oraz typie i wartosci zmiennej n. Jest ono czesto wykorzystywane podczas operowania na iteratorach struktur danych z biblioteki STL, ktorych nazwy typow sa bardzo dlugie
#define VAR(v, n) __typeof(n) v = (n)
// ALL(c) reprezentuje pare iteratorow wskazujacych odpowiednio na pierwszy i za ostatni element w strukturach danych STL. Makro to jest bardzo przydatne chociazby w przypadku korzystania z funkcji sort, ktora jako parametry przyjmuje pare iteratorow reprezentujacych przedzial elementow do posortowania.
#define ALL(c) (c).begin(), (c).end()
// Ponizsze makro sluzy do wyznaczania rozmiaru struktur danych STL. Uzywa sie go w programach, zamiast pisac po prostu x.size() z uwagi na fakt, iz wyrazenie x.size() jest typu unsigned int i w przypadku porownywania z typem int, w procesie kompilacji generowane jest ostrzezenie.
#define SIZE(x) ((int)(x).size())
// Bardzo pozyteczne makro, sluzace do iterowania po wszystkich elementach w strukturach danych STL.
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
// Skrot - zamiast pisac push_back podczas wstawiania elementow na koniec struktury danych, takiej jak vector, wystarczy napisac PB
#define PB push_back
// Podobnie - zamiast first bedziemy pisali po prostu ST
#define ST first
// a zamiast second - ND.
#define ND second
// Stala EPS jest uzywana w wielu algorytmach geometrycznych do porownywania wartosci bliskich zera
const double EPS = 10e-9;
namespace Simplex{
// Typ wykorzystywany do wykonywania obliczeñ - domyslnie jest to long double
  typedef long double T;
  typedef vector<T> VT;
  vector<VT> A;
  VT b,c,res;
  VI kt,N;
  int m;
  inline void pivot(int k,int l,int e){
      int x=kt[l]; T p=A[l][e];
      REP(i,k) A[l][i]/=p; b[l]/=p; N[e]=0;
      REP(i,m) if (i!=l) b[i]-=A[i][e]*b[l],A[i][x]=A[i][e]*-A[l][x];
      REP(j,k) if (N[j]){
        c[j]-=c[e]*A[l][j];
        REP(i,m) if (i!=l) A[i][j]-=A[i][e]*A[l][j];
      }
      kt[l]=e; N[x]=1; c[x]=c[e]*-A[l][x];
  }
  VT doit(int k){
    VT res; T best;
    while (1){
      int e=-1,l=-1; REP(i,k) if (N[i] && c[i]>EPS) {e=i; break;}
      if (e==-1) break;
      REP(i,m) if (A[i][e]>EPS && (l==-1 || best>b[i]/A[i][e]))
        best=b[ l=i ]/A[i][e];
      if (l==-1) 
		return VT();
      pivot(k,l,e);
    }
    res.resize(k,0); REP(i,m) res[kt[i]]=b[i];
    return res;
  }
  VT simplex(vector<VT> &AA,VT &bb,VT &cc){
    int n=AA[0].size(),k;
    m=AA.size(); k=n+m+1; kt.resize(m); b=bb; c=cc; c.resize(n+m);
    A=AA; REP(i,m){ A[i].resize(k); A[i][n+i]=1; A[i][k-1]=-1; kt[i]=n+i;}
    N=VI(k,1); REP(i,m) N[kt[i]]=0;
    int pos=min_element(ALL(b))-b.begin();
    if (b[pos]<-EPS){ 
      c=VT(k,0); c[k-1]=-1; pivot(k,pos,k-1); res=doit(k);
      if (res[k-1]>EPS) return VT();
      REP(i,m) if (kt[i]==k-1)
          REP(j,k-1) if (N[j] && (A[i][j]<-EPS || EPS<A[i][j])){
            pivot(k,i,j); break;
          }
      c=cc; c.resize(k,0); REP(i,m) REP(j,k) if (N[j]) c[j]-=c[kt[i]]*A[i][j];
    }
    res=doit(k-1); if (!res.empty()) res.resize(n);
    return res;
  }
};
// Struktura opisujaca mozliwy ruch malowania obrazu
struct move {
	char type;
	int lx,ly,hx,hy;
	move(int lx, int ly, int hx, int hy, char type) : lx(lx), ly(ly), hx(hx), hy(hy), type(type) {}
};


int main() {
	int m,n,h,v,s;
// Wczytaj wymiary obrazu oraz czas potrzebny na wykonanie poszczegolych ruchow
	cin >> m >> n >> h >> v >> s;
	vector<move> moves;
	vector<string> paint(m);
// Wczytaj opis obrazu
	REP(x, m) cin >> paint[x];
	vector<long double> c;
// Wygeneruj ruchy stawiania pojedynczej plamy
	REP(x, m) REP(y,n) {
		moves.PB(move(x,y,x,y,'s'));
		c.PB(-s);
	}
// Wygeneruj ruchy malowania pionowych paskow
	REP(x, m) {
		int l = 0;
		FOR(y,1,n)
		if (y==n || paint[x][y] != paint[x][y-1]) {
			moves.PB(move(x,l,x,y-1,'h'));
			c.PB(-h);
			l=y;
		}
	}
// Wygeneruj ruchy malowania poziomych paskow
	REP(y, n) {
		int l = 0;
		FOR(x,1,m)
		if (x==m || paint[x][y] != paint[x-1][y]) {
			moves.PB(move(l,y,x-1,y,'v'));
			c.PB(-v);
			l=x;
		}
	}
// Stworcz ograniczenia dla programowania liniowego wymuszajace, ze kazdy punkt obrazu jest pomacowany
	vector<long double> b(n*m);
	vector<vector<long double> > A(n*m, vector<long double>(SIZE(moves)));
	REP(x, m) REP(y,n) {
		int p = x*n+y;
		b[p] = -1;
		REP(z, SIZE(moves)) {
			A[p][z] = (moves[z].lx <= x && moves[z].ly <= y && moves[z].hx >= x && moves[z].hy >= y) ? -1 : 0;
		}
	}
// Rozwiaz programowania liniowe i wypisz wynik
	vector<long double> res = Simplex::simplex(A, b,c);
	int time = 0, moveC = 0;
	REP(x, SIZE(res)) if ((int) res[x] == 1) {
		moveC++;
		time -= (int) c[x];
	}
	cout << time << " " << moveC << endl;
	REP(x, SIZE(res)) if ((int) res[x] == 1) {
		if (moves[x].type == 's')
			cout << "s " << moves[x].lx+1 << " " << moves[x].hy+1;
		else cout << moves[x].type << " " << moves[x].lx+1 << " " << moves[x].ly+1 << " " << moves[x].hx+1 << " " << moves[x].hy+1;
		cout << " " << paint[moves[x].lx][moves[x].ly] << endl;
	}
	return 0;
}
