#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <stdio.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
#define MP make_pair
#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define FORD(v,p,k) for(int v=p;v>=k;--v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define SIZE(x) (int)x.size()
#define ALL(c) c.begin(),c.end()
#define LL long long
const int INF = 1000000001;
const int MaxM=500000;
const int MAX=100000;
short int colors[MAX];
int a,b,n,m;
int A[MAX];
int U[MAX];
int R[MAX];
vector<int> tablica;
vector<vector<int> > RMQ;
vector<int> potega;
void RMQOnlgn()
{
     n=20;
     tablica.resize(n);
     REP(x,n)tablica[x]=x;


     int k=1;
     int art=0;
     while(k<n) {
          k<<=1;
          ++art;
     }
     potega.resize(n);
     RMQ.resize(n);
     REP(x,n)RMQ[x].resize(art);
     REP(x,n)RMQ[x][0]=tablica[x];

     int d=1;
     int shift=1;
     d<<=shift;

     while(d<n) {
          REP(x,n-d+1) {
               RMQ[x][shift]=max(RMQ[x][shift-1],RMQ[x+d/2][shift-1]);


          }

          d=1;
          ++shift;
          d<<=shift;
     }

     REP(y,n) {
          int art=0;
          int x=y;
          while(x>1) {
               x/=2;
               ++art;
          }
          potega[x]=art;
     }

}
int queryRMQOnlgn(int a,int b)
{
     int x=potega[b-a];
     return max(RMQ[a][x],RMQ[b-(1<<x)][x]);
}
void RMQON()
{int n=20;
potega.resize(n);
RMQ.resize(n);
tablica.resize(n);
//potegi nie wieksze niz n
          REP(y,n) {
          int art=0;
          int x=y;
          while(x>1) {
               x/=2;
               ++art;
          }
          potega[x]=art;
     }
REP(x,n)RMQ[x].resize(potega[n-1]);

     REP(x,n)tablica[x]=x;

     int k=potega[n-1];
     int zz=(2*n)/k;//dlogosc ciagu b
     vector<int> bb(zz);
//rmq dla nowegociagu
     int d=1;
     int shift=1;
     d<<=shift;
     while(d<zz) {
          REP(x,zz-d+1) RMQ[x][shift]=max(RMQ[x][shift-1],RMQ[x+d/2][shift-1]);
          d=1;
          ++shift;
          d<<=shift;
     }

     //warunki brzegowe



}
void preorderdfs(){
//graf nie skierowany sa tylko krawdedzie drzewowe i powtornet


}
int main()
{
     RMQOnlgn();



     return 0;
}
