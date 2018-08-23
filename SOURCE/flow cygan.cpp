#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
using namespace std;
//ala dynic
const int INF = 1000000001;
const int N=500;
vector<int> krawedzie[N];
vector<int>::iterator poczatek[N];
int przepustowosc[N][N], odleglosc[N], q[N];

void AddEdge(int a,int b,int c){
  przepustowosc[a][b]+=c;
  krawedzie[a].push_back(b);
  krawedzie[b].push_back(a);
}

int bfs(int s,int t,int n){
  for (int i=0; i<n; ++i) odleglosc[i]=-1;
  odleglosc[s]=0;
  int beg=0,end=0;
  q[end++]=s;
  while (beg<end){
    int v=q[beg++];
    for (vector<int>::iterator it=krawedzie[v].begin(); it!=krawedzie[v].end(); ++it)
      if (przepustowosc[v][*it]>0 && odleglosc[*it]==-1){
        odleglosc[*it]=odleglosc[v]+1;
        q[end++]=*it;
      }
  }
  return odleglosc[t]!=-1;
}

int dfs(int x,int t,int minimum){
  int res=0;
  if (x==t || minimum==0) return minimum;
  //UWAGA: it jest referencja!!!
  for(vector<int>::iterator &it=poczatek[x];it!=krawedzie[x].end(); ++it){
    if (odleglosc[x]+1==odleglosc[*it] && przepustowosc[x][*it]>0){
      int y=dfs(*it,t,min(minimum,przepustowosc[x][*it]));
      //odwracamy czesc przepustowosci
      przepustowosc[x][*it]-=y;
      przepustowosc[*it][x]+=y;
      minimum-=y; res+=y;
      if (minimum==0) break;
    }
  }
  return res;
}

int Maxflow(int s,int t,int n){
  int res=0;
  while (bfs(s,t,n)){
    for (int i=0; i<n; ++i) poczatek[i]=krawedzie[i].begin();
    res+=dfs(s,t,INF);
  }
  return res;
}

int main(){
  int n=4;
  AddEdge(0,1,2);
  AddEdge(1,2,3);
  AddEdge(2,3,4);
  AddEdge(0,2,10);
  AddEdge(1,3,8);
  int res=Maxflow(0,3,n);
  printf("Maksymalny przeplyw wynosi %d\n",res);
  return 0;
}
