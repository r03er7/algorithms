#include "rwprwzentacja graf.h"


int main()
{
     FILE *plik=fopen("komisja.txt","r");
     int n,m, b, e, k, l;
     char c;
     // cin >>n>>m;
     fscanf(plik, "%d%c", &n, &c);
     fscanf(plik, "%d%c", &m, &c);
     Graph<Vs, Ve> g(2*n);
     REP(x, m) {
          //  cin >> b >> e;
          fscanf(plik, "%d%c", &b, &c);
          fscanf(plik, "%d%c", &e, &c);
          g.EdgeD(b-1, e-1);
     }



     g.SccS();
     vector<bool> inD(n,false), outD(n,false), notEmpty(n,false);
     int inVal = 0, outVal = 0, sccC = 0;

     REP(x, n) {
          if (!notEmpty[g.g[x].t]) {
               notEmpty[g.g[x].t] = true;
               sccC++;
          }
          FOREACH(it, g.g[x]) if (g.g[x].t != g.g[it->v].t)
               outD[g.g[x].t] = inD[g.g[it->v].t] = true;
     }

     REP(x, n) {
          if (!inD[x] && notEmpty[x]) inVal++;
          if (!outD[x] && notEmpty[x]) outVal++;
     }
// Jesli w grafie jest tylko jedna silnie spojna skladowa, to wynikiem jest 0
     if (sccC == 1) inVal = outVal = 0;
// Wypisz wynik
     cout << max(inVal, outVal) << endl;
     return 0;
}

