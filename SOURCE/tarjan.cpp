#include "szablon.h"
#define MAXN 100
///double x = 6861738402706e-91, y;
vector<int> rank,parent,ancestor,color,lista[MAXN],g[MAXN];
int n,r;
void makeset(int x) {
    parent[x]=x;
    rank[x]=0;
}
int find(int x) {
    if (parent[x] == x)
        return x;
    else
        return parent[x] = find(parent[x]);
}
void unin(int a, int b) {
    a = find(a);//znajduje reprezentanta a
    b = find(b);//znajduje reprezentanta b
    if (a!=b) {//ten sam reprezentant sa juz union
        if (rank[a] < rank[b])//jesli moc spojnej reprezentanta b jest wieksza(-1)
            swap(a,b);
        rank[a]+=rank[b]+1;//sumowanie mocy
        parent[b] = a;//0 mniejszej ilcznosci wzkazuje teraz na reprezentanta
    }
}
//http://en.wikipedia.org/wiki/Tarjan's_off-line_lowest_common_ancestors_algorithm
void tarjanOlaca(int u,int par) {
    makeset(u);
    ancestor[u]=u;
    color[u]=0;//bialy
    FOREACH(it,g[u])if(*it!=par) {
        tarjanOlaca(*it,u);
        unin(*it,u);
        ancestor[find(u)]=u;
    }
    color[u]=1;//black
    FOREACH(it,lista[u])if(color[*it]==1) {
        printf("\n {%d %d} %d",u,*it,ancestor[find(*it)]);
    }
}
void print() {
    FOREACH(it,rank)printf("%d ",*it);
    printf("\n");
    FOREACH(it,parent)printf("%d ",*it);
    printf("\n");
}
void read_file() {
    FILE *plik=fopen("tarjan test.txt","r");
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
        lista[b].PB(a);
    }
    ///REP(i,n)debug(a[i]);
}
int main() {
    ///  return(*(char*)&x?x*=y=x,main():printf((char*)&y));
    n=100;//liczba spojnych
    rank.resize(n);
    parent.resize(n);
    ancestor.resize(n);
    color.resize(n);
    REP(i,n)makeset(i);
    /*   print();
       unin(1,2);
       unin(3,7);
       unin(4,6);
       unin(1,8);
    */
    //print();
    read_file();
    tarjanOlaca(r,0);
    return 0;
}
