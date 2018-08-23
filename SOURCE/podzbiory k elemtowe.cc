#include "szablon.h"
void podzial(int k,int n) {
    VI aa;
    REP(i,n)aa.PB(i+1);
    VI vec(n,0);
    FOR(i,k,n)vec[i]=1;
    int c=-1;
    do {
        printf("\n%d\t",++c);
        ///FOREACH(it,vec)
        REP(i,SIZE(vec))
        if(vec[i])printf(" %d",aa[i]);
    } while(next_permutation(ALL(vec)));
}
int main() {
    podzial(4,6);
    return 0;
}
