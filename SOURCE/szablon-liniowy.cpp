/* Zadanie SZA (Szablon)
 * Autor: Jakub Radoszewski
 * Data: 15.06.2005
 * Program o z�o�ono�ci czasowej i pami�ciowej O(n),
 * obliczaj�cy d�ugo�ci szablon�w on-line.
 */

#include<cstdio>
#include<string>
using namespace std;

#define MAX_LEN 500000

/* Deklaracje zmiennych globalnych. */
int pref_suf[MAX_LEN + 1]; // Tablica d�ugo�ci najd�u�szych prefikso-sufiks�w
                           // (tak zwana funkcja prefiksowa).
char sl[MAX_LEN];          // Rozwa�ane s�owo.
int n;                     // D�ugo�� rozwa�anego s�owa.

int zakres[MAX_LEN + 1],   // Zakresy s�owa, kt�re mo�na pokry� poszczeg�lnymi
                           // prefiksami s�owa, jako szablonami.
szablony[MAX_LEN + 1];     // Najkr�tsze szablony dla kolejnych
                           // prefiks�w s�owa.


/* Procedura wyliczaj�ca warto�ci funkcji prefiksowej
 * dla podanego w parametrze s�owa.
 * Zak�adamy przy tym dla u�atwienia, �e
 * litery s�owa s� numerowane od jedynki (czyli litera
 * zerowa s�owa jest nieznacz�ca). */
void licz_pref_suf(string slowo)
{
	int k = 0;
  
  /* Inicjalizacja funkcji prefiksowej. */
	pref_suf[0] = pref_suf[1] = 0;
  
  /* Wyliczanie kolejnych warto�ci funkcji prefiksowej. */
	for (int q = 2; q <= n; q++)
	{
    /* Niezmiennik: najd�u�szy prefikso-sufiks prefiksu danego
    s�owa o d�ugo�ci q ma d�ugo�� k. */
		while (k > 0 && slowo[k + 1] != slowo[q])
      k = pref_suf[k];
		if (slowo[k + 1] == slowo[q])
      k++;
		pref_suf[q] = k;
	} /* for */
} /* licz_pref_suf */


int main()
{
  /* Odczyt s�owa i wyliczenie funkcji prefiksowej. */
  scanf("%s", sl);
  n = strlen(sl);
  licz_pref_suf('a' + string(sl));

  /* Obliczanie najkr�tszych szablon�w dla prefiks�w s�owa,
  wykonywane on-line. */
  for (int j = 1; j <= n; j++)
    szablony[j] = zakres[j] = j;

  /* P�tla po wszystkich, d�u�szych ni� jeden, prefiksach
  danego s�owa - w j-tym kroku rozwa�amy j-ty prefiks. */
  for (int j = 2; j <= n; j++)
  {
    int b = pref_suf[j];
    if (b > 0)
    {
      /* Sprawdzamy, czy najkr�tszy szablon najd�u�szego prefikso-sufiksu
      danego prefiksu s�owa jest dobrym szablonem dla aktualnego
      prefiksu: */
      int q = szablony[b];
      if (zakres[q] >= j - q)
      {
        /* je�eli tak, to wybieramy jego jako szablon, */
        szablony[j] = q;
        zakres[q] = j;
      } /* if */
      /* je�eli nie, to ju� jest ustawione szablony[i]=i. */
    } /* if */
  } /* for */
  
  /* Wypisanie wyniku */
  printf("%d\n", szablony[n]);
  return 0;
} /* main */
