#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
#define REP(x, n) for(int x = 0; x < (n); ++x)
using namespace std;
int const M=100;
int const Q=1000000007;
int n;
struct  matrix{
int t[M][M];
};

void mnorz(){
matrix c,a,b;


REP(i,n)REP(j,n){
    c.t[i][j]=0;
    REP(k,n) c.t[i][j]+=(long long)a.t[i][k]*b.t[k][j]%Q;
//1   5Q^2;
//2    nQ^2   to c long long i modulo na koncu
}
}
void mnorz_fast(){

matrix c,a,b;

REP(i,n)REP(j,n)
    c.t[i][j]=0;

REP(i,n)REP(k,n)REP(j,n)
c.t[i][j]+=(long long)a.t[i][k]*b.t[k][j]%Q;
//1   5Q^2;
//2    nQ^2   to c long long i modulo na koncu
}

void potegowanie(int k){matrix W,A;
while(k){
if(k%2) mnorz_fast();
mnorz_fast();
k/=2;
}


}
int main(){
    return 0;
}
