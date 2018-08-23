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
int s[MAX],in[MAX],out[MAX]; //s-przodek, in/out-czas wejścia/wyjścia
int a,b,n,m; //n-wierzchołków, m-krawędzi
int temp;//aktualny czas przetworzenia
void DfsV(int vs){
in[vs]=++temp;

	FOREACH(it,V[vs])if(s[*it]==-1){//nie odwiedzony
			s[*it]=vs;
			DfsV(*it);
		}
	out[vs]=++temp;
}
void DfsR(int e=-1){
temp=-1;
int b=0;
REP(i,n)in[i]=out[i]=s[i]=-1;
REP(i,n)if(s[i]==-1){DfsV(i);//FOR(x,b,e) e=SIZE(g)-1:b=e)
	//	s[i]=0;
		}
}
void Dfs(int e=-1){
    VI st(n);// SIZE(v) stack <data> S;
	int t=-1,i=0,b=0;
	REP(i,n)in[i]=out[i]=s[i]=-1;

	FOR(vs,b,n)if(in[i]==-1){
	in[st[i++]=vs]=++t;
	out[vs]=SIZE(V[vs]);//llicznik nie przerobionych krawedzi
	while(i){//dopuki st nie pusty
	int vs=st[i-1];
	if(!out[vs]){
	out[vs]=++t;//nie ma wiecej krawdezi
	--i;
	}else
	{
	if(in[vs=V[vs][--out[vs]]]==-1){
	s[vs]=st[i-1];
	out[vs]=SIZE(V[vs]);
	in[st[i++]=vs]=++t;
	}
	}

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
		//if(s[i]==-1) printf("%d. brak ścieżki\n",i);
		//else
		printf("%d. %d  %d   %d\n",i,in[i],out[i],s[i]);
}
int main(){

buildV();
	DfsR();
	VVrite();
	return 0;
}
