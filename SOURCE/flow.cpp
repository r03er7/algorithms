#include <cstdio>
#include "szablon.h"
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


const int INF = 1000000001;
const int N=500;
vector<int> krawedzie[N];
vector<int>::iterator poczatek[N];
int przepustowosc[N][N], odleglosc[N], q[N];

void AddEdge(int a,int b,int c) {
    przepustowosc[a][b]+=c;//krotnosc krawedzi
    krawedzie[a].push_back(b);
    krawedzie[b].push_back(a);
}
void print_bfs(int s, int poprawka) {
    int vis[N];
    REP(i,N)vis[i]=0;
    queue<int> q;
    set<string> stuff;
    map<int,string>stu;
    q.push(s);
    vis[s]=1;
    while(!q.empty()) {
        int v=q.front();
        q.pop();
        FOREACH(it,krawedzie[v])if(!vis[*it]) {
            ostringstream ss;
            ss<<"("<<v<<","<<*it<<")="<<przepustowosc[v][*it];
            string str=ss.str();
            stu.insert(MP(100*v+*it,str));
            q.push(*it);
            vis[v]=1;
        }

    }
    cout<<"map  poprawka "<<poprawka<<"\n";
    FOREACH(it,stu)cout<<(*it).ND<<endl;
}
int bfs(int s,int t,int n) {
    for (int i=0; i<n; ++i) odleglosc[i]=-1;
    odleglosc[s]=0;
    int beg=0,end=0;
    q[end++]=s;
    while (beg<end) {
        int v=q[beg++];
        for (vector<int>::iterator it=krawedzie[v].begin(); it!=krawedzie[v].end(); ++it)
            if (przepustowosc[v][*it]>0 && odleglosc[*it]==-1) {
                odleglosc[*it]=odleglosc[v]+1;
                q[end++]=*it;
            }
    }
    return odleglosc[t]!=-1;
}

int dfs(int x,int t,int minimum) {
    int res=0;
    if (x==t || minimum==0) return minimum;
    //UWAGA: it jest referencja!!!
    for(vector<int>::iterator &it=poczatek[x]; it!=krawedzie[x].end(); ++it) {
        if (odleglosc[x]+1==odleglosc[*it] && przepustowosc[x][*it]>0) {
            int y=dfs(*it,t,min(minimum,przepustowosc[x][*it]));
            //odwracamy czesc przepustowosci
            przepustowosc[x][*it]-=y;
            przepustowosc[*it][x]+=y;
            minimum-=y;
            res+=y;
            if (minimum==0) break;
        }
    }
    return res;
}

int Maxflow(int s,int t,int n) {
    int res=0;
    int cos=0;
    while (bfs(s,t,n)) {
        for (int i=0; i<n; ++i) poczatek[i]=krawedzie[i].begin();
        res+=dfs(s,t,INF);
        print_bfs(0,cos++);
    }
    return res;
}

int main() {
    int n=12;
    int s=0;
    int t=11;
//AddEdge(0,1,210);
//AddEdge(1,2,210);
//AddEdge(2,11,210);
      /* test
    AddEdge(0,1,210);
    AddEdge(0,2,210);
    AddEdge(0,3,260);
    AddEdge(0,4,280);
    AddEdge(0,5,340);

    AddEdge(6,11,190);
    AddEdge(7,11,240);
    AddEdge(8,11,230);
    AddEdge(9,11,220);
    AddEdge(10,11,420);

    AddEdge(1,9,70);
    AddEdge(1,10,230);

    AddEdge(2,6,90);
    AddEdge(2,7,210);

    AddEdge(3,9,190);
    AddEdge(3,10,130);

    AddEdge(4,8,200);
    AddEdge(4,10,110);

    AddEdge(5,6,200);
    AddEdge(5,7,70);
    AddEdge(5,8,100);

      */
/*
    AddEdge(0,1,280);
    AddEdge(0,2,250);
    AddEdge(0,3,220);
    AddEdge(0,4,210);
    AddEdge(0,5,270);

    AddEdge(1,9,180);
    AddEdge(1,10,220);

    AddEdge(2,8,210);
    AddEdge(2,10,130);

    AddEdge(3,6,70);
    AddEdge(3,7,60);
    AddEdge(3,8,50);
    AddEdge(3,9,60);

    AddEdge(4,9,60);
    AddEdge(4,10,210);

    AddEdge(5,6,190);
    AddEdge(5,7,130);

    AddEdge(6,11,170);
    AddEdge(7,11,140);
    AddEdge(8,11,190);
    AddEdge(9,11,220);
    AddEdge(10,11,510);
    */
  /*  REP(i,n) {
        printf("\n");
        REP(j,n)printf("(%d,%d)%d\t",i,j,przepustowosc[i][j]);
    }

*/
REP(i,5)AddEdge(0,1+i,INF);
REP(i,5)AddEdge(6+i,11,INF);
AddEdge(1,7,25);
AddEdge(1,8,21);
AddEdge(1,9,18);
AddEdge(1,10,13);

AddEdge(2,6,11);
AddEdge(2,7,28);
AddEdge(2,8,32);
AddEdge(2,9,12);
AddEdge(2,10,11);

AddEdge(3,6,20);
AddEdge(3,7,210);
AddEdge(3,8,19);
AddEdge(3,9,17);
AddEdge(3,10,6);

AddEdge(4,9,19);
AddEdge(4,9,25);

AddEdge(5,6,17);
AddEdge(5,9,12);
    int res=Maxflow(0,11,n);
    printf("Maksymalny przeplyw wynosi %d\n",res);
  /*  REP(i,n) {
        printf("\n");
        REP(j,n)printf("(%d,%d)%d  ",i,j,przepustowosc[i][j]);
    }*/
    return 0;
}
