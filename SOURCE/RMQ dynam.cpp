#include "szablon.h"
#define MAXN 2000
#define MAXNLOG 10

int n;
vector<int> tablica;
vector<vector<int> > RMQ;
vector<int> potega;
void rmq_pregen() {
    potega.resize(MAXN);
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
    int art=potega[n];
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
}
int rmq_querry(int a,int b) {
    int x=potega[b-a];
    return max(RMQ[a][x],RMQ[b-(1<<x)+1][x]);
}
void RMQON() {//sprytne
    ///int n=20;
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
void read_file() {
    FILE *plik=fopen("rmq test.txt","r");
    fscanf(plik,"%d",&n);
    tablica.resize(n);
    REP(i,n) {
        int a;
        fscanf(plik,"%d",&a);
        tablica[i]=a;
    }
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
        REP(i,n)printf("%d ",RMQ[i][j]);
        printf("\n");
    }
}
int main() {
    read_file();
    rmq_pregen();
    do {
        rmq_gen();
        test();
    } while(next_permutation(ALL(tablica)));
    printf(" %d ",error);
    return 0;
}
