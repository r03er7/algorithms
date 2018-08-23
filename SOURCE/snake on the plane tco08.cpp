// {{{

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

#include <stack>

#include <queue>

using namespace std;

#define REP(i,n) for(int i=0;i<(n);++i)

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)

#define FORD(i,a,b) for(int i=(a);i>=(b);--i)

#define FOREACH(it,c) for(typeof((c).begin()) it=(c).begin();it!=(c).end();++it)

#define ALL(c) (c).begin(),(c).end()

#define debug(x) cerr << #x << " = " << x << "\n";

#define debugv(x) cerr << #x << " = "; FOREACH(it,(x)) cerr << *it << ","; cerr << "\n";

typedef long long LL; typedef long double ld;

typedef vector<int> VI; typedef vector<string> VS;

const int INF = 1000000000; const LL INFLL = LL(INF) * LL(INF);

template<class T> inline int size(const T&c) { return c.size(); }

template<class T> T parse(string s) { istringstream i(s); T x; i>>x; return x; }

template<class T> string show(T x) { ostringstream o; o<<x; return o.str(); }

VS split(string s, string del=" ") {

  string w; VS res; s += del[0];

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

  string s; FOREACH(it,v) s += *it; return s;

}

// }}}



int sx,sy;

vector<pair<int,int> > L,R;



bool close2(pair<int,int> a, pair<int,int> b) {

  return abs(a.first-b.first)+abs(a.second-b.second) <=1;

}



bool onedge(pair<int,int> a) {

  return a.first==0 || a.second==0 || a.first==sx-1 || a.second==sy-1;

}



const int MAXV = 256;



int V;

int cap[MAXV][MAXV];



int nrL(int x) { return x+5; }

int nrR(int x) { return x+5+size(L); }



int vis[MAXV];



bool dfs(int x) {

  vis[x]=true;

  if(x==1) return true;

  REP(y,V) if(!vis[y] && cap[x][y]>0) {

    if(dfs(y)) {

      cap[x][y]--;

      cap[y][x]++;

      return true;

    }

  }

  return false;

}



bool aug() {

  REP(i,V) vis[i]=false;

  return dfs(0);

}



int calcFlow() {

  bool progress = false;

  while(aug()) {

    progress=true;

  }

  bool ok = true;

  FOR(a,1,V-1) if(cap[0][a]>0) ok=false;

  if(ok) return 1;

  else if(progress) return 0;

  else return -1;

}



struct SnakesOnAPlane {

  int snakes(vector <string> grid) {

    sy=size(grid); sx=size(grid[0]);

    REP(x,sx) REP(y,sy) if(grid[y][x]=='.') {

      if((x+y)%2==0)

        L.push_back(make_pair(x,y));

      else

        R.push_back(make_pair(x,y));

    }

    V = size(L) + size(R)+5;

    debug(size(L));

    debug(size(R));

    REP(a,size(L)) REP(b,size(R)) if(close2(L[a],R[b])) cap[nrL(a)][nrR(b)]++;

    REP(a,size(L)) cap[0][nrL(a)]+=2;

    REP(a,size(R)) cap[nrR(a)][1]+=2;

    int res = 0;

    REP(a,size(L)) if(onedge(L[a])) cap[nrL(a)][2]++;

    REP(a,size(R)) if(onedge(R[a])) cap[4][nrR(a)]++;

    if(size(L)>size(R)) {

      int A = size(L)-size(R);

      res += A;

      cap[2][1] += 2 * A;

    }

    else if (size(R)>size(L)) {

      int A = size(R)-size(L);

      res += A;

      cap[0][4] += 2 * A;

    }

    for(int iter=0;;++iter) {

      int v = calcFlow();

      if(iter>0 && v==-1) break;

      if(v==1) return res;

      res++;

      ++cap[2][4];

    }

    return -1;

  }

};
