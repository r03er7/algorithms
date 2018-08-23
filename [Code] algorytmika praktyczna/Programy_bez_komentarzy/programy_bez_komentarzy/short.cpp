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
#include<stdio.h>
int h,w,l,s,x,v,k=1; char b[40];
main(){
	gets(b); sscanf(b,"%d%d%d",&h,&w,&l);
	char t[s=(h+2)*(w+2)*(l+2)];
	int d[s],e[256],que[s],dis[]={-1,1,-(v=w+2),v,-v*(l+2),v*(l+2)};
	for(x=0;x<s;++x) t[x]=0,d[x]=-1;
	for(x=0;x<h*w*l;++x) (x%w ?0: gets(t+(v=(w+2)*(l+3+2*(x/(w*l))+x/w)+1))), e[t[v+(x%w)]]=v+(x%w);
	for(d[que[0]=e['S']]=x=0;x<6*k;++x) if(t[v=que[x/6]+dis[x%6]]!='#' && t[v] && d[v]==-1) d[que[k++]=v]=d[que[x/6]]+1;
	printf("%d\n",d[e['M']]);}
