#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

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
#include <set>
struct el {
	int x, y;
	LL size;
	el(int x, int y) : x(x), y(y) {
		size = LL(x)*LL(y);
	}
};

struct obj {
	int x,y,z;
};

struct sizeOrder
{
  bool operator()(const el& a, const el& b) const
  {
	if (a.size != b.size)
		return a.size > b.size;
	return (a.x != b.x) ? a.x < b.x : a.y < b.y;
  }
};

struct xOrder
{
  bool operator()(const el& a, const el& b) const
  {
	return (a.x != b.x) ? a.x < b.x : a.y < b.y;
  }
};

bool zOrder(const obj& a, const obj& b) {
	if (a.z != b.z)
		return a.z < b.z;
	return (a.x != b.x) ? a.x < b.x : a.y < b.y;
}

set<el, sizeOrder> sizeSet;
set<el, xOrder> xSet;

int main() {
	int n;
	cin >> n;
	vector<obj> l(n+1);
	REP(x, n) cin >> l[x].x >> l[x].y >> l[x].z;
	l[n].x=l[n].y=l[n].z=1000000;
	sort(ALL(l), zOrder);
	LL res = 0;
	obj ores;
	sizeSet.insert(el(1000000, 1000000));
	xSet.insert(el(1000000, 1000000));
	REP(x, n+1) {
		VAR(it2, sizeSet.begin());
		if (res < it2->size * (LL)l[x].z) {
			res = it2->size * (LL)l[x].z;
			ores.x = it2->x;
			ores.y = it2->y;
			ores.z = l[x].z;
		}
		el e = el(l[x].x, l[x].y);
		VAR(it, xSet.lower_bound(e));
		if (it != xSet.end() && it->y > e.y) {
			el f = el(l[x].x, it->y);
			sizeSet.erase(*it);
			xSet.erase(*it);
			e.x = it->x;
			while(1) {
			    VAR(it2, xSet.lower_bound(e));
			    if (it2 == xSet.end() || it2->y < e.y) break;
			    e.x = it2->x;
    			sizeSet.erase(*it2);
			    xSet.erase(*it2);
			}
			e.size = (LL)e.x*(LL)e.y;
			xSet.insert(e);
			xSet.insert(f);
			sizeSet.insert(e);
			sizeSet.insert(f);
		}
	}
	cout << ores.x << " " << ores.y << " " << ores.z << endl;
	return 0;
}
