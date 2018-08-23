#include "szablon.h"
int sx,sy;
vector<pair<int,int> > L,R;

bool close2(pair<int,int> a, pair<int,int> b) {
    return abs(a.first-b.first)+abs(a.second-b.second) <=1;
}

bool onedge(pair<int,int> a) {
    return a.first==0 || a.second==0 || a.first==sx-1 || a.second==sy-1;
}

const int MAXV = 256;
int V;
int cap[MAXV][MAXV];

int nrL(int x) {
    return x+5;
}
int nrR(int x) {
    return x+5+size(L);
}

int vis[MAXV];

bool dfs(int x) {
    vis[x]=true;
    if(x==1) return true;
    REP(y,V) if(!vis[y] && cap[x][y]>0) {
        if(dfs(y)) {
            cap[x][y]--;
            cap[y][x]++;
            return true;
        }
    }
    return false;
}

bool aug() {
    REP(i,V) vis[i]=false;
    return dfs(0);
}

int calcFlow() {
    bool progress = false;
    while(aug()) {
        progress=true;
    }
    bool ok = true;
    FOR(a,1,V-1) if(cap[0][a]>0) ok=false;
    if(ok) return 1;
    else if(progress) return 0;
    else return -1;
}

///struct SnakesOnAPlane {
int snakes(vector <string> grid) {
    sy=size(grid);
    sx=size(grid[0]);
    REP(x,sx) REP(y,sy) if(grid[y][x]=='.') {
        if((x+y)%2==0)
            L.push_back(make_pair(x,y));
        else
            R.push_back(make_pair(x,y));
    }
    V = size(L) + size(R)+5;
    debug(size(L));
    debug(size(R));
    REP(a,size(L)) REP(b,size(R)) if(close2(L[a],R[b])) cap[nrL(a)][nrR(b)]++;
    REP(a,size(L)) cap[0][nrL(a)]+=2;
    REP(a,size(R)) cap[nrR(a)][1]+=2;
    int res = 0;
    REP(a,size(L)) if(onedge(L[a])) cap[nrL(a)][2]++;
    REP(a,size(R)) if(onedge(R[a])) cap[4][nrR(a)]++;
    if(size(L)>size(R)) {
        int A = size(L)-size(R);
        res += A;
        cap[2][1] += 2 * A;
    } else if (size(R)>size(L)) {
        int A = size(R)-size(L);
        res += A;
        cap[0][4] += 2 * A;
    }
    for(int iter=0;; ++iter) {
        int v = calcFlow();
        if(iter>0 && v==-1) break;
        if(v==1) return res;
        res++;
        ++cap[2][4];
    }
    return -1;
}
///};
int main() {
    vector <string> grid;
    grid.PB("##.##..#####");
    grid.PB("....#..#...#");
    grid.PB("..#.#..#.#.#");
    grid.PB("....#..#...#");
    grid.PB("#####..#####");
    grid.PB("............");
    grid.PB( "............");
    grid.PB( "#####..#####");
    grid.PB( ".#..#..#....");
    grid.PB( ".#..#..#....");
    grid.PB( "...##..#....");
    grid.PB( "##.....#....");
    printf("%2d\n",snakes(grid));
    return 0;
}
