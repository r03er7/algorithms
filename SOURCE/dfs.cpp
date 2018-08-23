#include<cstdio>
#include<vector>
#include<list>
#include<stack>
using namespace std;
#define MAX 10

//structure for a single linked list
typedef struct element {
     int info;
     struct element *link;
} node;

//structure for a grapgh
typedef struct graphAdjList {
     int nodes;
     node * adjList[MAX];
} graph;


/*
       g is a graph
       start is info of some node
       visited is an array of all the nodes
*/
void DFS(graph *g, int start, int visited[])//function for a Depth First Search
{
     visited[start]=1;//set the current node as visited

     //printf("%d", start);

     node *p;//pointer that is needed for traversing through the graph

     for(p=g->adjList[start]; p; p=p->link) {
          if(!visited[p->info]) //if not visited
               DFS(g, p->info, visited);   //visit then node with p->info
     }
}
int main()
{



     return 0;
}
