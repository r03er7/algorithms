#include <iostream>     // std::cout
#include <algorithm>
#include <vector>
int solution(vector<int> &A, vector<int> &B)
{
    int N=A.size();
    int p=0,q=0;
    int sol=0;
    double c[N];

    for(int i=0; i<N; ++i)
    {
        c[i]=A[i]+(double)B[i]/1000000;
        printf("%f ",c[i]);
    }
    std::vector<double> v(c,c+N);           // 10 20 30 30 20 10 10 20

    //std::sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

    std::vector<double>::iterator low,up;
    low=std::lower_bound (v.begin(), v.end(), c[1]);
    up= std::upper_bound (v.begin(), v.end(), c[1]);

    for(int p=0; p<N; ++p)
    {
        up= std::upper_bound (v.begin(), v.end(), c[p]/(c[p]-1));
        std::cout << "\n"<<p<<" "<<up<<" "<<(up - v.begin())<<"  "<<c[p]/(c[p]-1);

        if(up!=v.end())
        {
            if((up-v.begin())>=p)
                sol+=(N-1-(up-v.begin()));
            else
            {
                sol+=(N-1-p);
            }
        }
    }
    return sol;
}
