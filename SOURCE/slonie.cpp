#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <stack>
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
int const INF=1000000;
int const K=22;

#define MAXN 1000000

int wagi[MAXN];
int orig[MAXN]; // orig[i] = kto stal na pozycji i
int perm[MAXN]; // slon i ma wyladowac na pozycji slonia perm[i]
bool vis[MAXN]; // nalezy do juz zbadanego cyklu

int minw = INF; // minimalna waga
vector<vector<int> > cykle(MAXN);

int main()
{int ile=-1;
	int N=6;
/*


	scanf("%d", &N);
	REP(a, N)
	{
		scanf("%d", &wagi[a]);
		minw = min(minw, wagi[a]);
	}
	REP(a, N)
	{
		scanf("%d", &orig[a]);
		--orig[a];
	}
	REP(a, N)
	{vis[a]=0;
		int nr;
		scanf("%d", &nr);
		--nr;
		perm[nr] = orig[a];
	}
*/


int a[]={1 ,4 ,5 ,3 ,6 ,2};
int b[]={5 ,3 ,2, 4 ,6 ,1};
int r1[6];
REP(x,N){vis[x]=0;--a[x];--b[x];
r1[a[x]]=x;
}

	REP(x,N){cout<<1;
	if(!vis[x]){

	int c=x;
	vis[c]=1;
cykle[++ile].PB(x);


while(1){


c=b[r1[c]];
if(c==x)break;
cykle[ile].PB(c);
vis[c]=1;

cout<<2;
}

	}
	}
	cout<<3<<endl;;

REP(x,N){
	cout<<endl;
	FOREACH(it,cykle[x])
	cout<<*it+1<<" ";}


	return 0;
}
