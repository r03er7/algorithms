/* Jakub Radoszewski
 * Minimalizacja automatu sko�czonego nad alfabetem unarnym
 * Z�o�ono�� czasowa i pami�ciowa: O(n).
 * 
 * U�ycie:
 * liczba_stan�w_automatu stan_pocz�tkowy
 * przej�cia (na co si� przechodzi ze stanu i-tego)
 * typy_stan�w (1-akceptuj�cy, 0-nieakceptuj�cy).
 *
 * Wynik:
 * Dla ka�dego stanu jego numer; te same numery oznaczaj� r�wnowa�ne stany.
 * Numer 0 oznacza stan, kt�ry nie jest osi�galny ze stanu pocz�tkowego.
 */

#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

#define MAX_N 1000000

/* Stany automatu maj� numery 0..n-1. */
int t[MAX_N]; /* tablica przej�� */
bool stany[MAX_N]; /* typy stan�w */
int spocz; /* stan pocz�tkowy */
int n; /* liczba stan�w automatu */

int wynik[MAX_N]; /* numery stan�w (te same numery to stany r�wnowa�ne) */

int pierw; /* d�ugo�� pierwiastka pierwotnego s�owa na cyklu */
int pocz; /* pocz�tek cyklu */
vector<int> cykl; /* 1-akceptuj�cy, 0-nieakceptuj�cy */
int pref_suf[MAX_N]; /* warto�ci funkcji prefiksowej */
int col[MAX_N]; /* tablica pomocnicza */

void odczyt()
{
  scanf("%d%d", &n, &spocz);
  for (int i = 0; i < n; i++)
    scanf("%d", &t[i]);
  for (int i = 0; i < n; i++)
    scanf("%d", &stany[i]);
}


/* Funkcja zwraca pocz�tek cyklu w automacie i wylicza vector cykl,
 * czyli s�owo binarne skonstruowane ze stan�w cyklu. */
int poczatek_cyklu()
{
  memset(col, 0, sizeof(col));
  int poz = spocz;
  while (!col[poz])
  {
    col[poz] = 1;
    poz = t[poz];
  }
  cykl.push_back(0);
  while (col[poz] < 2)
  {
    col[poz] = 2;
    cykl.push_back(stany[poz]);
    poz = t[poz];
  }
  return poz;
}



/* Funkcja liczy funkcj� prefiksow� s�owa z cyklu i zwraca jej warto��
 * na ca�ym s�owie. */
int funkcja_prefiksowa()
{
  pref_suf[0] = pref_suf[1] = 0;
  int k = 0;
  for (int q = 2; q < cykl.size(); q++)
  {
    while (k > 0 && cykl[k + 1] != cykl[q])
      k = pref_suf[k];
    if (cykl[k + 1] == cykl[q])
      k++;
    pref_suf[q] = k;
  }
  return pref_suf[cykl.size() - 1];
}


/* Numerowanie cyklu, czyli grupowanie jego stan�w w stany r�wnowa�ne. */
void numeruj_cykl(int pocz)
{
  int dlugosc = 0;
  while (col[pocz] < 3)
  {
    wynik[pocz] = !(dlugosc % pierw) ? pierw : (dlugosc % pierw);
    dlugosc++;
    col[pocz]= 3;
    pocz = t[pocz];
  }
}


int dlugosc = 0; /* d�ugo�� nawini�tej cz�ci cyklu */

/* Funkcja rekurencyjna, kt�ra numeruje stany ogonka, dop�ki si�
 * ogonek nawija na cyklu. Kiedy przestaje, zaczyna im przypisywa�
 * unikalne numery. */
bool nawin_ogonek(int poz)
{
  if (poz == pocz)
    return true;
  /* Ju� poprzednio si� nie da�o nawin��. */
  if (!nawin_ogonek(t[poz]))
  {
    wynik[poz] = ++pierw;
    return false;
  }
  dlugosc++;
  /* Sprawdzamy, czy si� dobrze odwija. */
  if (stany[poz] != cykl[(pierw - dlugosc % pierw) % pierw])
  {
    wynik[poz] = ++pierw;
    return false;
  } else
  {
    wynik[poz] = pierw - dlugosc % pierw;
    return true;
  }
}

int main()
{
  odczyt();
  pocz = poczatek_cyklu();
  int pref = funkcja_prefiksowa(); /* pref_suf[ca�y_cykl] */
  cykl.erase(cykl.begin());
  if (cykl.size() % (cykl.size() - pref))
    pierw = cykl.size();
  else
    pierw = cykl.size() - pref;
  numeruj_cykl(pocz);
  nawin_ogonek(spocz);
  /* Wypisujemy numery. */
  for (int i = 0; i < n; i++)
    printf("%d ",wynik[i]);
  printf("\n");
  return 0;
}
