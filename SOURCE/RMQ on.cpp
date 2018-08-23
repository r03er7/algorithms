#include "szablon.h"
int n;
vector<int> tablica;
vector<vector<int> > RMQ;
vector<int> potega;
void rmq_gen() {
    int k=1;
    int art=0;//logarytm
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
        potega[y]=art;
    }
}
int rmq_querry(int a,int b) {
    ///if(a==b)return tablica[a];
    //a<=b
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
    ///printf("permutacja ");
    //FOREACH(it,tablica)printf("%d ",*it);

    rmq_gen();
    //printf("\n");
    REP(i,n) {
        //printf("\n");
        FOR(j,i,n-1) {
            ///printf("(%d,%d) ",i,j);
            ///printf("%d ",rmq_querry(i,j));
            int res=-INF;
            FOR(x,i,j)res=max(res,tablica[x]);
            //printf("%d ",res);
            if(res!=rmq_querry(i,j)) {
                ++error;
                printf("ERROR");
            }

        }
    }
    ///printf("\n");
}
void write_nlgn() {
    /*
          REP(j,art) {
         REP(i,n)printf("%d ",RMQ[i][j]);
         printf("\n");
          }
          */
}
int main() {
    read_file();
    ///RMQOnlgn();
    printf("rmq test\n");
    do {
        //FOREACH(it,tablica)printf("%d ",*it);
        //printf("\n");
        test();
    } while(next_permutation(ALL(tablica)));
    printf(" %d ",error);
    return 0;
}
