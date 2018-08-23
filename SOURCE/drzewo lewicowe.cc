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
#include <stack>
#include <queue>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define FORD(i,a,b) for(int i=(a);i>=(b);--i)
#define FOREACH(it,c) for(typeof((c).begin()) it=(c).begin();it!=(c).end();++it)
#define ALL(c) (c).begin(),(c).end()
#define debug(x) cerr << #x << " = " << x << "\n";
#define debugv(x) cerr << #x << " = "; FOREACH(it,(x)) cerr << *it << ","; cerr << "\n";
typedef long long LL;
typedef long double ld;
typedef vector<int> VI;
typedef vector<string> VS;
const int INF = 1000000000;
const LL INFLL = LL(INF) * LL(INF);
template<class T> inline int size(const T&c) {
    return c.size();
}



#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
struct road {
    int from, to;
    list<road*> adj;
    int color, number;

    road():color(-1) {}
};

struct tree_node {
    tree_node *left, *right;
    int len;
    road *rd;

    tree_node(road *rdi):left(0), right(0), len(1), rd(rdi) {}
};

tree_node *union_trees(tree_node *a, tree_node *b) {
    if (a->rd->to > b->rd->to) swap(a, b);
    a->left = a->left ? union_trees(a->left, b) : b;
    if (!a->right || a->left->len > a->right->len) swap(a->left, a->right);
    a->len = a->left ? a->left->len+1 : 1;
    return a;
}

bool operator<(const road &a, const road &b) {
    return a.from < b.from || a.from == b.from && a.to > b.to;
}

void search(road *current, int c) {
    if (current->color != -1) return;
    current->color = c;
    for (list<road*>::iterator i = current->adj.begin();
            i != current->adj.end(); ++i)

        //FOREACH(i,current->adj)
        search(*i, c^1);
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<road> roads(k);
    for (int i = 0; i < k; ++i) {
        cin >> roads[i].from >> roads[i].to;
        roads[i].number = i;
    }
    sort(roads.begin(), roads.end());
    stack<tree_node*> S;
    for (int i = 0; i < k; ++i) {
        while (!S.empty() && S.top()->rd->to <= roads[i].from) {
            tree_node *root = S.top();
            if (root->left) S.top() = union_trees(root->left, root->right);
            else if (root->right) S.top() = root->right;
            else S.pop();
            delete root;
        }
        tree_node *cur = new tree_node(&roads[i]);
        while (!S.empty() && S.top()->rd->to < roads[i].to) {
            S.top()->rd->adj.push_back(&roads[i]);
            roads[i].adj.push_back(S.top()->rd);
            cur = union_trees(cur, S.top());
            S.pop();
        }
        S.push(cur);
    }
    for (int i = 0; i < k; ++i) search(&roads[i], 0);
    stack<road*> side[2];
    for (int i = 0; i < k; ++i) {
        int c = roads[i].color;
        while (!side[c].empty() && side[c].top()->to <= roads[i].from)
            side[c].pop();
        if (!side[c].empty() && side[c].top()->to < roads[i].to) {
            cout << "NIE" << endl;
            return 0;
        }
        side[c].push(&roads[i]);
    }
    vector<int> colors(k);
    for (int i = 0; i < k; ++i) colors[roads[i].number] = roads[i].color;
    for (int i = 0; i < k; ++i) cout << (colors[i] ? 'S' : 'N') << endl;
    return 0;
}
