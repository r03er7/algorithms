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
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

int main(void)
{
 priority_queue<int, vector<int>, greater<int> > Q;
// sprawia, �e na szczycie kolejki jest minimum

 Q.push(5);
 Q.push(7);

 cout << Q.top() << endl;
 return 0;
}
