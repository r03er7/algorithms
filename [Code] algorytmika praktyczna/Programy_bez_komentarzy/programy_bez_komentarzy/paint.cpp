#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef long long LL;

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
const double EPS = 10e-9;
namespace Simplex{
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
struct move {
	char type;
	int lx,ly,hx,hy;
	move(int lx, int ly, int hx, int hy, char type) : lx(lx), ly(ly), hx(hx), hy(hy), type(type) {}
};


int main() {
	int m,n,h,v,s;
	cin >> m >> n >> h >> v >> s;
	vector<move> moves;
	vector<string> paint(m);
	REP(x, m) cin >> paint[x];
	vector<long double> c;
	REP(x, m) REP(y,n) {
		moves.PB(move(x,y,x,y,'s'));
		c.PB(-s);
	}
	REP(x, m) {
		int l = 0;
		FOR(y,1,n)
		if (y==n || paint[x][y] != paint[x][y-1]) {
			moves.PB(move(x,l,x,y-1,'h'));
			c.PB(-h);
			l=y;
		}
	}
	REP(y, n) {
		int l = 0;
		FOR(x,1,m)
		if (x==m || paint[x][y] != paint[x-1][y]) {
			moves.PB(move(l,y,x-1,y,'v'));
			c.PB(-v);
			l=x;
		}
	}
	vector<long double> b(n*m);
	vector<vector<long double> > A(n*m, vector<long double>(SIZE(moves)));
	REP(x, m) REP(y,n) {
		int p = x*n+y;
		b[p] = -1;
		REP(z, SIZE(moves)) {
			A[p][z] = (moves[z].lx <= x && moves[z].ly <= y && moves[z].hx >= x && moves[z].hy >= y) ? -1 : 0;
		}
	}
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
