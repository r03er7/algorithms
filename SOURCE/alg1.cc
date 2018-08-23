#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

#include <iomanip>
using namespace std;
typedef vector<int> VI;
typedef long long LL;
typedef long double LD;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) __typeof(n) v = (n)
#define VAL(i,v) __typeof(v) i=(v)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
#define MAXN  (1<<21)
///2000004
int n,a,b,N;
LL load[2*MAXN];
int  sub[2*MAXN];
int sub1[2*MAXN];
int load1[2*MAXN];
struct Pkt {
    int x;
    int y;
    bool id;
    bool operator <(const Pkt &p) const {
        return x<p.x || (x==p.x && id<p.id);//konce poczatki
    }
};
Pkt *pkt=new Pkt[2*MAXN];
void insert(int a, int b, int v) {
    int l=N+a,r=N+b;
    int length = 1;
    load[l] += v;
    sub[l] += v;
    if(r != l) {
        load[r] += v;
        sub[r] += v;
    }
    while(l >= 1) {
        if(l<r-1) {
            if(l%2==0) { //l jest lewym synem swego ojca
                load[l + 1] += v;
                sub[l + 1] += v * length;
            }
            if(r%2==1) { //r jest prawym synem swego ojca
                load[r - 1] += v;
                sub[r - 1] += v * length;
            }
        }
        if(r < N) {
            sub[l] = sub[2 * l] + sub[2*l+1]+ load[l] * length;
            sub[r] = sub[2 * r] + sub[2*r+1]+ load[r] * length;
        }
// przechodzimy poziom wy¿ej
        l /= 2;
        r /= 2;
        length *= 2;
    }
}
LD query(int a, int b) {
    int l=N+a,r=N+b;
    int length = 1;
    int llen=1,rlen=(a!=b?1:0);
    LD res = 0;
    while(l >= 1) {
        res += (LD)llen * load[l] + (LD)rlen * load[r];
        if(l<r-1) {
            if(l % 2 == 0) { // l jest lewym synem swego ojca
                res += sub[l + 1];
                llen += (LD)length;
            }
            if(r % 2 == 1) { // r jest prawym synem swego ojca
                res += sub[r - 1];
                rlen += (LD)length;
            }
        }
// przechodzimy poziom wy¿ej
        l /= 2;
        r /= 2;
        length *= 2;
    }
    return res;
}
void insert1(int a, int b, int v) {
    int l=N+a,r=N+b;
    int length = 1;
    load1[l] += v;
    sub1[l] += v;
    if(r != l) {
        load1[r] += v;
        sub1[r] += v;
    }
    while(l >= 1) {
        if(l<r-1) {
            if(l%2==0) { //l jest lewym synem swego ojca
                load1[l + 1] += v;
                sub1[l + 1] += (LL)v * length;
            }
            if(r%2==1) { //r jest prawym synem swego ojca
                load1[r - 1] += v;
                sub1[r - 1] += (LL)v * length;
            }
        }
        if(r < N) {
            sub1[l] = sub1[2 * l] + sub1[2*l+1]+ load1[l] * length;
            sub1[r] = sub1[2 * r] + sub1[2*r+1]+ load1[r] * length;
        }
// przechodzimy poziom wy¿ej
        l /= 2;
        r /= 2;
        length *= 2;
    }
}
LD query1(int a, int b) {
    int l=N+a,r=N+b;
    int length = 1;
    int llen=1,rlen=(a!=b?1:0);
    LD res = 0;
    while(l >= 1) {
        res +=(LD) llen * load1[l] + (LD)rlen * load1[r];
        if(l<r-1) {
            if(l % 2 == 0) { // l jest lewym synem swego ojca
                res += sub1[l + 1];
                llen += length;
            }
            if(r % 2 == 1) { // r jest prawym synem swego ojca
                res += sub1[r - 1];
                rlen += (LD)length;
            }
        }
// przechodzimy poziom wy¿ej
        l /= 2;
        r /= 2;
        length *= 2;
    }
    return res;
}
long double zamiataj_x() {
    ///int sol=0;
    long double mianowik=(long double)n*(long double)(n-1);
    mianowik/=2;
    long double solor=0.L;
    LL pun;
    LL pole;
    REP(i,2*n) {
        if(pkt[i].id==0) {
            //usuwanie
            insert(pkt[i].y,pkt[i].y+b-1,-(pkt[i].x));
            insert1(pkt[i].y,pkt[i].y+b-1,-1);
        } else {
            //dodawanie
            pole=query(pkt[i].y,pkt[i].y+b-1);//,pkt[i].x+a);
            pun=query1(pkt[i].y,pkt[i].y+b-1);
            ///     sol+=(pole-pkt[i].x*pun);
            long double xx=(long double)pole-(long double)pkt[i].x*(long double)pun;
            solor+=xx;//(pole-pkt[i].x*pun)/mianowik;
            insert(pkt[i].y,pkt[i].y+b-1,pkt[i].x+a);
            insert1(pkt[i].y,pkt[i].y+b-1,1);

        }
    }
    ///printf("%lf\n",solor/mianowik);
    return solor/mianowik;
}

void readf() {
    FILE *plik=fopen("kocyki.txt","r");
    fscanf(plik, "%d", &n);
    fscanf(plik, "%d", &a);
    fscanf(plik, "%d", &b);
    REP(i,n) {
        fscanf(plik,"%d",&pkt[i].x);
        fscanf(plik,"%d",&pkt[i].y);
        pkt[i].id=1;

        pkt[n+i].x=pkt[i].x+a;
        pkt[n+i].y=pkt[i].y;
        pkt[n+i].id=0;
    }
    N=MAXN;
}
void read() {
    scanf("%d",&n);
    scanf("%d",&a);
    scanf("%d",&b);
    REP(i,n) {
        scanf("%d",&pkt[i].x);
        scanf("%d",&pkt[i].y);
        pkt[i].id=1;

        pkt[n+i].x=pkt[i].x+a;
        pkt[n+i].y=pkt[i].y;
        pkt[n+i].id=0;
    }
    N=MAXN;
}
int main() {

    //readf();
    read();
    sort(pkt,pkt+n+n);
    long double ress=zamiataj_x();
   /// printf("%Lf\n",ress); //long double
    ///printf("%.3Lf\n",1/ress); //long double
    cout<<(LD)ress;
    return 0;
}
