#include "szablon.h"
#define ILE_LICZB 9
#define PUSTE -1.0
//newton[n][k] = symbol newtona; liczba podzbiorów k-elementowych zbioru n-elementowego.
int newton [ILE_LICZB+1][ILE_LICZB+1];
//pr_sukc[k] prawdopodobienstwo sukcesu naszej strategii dla k liczb
void gen_newton () {
    FOR(i,0,ILE_LICZB) {
        newton [i][0] = 1;
        newton [i][i] = 1;
        FOR(j,1,i-1)
        newton [i][j] = newton [i - 1][j - 1] + newton [i - 1][j];
    }
}
int main() {
    gen_newton();
    printf("%d",newton[6][2]);
    return 0;
}
