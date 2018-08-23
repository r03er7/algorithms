/*
USER: robert
DATE: 25 10 2014
*/

//#pragma warning (disable: 4786)
//#pragma comment (linker, "/STACK:0x800000")
//#define _CRT_SECURE_NO_WARNINGS 1

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <bitset>
#include <iterator>
#include <set>
#include <cstring>//clr

#include <cassert>//arab
#include <climits>
#include <iomanip>
#include <list>
#include <ctime>

#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define REP(i,nn) for(int i=0;i<(nn);++i)
#define VAR(v, nn) __typeof(nn) v = (nn)
#define VAL(i,v) VAR(v,n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define CLR(A,v) memset((A),v,sizeof((A))) //p o size p
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
//ios_base::sync_with_stdio(0);
using namespace std;

template< class T > T _abs(T n) {
	return (n < 0 ? -n : n);
}
template< class T > T _max(T a, T b) {
	return (!(a < b) ? a : b);
}
template< class T > T _min(T a, T b) {
	return (a < b ? a : b);
}
template< class T > T sq(T x) {
	return x * x;
}

typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef vector<int> VI;
typedef vector<double> VD;

typedef vector<string> VS;
typedef pair<int, int> PI;
///const int INF = 1000000000;
///const LL INFLL = LL(INF) * LL(INF);
const double EPS = 1e-9;
template<class T> inline int size(const T&c) {
	return c.size();
}
template<class T> T parse(string s) {
	istringstream i(s);
	T x;
	i >> x;
	return x;
}
template<class T> string show(T x) {
	ostringstream o;
	o << x;
	return o.str();
}
VS split(string s, string del = " ") {
	string w;
	VS res;
	s += del[0];
	FOREACH(it, s) {
		if (find(ALL(del), *it) == del.end()) w += *it;
		else if (w != "") {
			res.push_back(w);
			w = "";
		}
	}
	return res;
}
VI s2vi(string s, string del = " ") {
	VS v = split(s, del);
	VI res;
	FOREACH(it, v) res.push_back(parse<int>(*it));
	return res;
}
string mergeStrings(VS v) {
	string s;
	FOREACH(it, v) s += *it;
	return s;
}

#define debug(x) cerr << #x << " = " << x << "\n";
#define debugv(x) cerr << #x << " = "; FOREACH(it,(x)) cerr << *it << ","; cerr << "\n";
