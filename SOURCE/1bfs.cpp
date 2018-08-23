#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <stack>
#include <cstdio>
#include <vector>
#include <queue>
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
int const M=8;//131072;

#define INF 1000000000 //nieskończoność
#define MAX 100000 //maksymalna liczba wierzchołków
using namespace std;
vector <int> V[MAX];
int s[MAX],t[MAX]; //t[]-odległość, s[]-przodek
int a,b,n,m; //n-wierzchołków, m-krawędzi

void BFS(int vs){
	REP(i,n) s[i]=t[i]=-1;//FOREACH(it,V) t[*it]=-1;
	t[vs]=0;
	int qu[n],b,e;//FIFO SIZE(G)
	qu[b=e=0]=vs;
	while(b<=e){
	vs=qu[b++];
	FOREACH(it,V[vs]) if(t[*it]==-1){
	t[qu[++e]=*it]=t[vs]+1;
	s[*it]=vs;
	}
	}
}
void buildV(){
	scanf("%d %d",&n,&m);
	REP(i,m){
		scanf("%d %d",&a,&b);
		V[a].PB(b);
		V[b].PB(a); //graf nieskierowany
	}

}
void VVrite(){
REP(i,n)
		if(t[i]==-1) printf("%d. brak ścieżki\n",i);
		else printf("%d. %d   %d\n",i,t[i],s[i]);
}
int main(){

buildV();
	BFS(1);
	VVrite();
	return 0;
}
