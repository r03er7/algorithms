#include "szablon.h"
#define MAXN 100

int n=8;
int parents[] = {-1,0,1,1,0,0,5,5};
VI g[MAXN];
string names[] = {"Root","SubB","LEAF1","LEAF2","LEAF3","SubA","LEAF4","LEAF5"};


void dfs_(int cur,int poz,VI kreski,int nr) {
    string s;
    REP(i,poz)s+=" ";
    REP(i,SIZE(kreski))s[kreski[i]]='|';
    s+="+-";
    s+=names[cur];
    cout<<s<<endl;
    REP(i,SIZE(g[cur])) {
        int bro=g[cur][i];
        VI tit(kreski);
        if(parents[cur]!=-1&&nr<SIZE(g[parents[cur]])-1) //ma jeszcze brata to dopisz preske;
            tit.PB(poz);
        dfs_(bro,poz+2,tit,i);

    }
}
int main() {
    int root;
    REP(i,n)if(parents[i]!=-1)g[parents[i]].PB(i);
    else root=i;
    REP(i,n)sort(ALL(g[i]));
    VI tt;
    dfs_(root,0,tt,-1);
    return 0;
}
