porzadek
bool operator<(const road &a, const road &b) {
    return a.from < b.from || a.from == b.from && a.to > b.to;
}
struct cmp
{
 // czy a jest mniejsze od b
 bool operator() (const int &a, const int &b)
 {
  if (dist[a] < dist[b]) return true;
  if (dist[a] > dist[b]) return false;
  return a<b;
 }
};
set<int, cmp> kopiec; // ;-)tak do dijstry
int main(){
priority_queue<int, vector<int>, greater<int> > Q;
// sprawia, że na szczycie kolejki jest minimum
priority_queue<int, vector<int>, cmp > Qq;
 Q.push(5);
 Q.push(7);

 cout << Q.top() << endl;
return 0;}



struct ltstr {
  bool operator() (const Point & p1, const Point & p2) {
    ll vectorProduct = p1.x * p2.y - p2.x * p1.y;
    if (vectorProduct != 0)
       return vectorProduct > 0;
    else                        // Je¶li maj± ten sam kierunek, mniejszy jest ten o mniejszej d³ugo¶ci.
       return sqrSize(p1) < sqrSize(p2);  // Wystarczy porównaæ kwadraty d³ugo¶ci wektorów.
    // Zauwa¿my, ¿e w takim porz±dku wektor (0,0) jest mniejszy od ka¿dego innego
    // wektora i po posortowaniu znajdzie siê na pocz±tku.
}};

// Sortowanie wektorów (punktów) wzglêdem k±tów, jakie tworz± z wektorem (1,0)
// oraz wzglêdem d³ugo¶ci.
// Punkty (0,0) s± traktowane jako minimalne i trafiaj± na pocz±tek tablicy.
void sortByAngles(vector < Point > &set)
{
  // Podzia³ zbioru punktów wed³ug kryterium upperPart (patrz opis funkcji upperPart).
  vector < Point >::iterator middle =
      partition(set.begin(), set.end(), upperPart);

  // Sortowanie obu czê¶ci.
  sort(set.begin(), middle, ltstr());
  sort(middle, set.end(), ltstr());
}
