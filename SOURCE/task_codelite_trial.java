#include <vector>
#include <algorithm>
int solution(vector<int>& A) {
    int n = A.size();
    vector<int> L;
    L.push_back(-1);
    for (int i = 0; i < n; i++) {
        L.push_back(A[i]);
    }
    int count = 0;
    int pos = (n) / 2;
    int candidate = L[pos+1];
    for (int i = 1; i <= n; i++) {
        if (L[i] == candidate)
            count = count + 1;
    }
    if (count > pos)
        return candidate;
    return (-1);





// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(IntList * L) {
    // write your code in C++11
    int hitler=0;
    for(;;){
     if(L==0)return hitler;
     ++hitler;
       L=L->next; 
        
    }
}


SELECT
    SUM(v) AS SumTotal
FROM elements






// System.out.println("this is a debug message");

class Solution {
    public int solution(int[] A) {
        // write your code in Java SE 8
        long[] l=new long[A.length+1];
        long[] p=new long[A.length+1];
        for(int i=0;i<A.length;++i){
         l[i]+=A[i];
         l[i+1]=l[i];
        }
        p[0]=l[A.length];
        for(int i=1;i<A.length;++i)
        {p[i]=p[i-1]-A[i-1];
        }
        for(int i=0;i<A.length;++i)if(p[i]==l[i])return i;
        return -1;
    }
}
