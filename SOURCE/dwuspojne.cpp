/* Podzial grafu na dwuspojne skladowe.
 * Zlozonosc: O(V+E).
 */

#define MAX_N 100001

int n,nr;
VI t[MAX_N];
int d[MAX_N],low[MAX_N];

/* Dwuspojne: ile - liczba, dwu - listy krawedzi w dwuspojnych */
int ile;
vector<PII> stos,dwu[MAX_N];

void dfs(int v,int par)
{
  low[v]=d[v]=nr++;
	FOREACH(it,t[v]) if (*it!=par)
  {
    if (d[*it]==-1)
    {
      stos.PB(MP(min(v,*it),max(v,*it)));
      dfs(*it,v);
      low[v]=min(low[v],low[*it]);
      if (low[*it]>=d[v])
      {
        do
        {
          dwu[ile].PB(stos.back()); stos.pop_back();
        } while (dwu[ile].back() != MP(min(v,*it),max(v,*it)));
        ile++;
      }
    }
    else
    {
      if (d[v]>d[*it]) stos.PB(MP(v,*it));
      low[v]=min(low[v],d[*it]);
    }
  }
}
								
void visit()
{
  nr=1; ile=0;
	REP(i,n) d[i]=-1;
	REP(i,n) if (d[i]==-1) dfs(i,-1);
}
