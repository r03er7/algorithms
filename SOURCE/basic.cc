
#include "szablon.h"
#define MAXTRY 1000000
#define INF 1000

class neuron
{
private:
    int n;
    VD w;
    double c;
    //activation function
    double a()
    {
       return c;
    }
    //combination function
    double cf()
    {
        double res=b;
        REP(i,SIZE(w))
        res+=w[i]*x[i];
        return res;
    }
public:
    //inbup
    VD x;
    //bias
    double b=1.0;
    //output
    double y;
    neuron(VD& a)
    {
        n=SIZE(a);
        x=a;
        REP(i,n)w.PB(1);
    }
    int write()
    {
        printf("\n");
        FOREACH(it,x)printf("%f\t",*it);
    }
};
class laver
{




};
int main()
{
    VD v;
    REP(i,6)v.PB(0.5+i);
    FOREACH(it,v)printf("%f\t",*it);
    neuron n(v);
    n.write();
    //iSecret = rand() % 10 + 1;
    return 0;
}
