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
typedef long double LD;

int main(){
  vector<vector<LD> > A(2,vector<LD>(3));
  vector<LD> b(2),c(3),res;
  A[0][0]=-0.5, A[0][1]=-1, A[0][2]=2, b[0]=-2;
  A[1][0]=1, A[1][1]=2, A[1][2]=0, b[1]=100;
  c[0]=5, c[1]=-1.5, c[2]=0.1;
  res=Simplex::simplex(A,b,c);
  cout << "Najlepsze rozwiazanie : ";
  REP(i,SIZE(res)) cout << "x" << i << " = " << res[i] << "\t";
  cout << endl;
  LD acc=0; REP(i,SIZE(res)) acc+=res[i]*c[i];
  cout << "Wartosc funkcji celu = " << acc << endl;
  return 0;
}
