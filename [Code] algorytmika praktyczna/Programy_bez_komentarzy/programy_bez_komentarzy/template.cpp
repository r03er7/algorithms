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
#define MP make_pair
VI Pref(char* text) {
	int k=0,q;
	VI pre(strlen(text),0);
    for(q=1;text[q];q++) {
		while(k>0 && text[k] != text[q]) k=pre[k-1]; if(text[k]==text[q]) k++;
		pre[q]=k;
    }
	return pre;
}
void KMP(const char* str,const char* wzo, void (*fun)(int)) { 
#define KMPH(z) while(k > 0 && wzo[k] != z[q]) k = p[k]; if(wzo[k] == z[q]) k++;
	int p[strlen(wzo) + 1], k = 0, q, m;
	p[1] = 0;
	for (q = 1; wzo[q]; q++) {
		KMPH(wzo);
		p[q + 1] = k;
	}
	m = q;
	k = 0;
	for (q = 0; str[q]; q++) {
		KMPH(str);
		if(m == k) {
			fun(q - m + 1); 
			k = p[k];
		}
	}
}
int lpos, pos, res, len;
char s[500001];
bool cover;

void Check(int x) {
	if (x > pos+lpos) cover = false;
	lpos = x;
}

int main() {
	cin >> s;
	VI pr = Pref(s);
	res = pos = len = strlen(s);
	while(pos) {
		if (pr[pos-1] <= pos/2) {
			cover = true; lpos = 0;
			KMP(s, s+len-pos, Check);
			if (cover) res = pos;
		}
		pos = pr[pos-1];
	}
	cout << res << endl;
	return 0;
}
