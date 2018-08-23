#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <conio.h>
using namespace std;
typedef vector<int> VI;
typedef long long LL;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
void KMP(const char* wzo) {
#define KMPH(z) while(k > 0 && wzo[k] != z[q]) k = p[k]; if(wzo[k] == z[q]) k++;
	int p[string(wzo).length() + 1], k = 0, q, m;
	p[1] = 0;
	for (q = 1; wzo[q]; q++) {
		KMPH(wzo);
		p[q + 1] = k;
	}
	m = q;
REP(x,string(wzo).length())cout<<p[x+1]<<' ';
cout<<endl;

}
void Disp(int x) {
	cout << "Znaleziono wystapienie wzorca na pozycji " << x << endl;
}

int main() {
    int N=100;
     vector< vector<int> > Matrix(N, vector<int>(N, -1));
     REP(i,100)REP(j,100)
     {
         Matrix[i][j]=j;
         cout<<Matrix[i][j]<<" ";
         if ((j-99)==0)cout<<endl;
     }
      //////
       vector<int> v;

 for(int i = 0; i < 7; i++) {
      v.push_back(i);
 }

 do {FOREACH(it,v)cout<<*it<<" ";
cout<<endl;
//      Solve(..., v);
 } while(next_permutation(ALL(v)));

return 0;
}
#include <sstream>
 void f(const string& s) {

      // Construct an object to parse strings
      istringstream is(s);

      // Vector to store data
      vector<int> v;

      // Read integer while possible and add it to the vector
      int tmp;
      while(is >> tmp) {
           v.push_back(tmp);
      }
 }

