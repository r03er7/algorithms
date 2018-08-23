#include <iostream>
#include <algorithm>
#include <vector>
// you can use includes, for example:
// #include <algorithm>

int solution(vector<int> &A) {
    vector<int > l;
    vector<int > p;
    p.resize(A.size());
    l.resize(A.size());
    int lasti=0;
    for(int i=1;i<A.size();++i){
        if(A[i]<A[i-1]){
            l[i]=lasti;
            }
            else{
             l[i]=i;
             lasti=i;
            }
}
lasti=A.size()-1;
p[lasti]=lasti;
    for(int i=A.size()-2;i>-1;--i){
        if(A[i]<A[i+1]){
            p[i]=lasti;
            }
            else{
             p[i]=i;
             lasti=i;
            }
}
int sol=-1;
for(int i=0;i<A.size();++i)
    sol=max(sol,min(A[l[i]]-A[i],A[p[i]]-A[i]));
if (sol==0)--sol;
    return sol;
}
