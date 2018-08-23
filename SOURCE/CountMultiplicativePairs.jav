#include <iostream>
#include <algorithm>
#include <vector>
int warunek(vector<int > &A,vector<int> &B,int p,int q){
  double a=A[p]*A[q];
  double b=(double)B[p]/1000000;
  double bb=(double)B[q]/1000000;
  double cc=b+bb;
  b*=bb;
  double ab=A[p]*B[q];
  double ba=A[q]*B[p];
  ab+=ba;
  ab/=1000000;  
    double aa=A[p]+A[q];
    double baba=B[p]+B[q];
    baba/=1000000;
 return a+b+ab>=aa+cc;   
}
int nwarunek(vector<int > &A,vector<int> &B,int p,int q){
    
// return ((A[p]*A[q])+((A[p]*B[q]+A[q]*B[p])/1000000)+((B[p]/1000000)*(B[q]/1000000)))<(A[p]+A[q]//+((B[p]+B[q])/1000000));   
double a=A[p]*A[q];
  double b=(double)B[p]/1000000;
  double bb=(double)B[q]/1000000;
  double cc=b+bb;
  b*=bb;
  double ab=A[p]*B[q];
  double ba=A[q]*B[p];
  ab+=ba;
  ab/=1000000;  
    double aa=A[p]+A[q];
    double baba=B[p]+B[q];
    baba/=1000000;
 return a+b+ab<aa+cc;   

}
int solution(vector<int> &A, vector<int> &B) {
    int N=A.size();
    int sol=0;
    double c[N];
    for(int i=0;i<N;++i){
     c[i]=A[i]+(double)B[i]/1000000;           
       // printf("%f ",c[i]);
    }    
  std::vector<double> v(c,c+N);
  std::vector<double>::iterator low,up;
  int q=N-1;
  
  for(int p=0;p<N-1;++p){
      if(c[p]==0){
      int sth=p;
      if(c[p]==0){up= std::upper_bound(v.begin(), v.end(),0);
      sth=max(p,(int)(up-v.begin())-1);
      //printf("sth %d %d",p,sth);
      }
      sol+=sth-p;
      }
      else{
q=max(q,p+1);  
//while(q>p+1&&c[p]*c[q-1]>=c[p]+c[q-1])--q;
while((q>(p+1)) && warunek(A,B,p,q-1) )--q;
//while(q<N&&c[p]*c[q]<c[p]+c[q])++q;
while(q<N&&nwarunek(A,B,p,q))++q;
sol+=N-q;//+(sth-p);
}
sol=min(sol,1000000000);
}
return sol;
  }
