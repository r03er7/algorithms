/* Program wykonuj�cy szybkie numerowanie sufiks�w s��w Fibonacciego
 * w porz�dku leksykograficznym i sprawdzanie, czy otrzymany jest
 * ten sam wynik w metodzie brutalnej (sortowanie sufiks�w).
 * Dla n<=20 parzystego metoda si� sprawdza.
 * Autor: Jakub Radoszewski
 */
#include <cstdio>
#include <vector>
#include <string>
#include <utility>
using namespace std;

#define MAX_LEN 1000000
#define MAX_FIB 32

int n; /* numer s�owa Fibonacciego */
int sposob;
int fib[MAX_FIB]; /* tablica liczb Fibonacciego */
string f[MAX_FIB]; /* tablica s��w Fibonacciego */
int tab[MAX_LEN]; /* tablica numer�w sufiks�w Fib(n) w porz�dku s�ownikowym */

void licz_sufiksy()
{
  /* Funkcja realizuje algorytm brutalny - tworzy pary (sufiks, pozycja),
   * a nast�pnie sortuje je leksykograficznie po sufiksach i dla ka�dego
   * numeru sufiksu wpisuje do tablicy tab jego numer w porz�dku
   * leksykograficznym */
  vector<pair<string,int> > t;
  int i;
  for (i = 0; i < f[n].size(); i++)
    t.push_back(make_pair(string(f[n].begin() + i, f[n].end()), i));
  sort(t.begin(), t.end());
  for (i = 0; i < t.size(); i++)
    tab[t[i].second] = i;
} /* licz_sufiksy */

int licz(int m)
{
  /* Funkcja realizuje szybki algorytm numerowania sufiks�w. W tym celu
   * w spos�b zach�anny rozk�ada numer sufiksu na sum� liczb Fibonacciego,
   * a nast�pnie dodaje do wyniku odpowiednie liczby Fibonacciego,
   * ewentualnie przemno�one przez -1. */
  int k = m, i = 0, wyn = 0;
  int nr = n - 1;
  while (fib[i] <= k)
    i++;
  i--;
  while (k > 0)
  {
    if (k - fib[i] >= 0)
    { 
      k -= fib[i];
      wyn += (nr - i - 1 < 0) ? -1 : (fib[nr - i - 1] * ((nr - i - 1) % 2 ? -1 : 1));
    } /* if */
    i--;
  } /* while */
  wyn += fib[n - 2]; /* ko�cowe przeskalowanie */
  return wyn;
} /* licz */

void inicjuj()
{
  fib[0] = 1; fib[1] = 2;
  for (int i = 2; i <= n; i++)
    fib[i] = fib[i - 1] + fib[i - 2];
  
  f[0] = "a"; f[1] = "ab";
  for (int i = 2; i <= n; i++)
    f[i] = f[i - 1] + f[i - 2];
} /* inicjuj */

int main()
{
  printf("Podaj parzysty numer s�owa Fibonacciego i spos�b podania wyniku.\n");
  printf("Je�eli spos�b=0, to wypisane zostanie, czy teza jest prawdziwa dla wszystkich sufiks�w.\n");
  printf("Je�eli spos�b=1, to dla ka�dego sufiksu wypisane zostanie por�wnanie\n");
  printf("mi�dzy wynikiem otrzymanym szybk� metod� a wynikiem uzyskanym w spos�b brutalny.\n\n");
  scanf("%d%d", &n, &sposob);
  inicjuj();
  licz_sufiksy();
  bool ok = true;
  for (int i = 0; i < f[n].size(); i++)
  {
    int x = licz(i);
    if (x != tab[i])
      ok = false;
    if (sposob)
      printf("Sufiks %d - faktycznie: %d, u nas: %d\n", i, tab[i], x);
  } /* for */
  if (ok)
    printf("Teza jest prawdziwa dla n=%d.\n", n);
  else
    printf("Teza jest nieprawdziwa dla n=%d!!!\n", n);
  return 0;
} /* main */
