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
using namespace std;

struct LTree {
	LTree* left;
    LTree* right;
	int key;
	int dist;
};
inline LTree* singleton(int x) {
	LTree* ret = new LTree;
	ret->key   = x;
	ret->dist  = 1;
	ret->left  = NULL;
	ret->right = NULL;
	return ret;
}
inline int getMin(struct LTree* t){
    return t->key;//(t==NULL)?(0):(d->key);
}
inline int getDist(struct LTree* t){
    return (t==NULL)?(0):(t->dist);
}
LTree* merge(LTree* a, LTree* b) {
	if (a==NULL) return b;
	if (b==NULL) return a;
	// a!=NULL && b!=null
	if (getMin(b)<getMin(a)) swap(a,b);
	a->left = merge(a->left,b);
	if (getDist(a->left) > getDist(a->right) ) swap(a->right,a->left);
	if (a->right==NULL) a->dist = 0; else a->dist = 1+a->right->dist;
	return a;
}
LTree* delMin(LTree* d) {
	if (d!=NULL) {
		LTree* tmp = merge(d->left,d->right);
		free(d);
		return tmp;
	}
	return NULL;
}
inline bool isEmpty(LTree* d) {
	return (d==NULL);
}
inline void deLTree(struct LTree* t){
    if (t==NULL) return;
    deLTree(t->left);
    deLTree(t->right);
    free(t);
}
void w(LTree *t){
if(t==NULL)cout<<"!";
else
cout<<(t->key)<<"|"<<(t->dist)<<" ";
}
void write(LTree *t){
if(t==NULL)cout<<"!";
else
{cout<<(t->key)<<"|"<<(t->dist)<<": ";
 w(t->left);
 w(t->right);
 cout<<endl;


}

}
void writer(LTree* t){
write(t);
if(t==NULL)return;
writer(t->left);
writer(t->right);
}
int main() {
    LTree* h,*b;

    int A[]={3,4,5,6,2,3,45,6,3,34,634,6,3,2};
    h=singleton(A[0]);
    writer(h);cout<<endl;
    FOR(x,3,8){
writer(h);cout<<endl;
    h=merge(singleton(A[x]),h);
    }
writer(h);
	return 0;
}

