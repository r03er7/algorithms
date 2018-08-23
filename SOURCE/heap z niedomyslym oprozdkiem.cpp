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
/*************************************************************************
 *************************************************************************/
#include <stdio.h>

#define MAX_SEQ_LEN 500000
#define MAX_CARS 100000

int n_cars, max_on_floor, seq_len;
int seq[MAX_SEQ_LEN];

int heap[MAX_CARS + 1];
int heap_size;
int heap_pos[MAX_CARS + 1];
//stosy czsow
struct node {
  struct node *next;
  int t;
} nodes[MAX_SEQ_LEN];
struct node *head[MAX_CARS];


void read_data(void)
{
  int i;
  scanf("%d%d%d", &n_cars, &max_on_floor, &seq_len);
  for (i = 0; i < seq_len; i++) {
    int a;
    scanf("%d", &a);
    seq[i] = a - 1;
  }
}

int key(int c)
{
  return head[c] ? head[c]->t : seq_len;
}

#define parent(v)((v) / 2)
#define left(v)  (2 * (v))
#define right(v) (2 * (v) + 1)

void up_heap(int v)
{
  int c = heap[v];
  while (v > 1 && key(c) > key(heap[parent(v)])) {
    heap[v] = heap[parent(v)];
    heap_pos[heap[v]] = v;
    v = parent(v);
  }
  heap[v] = c;
  heap_pos[c] = v;
}

void down_heap(int v)
{
  int c = heap[v];
  while (left(v) <= heap_size) {
    int w = left(v);
    if (right(v) <= heap_size && key(heap[w]) < key(heap[right(v)]))
      w = right(v);
    if (key(heap[w]) > key(c)) {
      heap[v] = heap[w];
      heap_pos[heap[v]] = v;
      v = w;
    } else break;
  }
  heap[v] = c;
  heap_pos[c] = v;
}

void heap_delete_max(void)
{
  heap_pos[heap[1]] = 0;
  heap[1] = heap[heap_size--];
  down_heap(1);
}

void heap_insert(int c)
{
  heap[++heap_size] = c;
  up_heap(heap_size);
}

void heap_increase_key(int c)
{
  up_heap(heap_pos[c]);
}

void build_lists(void)
{
  int t;
  struct node *n = nodes;

  for (t = seq_len - 1; t >= 0; t--) {
    int c = seq[t];
    n->t = t;
    n->next = head[c];
    head[c] = n;
    n++;
  }
}

int solve(void)
{
  int res, t;

  build_lists();
  heap_size = 0;
  res = 0;
  for (t = 0; t < seq_len; t++) {
    int c = seq[t];
    if (!heap_pos[c]) {
      if (heap_size == max_on_floor)
      heap_delete_max();
      heap_insert(c);
      res++;
    }
    head[c] = head[c]->next;
    heap_increase_key(c);
  }
  return res;
}

int main(void)
{
  read_data();
  printf("%d\n", solve());
  return 0;
}
