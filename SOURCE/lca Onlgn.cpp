#include "szablon.h"

#define MAX 1000
#define LOGN 16

VI g[MAX];
int P[LOGN][MAX],pre[MAX],treeSize[MAX];
bool vis[MAX];
VI lista[MAX];
int n,r,from,to,counter=0;

bool potomek(int u,int v) {
    return (pre[u]>=pre[v] && pre[u] < pre[v]+treeSize[v]);
}
int lca(int u,int v) {
    if(potomek(u, v))return v;
    if(potomek(v, u))return u;
    int i=u, j=LOGN-1;
    ///int i=u, j=1;
    while(j>=0) {
        if(potomek(v, P[j][i]))
            j--;
        else
            i = P[j][i];
    }
    return P[0][i];
}

void dfs(int v) {
    counter++;
    pre[v]=counter;
    //vis[v]=true;
    FOREACH(it,g[v])if(!vis[*it]) {
        P[0][*it]=v;
        vis[*it]=true;
        dfs(*it);
    }
    treeSize[v]=counter+1-pre[v];
}
void read_file() {
    FILE *plik=fopen("lca test.txt","r");
    fscanf(plik,"%d%d",&n,&r);
    int a,b;
    REP(i,n-1) {
        fscanf(plik,"%d%d",&a,&b);
        g[a].PB(b);
        g[b].PB(a);
    }
    int cos;
    fscanf(plik,"%d",&cos);
    REP(i,cos) {
        fscanf(plik,"%d%d",&a,&b);
        lista[a].PB(b);
        ///list[b].PB(a);
    }
}
int main() {
    read_file();
    REP(i,n+1) {
        pre[i]=treeSize[i]=0;
        vis[i]=false;
    }
    REP(i,LOGN)
    REP(j,MAX)P[i][j]=0;

    vis[r]=true;
    dfs(r);
    P[0][r]=1;

    FOR(i,1,LOGN-1)
    FOR(j,1,MAX-1)
    P[i][j]=P[i-1][P[i-1][j]];
    printf("\n");
    REP(j,16) {
        REP(i,n+1)printf("%d ",P[j][i]);
        printf("\n");
    }
    printf("\n");

    REP(i,n+1)printf("%d ",i);
    printf("\n");
    REP(i,n+1)printf("%d ",pre[i]);
    printf("\n");
    REP(i,n+1)printf("%d ",treeSize[i]);
    printf("\n");
    REP(i,MAX)
    FOREACH(it,lista[i])
    printf("\n {%d %d} %d",i,*it,lca(i,*it));
    return 0;
}
