/* Funkcja LOW, punkty artykulacji i mosty.
 * Zlozonosc: O(V+E).
 * Graf musi byc spojny, zeby to mialo sens!
 * UWAGA: Slabo przetestowane, ale raczej dziala.
 */

#define MAX_N 100001

/* Graf */
int n;
VI t[MAX_N];

/* Pkty artykulacji */
VI pkty;
int d[MAX_N],low[MAX_N];
int nr=1;

#define most(v1,v2) printf("most: %d %d\n",v1+1,v2+1);

/* Funkcja LOW, punkty artykulacji i mosty.
 * 
 * LOW(v) to minimum z numerow preorder wezlow, do ktorych da sie
 * dojsc z v inaczej niz przez par(v). 
 *
 * Wywolanie: dfs(0,-1)
 * */
void dfs(int v,int par)
{
	int ile=0,pkt_art=false;
  low[v]=d[v]=nr++;
	FOREACH(it,t[v]) if (*it!=par)
  {
    if (!d[*it])
    {
      dfs(*it,v);
      ile++;
      low[v]=min(low[v],low[*it]);
      if (par!=-1 && low[*it]>=d[v]) pkt_art=true;
      if (low[*it]>d[v]) most(v,*it); /* most */
    }
    else low[v]=min(low[v],d[*it]);
  }
	if (par==-1 && ile>1) pkt_art=true;
	if (pkt_art) pkty.PB(v); /* punkt artykulacji */
}
