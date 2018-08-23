#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <queue>
#include <list>
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
#define PF push_front
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
void BuildA()
{
     scanf("%d",&n);
     REP(x,n) {
          scanf("%d",&A[x]);
          --A[x];
     }
}
void BuildU() //next
{
     int m=n;
     FORD(i,n-1,0) {
          U[i]=m;
          if (m>A[i]) m=A[i];

     }

}

struct waz {
     list<int> red;
     list<int> blu;
};
inline waz* sing(int x)
{
     waz* ret = new waz;
     ret->red.PF(x);
     return ret;
}
inline bool isEmpty(waz* d)
{
     return (d->blu.empty&&d->red.empty);
}
inline int geMin(struct waz* t)
{
     if(isEmpty(t)) return -1;
     else if(t->red.empty())return t->blu.front();
     else if (t->blu.empty())return t->red.front();
     else
          return min(t->blu.front(),t->red.front());
}

waz* merge(waz* a, waz* b,bool wyn)
{
     if (isEmpty(a)) return b;
     if (isEmpty(b)) return a;

     if (getMin(b)<getMin(a)) swap(a,b);
     a->left = merge(a->left,b);
     if (getDist(a->left) > getDist(a->right) ) swap(a->right,a->left);
     if (a->right==NULL) a->dist = 0;
     else a->dist = 1+a->right->dist;
     return a;
}
waz* merge(waz* a, waz* b)
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
waz* delMin(waz* d)
{
     if (d!=NULL) {
          LTree* tmp = merge(d->left,d->right);
          free(d);
          return tmp;
     }
     return NULL;
}
inline bool isEmpty(waz* d)
{
     return (d->blu.empty&&d->red.empty);
}
inline void deLTree(struct LTree* t)
{
     if (t==NULL) return;
     deLTree(t->left);
     deLTree(t->right);
     free(t);
}

stack<struct waz*> heap;		/* stos spojnych skladowych */
vector<vector<int> > edges;
void dfs(int t,int c)
{
     colors[t]=c;
     REP(s,edges[t].size()) if (colors[edges[t][s]]<0) dfs(edges[t][s],c^1);
}
void BuildSolutionOn()
{
     struct waz* nxt;
     struct waz* tmp;
     edges.resize(n);
     int f;
     REP(x,n) {
          nxt=sing(A[x]);
          //laczenie
          while (!heap.empty()) {
               tmp = SSheap.top();
               f=getMin(tmp);
               if (f<A[x]) {
                    edges[x].PB(R[f]);
                    edges[R[f]].PB(x);
                    nxt=merge(nxt,tmp);
                    heap.pop();
               } else break;
          }
          heap.push(nxt);
//pierwszya ss na stosie trzeba uaktualnic
          while (!heap.empty()) {
               tmp = heap.top();
               heap.pop();
               while ((tmp!=NULL) && geMin(tmp)<U[x]) tmp=delMin(tmp);
               if (tmp!=NULL) {
                    heap.push(tmp);
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


inline void BuildAnswer()
{
     if (checkSolution()) {
          printf("TAK\n");
          REP(i,n) printf("%s%d",(i)?" ":"",colors[i]+1);
          printf("\n");
     } else
          printf("NIE\n");
}

int main()
{
     // BuildA();
     // BuildL();
     // BuildU();
     //BuildSolution();
//ans();
    // BuildAnswer();

          return 0;
}
