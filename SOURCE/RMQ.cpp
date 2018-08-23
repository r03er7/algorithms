#include "szablon.h"

#define MAXN 2000
#define MAXNLOG 10
int n;
int tablica[MAXN];
int RMQ[MAXNLOG][MAXN];
int potega[MAXN];
void rmq_pregen() {
    int y=0;
    int last=1;
    int next=2;
    potega[0]=0;
    while(y<MAXNLOG) {
        FOR(i,last,next-1)potega[i]=y;
        last=next;
        next=next*2;
        ++y;
    }
}
void rmq_gen() {
    REP(x,n)RMQ[0][x]=tablica[x];
    int d=1;
    int shift=1;
    d<<=shift;
    while(d<n) {
        REP(x,n-d+1) {
            RMQ[shift][x]=max(RMQ[shift-1][x],RMQ[shift-1][x+d/2]);
        }
        d=1;
        ++shift;
        d<<=shift;
    }
}
int rmq_querry(int a,int b) {
    int x=potega[b-a];
    return max(RMQ[x][a],RMQ[x][b-(1<<x)+1]);
}
void read_file() {
    FILE *plik=fopen("rmq test.txt","r");
    fscanf(plik,"%d",&n);
    REP(i,n)fscanf(plik,"%d",&tablica[i]);
}
int error=0;
void test() {
    REP(i,n) {
        FOR(j,i,n-1) {
            int res=-INF;
            FOR(x,i,j)res=max(res,tablica[x]);
            if(res!=rmq_querry(i,j))++error;
        }
    }
}
void write_nlgn() {
    REP(j,potega[n]) {
        REP(i,n)printf("%d ",RMQ[j][i]);
        printf("\n");
    }
}
int main() {
    read_file();
    rmq_pregen();
    printf("rmq test\n");
    do {
        rmq_gen();
        test();
    } while(next_permutation(tablica,tablica+n));
    printf(" %d ",error);
    return 0;
}
