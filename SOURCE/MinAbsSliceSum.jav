#include <algorithm>
int solution(vector<int> &A) {
    int n=A.size();
    vector<int > l;
    l.resize(n+1);
    l[0]=0;
    for(int i=0;i<n;++i)l[i+1]=A[i]+l[i];
    int res=1000000000;
    int temp=0;
    sort(l.begin()+1,l.end());
    
    //for(int i=1;i<n;++i)printf(" %d",l[i]);
    
     for(int i=1;i<n;++i){
         temp=l[i]-l[i+1];
         if (temp<0)temp*=-1;
         res=min(res,temp);
     }
     for(int i=1;i<n+1;++i){
         if(l[i]<0)l[i]*=-1;
         res=min(res,l[i]);
     }
    return res;
}
