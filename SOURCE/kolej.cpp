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

//int colors[MAX];
//int s[MAX],in[MAX],out[MAX];
//int temp;//aktualny czas przetworzenia
//int B[MAX];
//int L[MAX];
//krawedzie lasu rospinajacego
void BuildA()
{
     scanf("%d",&n);
     REP(x,n) {
          scanf("%d",&A[x]);
          --A[x];
     }
}
/*void BuildL()
{
     REP(x,n)R[x]=-1;
     int next=0;
     REP(i,n) {
          R[A[i]]=i;
          while((next<n)&&(R[next]!=-1)) {
               L[R[next]]=i;
               ++next;
          }
     }
}*/
void BuildU() //next
{
     int m=n;
     FORD(i,n-1,0) {
          U[i]=m;
          if (m>A[i]) m=A[i];

     }

}
struct LTree {
     LTree* left;
     LTree* right;
     int key;
     int dist;
};
inline LTree* singleton(int x)
{
     LTree* ret = new LTree;
     ret->key   = x;
     ret->dist  = 1;
     ret->left  = NULL;
     ret->right = NULL;
     return ret;
}
inline int getMin(struct LTree* t)
{
     return t->key;//(t==NULL)?(0):(d->key);
}
inline int getDist(struct LTree* t)
{
     return (t==NULL)?(0):(t->dist);
}
LTree* merge(LTree* a, LTree* b)
{
     if (a==NULL) return b;
     if (b==NULL) return a;
     // a!=NULL && b!=null
     if (getMin(b)<getMin(a)) swap(a,b);
     a->left = merge(a->left,b);
     if (getDist(a->left) > getDist(a->right) ) swap(a->right,a->left);
     if (a->right==NULL) a->dist = 0;
     else a->dist = 1+a->right->dist;
     return a;
}
LTree* delMin(LTree* d)
{
     if (d!=NULL) {
          LTree* tmp = merge(d->left,d->right);
          free(d);
          return tmp;
     }
     return NULL;
}
inline bool isEmpty(LTree* d)
{
     return (d==NULL);
}
inline void deLTree(struct LTree* t)
{
     if (t==NULL) return;
     deLTree(t->left);
     deLTree(t->right);
     free(t);
}

stack<struct LTree*> SSheap;		/* stos spojnych skladowych */
vector<vector<int> > edges;
void dfs2(){

int c0=0;
     REP(x,n)colors[x]=-1;
     REP(vs,n)if(colors[vs]==-1) {
          colors[vs]=c0;
          c0^=1;

          REP(x,SIZE(edges[vs])) {
               if(colors[edges[vs][x]]==-1)colors[edges[vs][x]]=c0;
          }
          c0^=1;
     }

}
void dfs(int t,int c)
{
     colors[t]=c;
     REP(s,edges[t].size()) if (colors[edges[t][s]]<0) dfs(edges[t][s],c^1);
}
void BuildSolution()
{
     struct LTree* nxt;
     struct LTree* tmp;
     edges.resize(n);
     int f;
     REP(x,n) {
          nxt=singleton(A[x]);
          //laczenie
          while (!SSheap.empty()) {
               tmp = SSheap.top();
               f=getMin(tmp);
               if (f<A[x]) {
                    edges[x].PB(R[f]);
                    edges[R[f]].PB(x);
                    nxt=merge(nxt,tmp);
                    SSheap.pop();
               } else break;
          }
          SSheap.push(nxt);
//pierwszya ss na stosie trzeba uaktualnic
          while (!SSheap.empty()) {
               tmp = SSheap.top();
               SSheap.pop();
               while ((tmp!=NULL) && getMin(tmp)<U[x]) tmp=delMin(tmp);
               if (tmp!=NULL) {
                    SSheap.push(tmp);
                    break;
               }
          }
     }

     REP(t,n) colors[t]=-1;
     REP(t,n) if (colors[t]<0) dfs(t,0);

}

stack<int> st[2];	///* stosy do zdejmowania
int c=0;
// zdejmuje ze stosow tyle, ile mozna
void flush()
{
     int flag;
     for(;;) {
          flag = 1;
          REP(t,2) if (st[t].top()==c) {
               c++;
               st[t].pop();
               flag = 0;
          }
          if (flag) break;
     }
}

// sprawdza, czy zbudowane rozwiazanie jest poprawne
bool checkSolution()
{
     REP(i,2) st[i].push(n+2);
     REP(i,n) {
          st[colors[i]].push(A[i]);
          flush();
     }
     return (c>=n);
}
inline void BuildAnswer()
{
     if (checkSolution()) {
          printf("TAK\n");
          REP(i,n) printf("%s%d",(i)?" ":"",colors[i]+1);
          printf("\n");
     } else
          printf("NIE\n");
}
/*
bool check()
{REP(x,n)
REP(y,SIZE(edges[x]))
if(colors[edges[x][y]]==colors[x])return 0;


     return 1;
}


void ans()
{
    if(!check())printf("NIE");
     else {printf("TAK\n");
     REP(x,n)printf("%d ",colors[x]+1);
     }
}*/
int main()
{
     BuildA();
     // BuildL();
     BuildU();
     BuildSolution();
//ans();
     BuildAnswer();
     return 0;
}
