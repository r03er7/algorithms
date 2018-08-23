#include "rbtree.h"
int const comp=1;
string a[comp*nmx];
int HashTab[nmx];
void gen_words_small(int comp)
{
    string s[54];
    int full[300];
    REP(i,300)full[i]=0;
    REP(i,26)s[i]="a";
    s[26]=" ";
    REP(i,26)
    {
        s[i][0]+=i;
        a[i]=s[i];
    }
    FOR(i,27,52)s[i]="A";
    FOR(i,27,52)
    {
        s[i][0]+=i-27;
        a[i]=s[i];
    }
    a[26]=s[26];
    FOR(i,53,comp*nmx-1)
    {
        if((i%17)) a[i]=a[rand()%i]+s[(rand()%i)%53];
        else a[i]=a[rand()%i];
    }
    int suma=0;
    int max=0;
    int maxi=0;
    REP(i,nmx)HashTab[i]=0;
    REP(i,300)full[i]=0;

    REP(i,comp*nmx)
    {
        int key=hashF(a[i]);
        ++HashTab[key];
    }
    REP(i,nmx)
    {
        int x=HashTab[i];
        if(x>299)x=299;
        ++full[x];
        //if(!(i%2000))std::cout<<i<<"\n";
    }
    REP(i,nmx)
    {
        if(HashTab[i]>max)
        {
            max=HashTab[i];
            // std::cout<<i<<"\n";
            maxi=i;
        }
    }


    int tempo=comp*nmx;
    REP(i,comp*nmx)
    {
        if(hashF(a[i])==maxi)
        {
            //std::cout<<"\n"<<i<<"\t"<<a[i]<<"\t";
        }
    }
    REP(i,min(max+1,300))std::cout<<"\n"<<i<<"\t"<<full[i]<<"\t";//<<(tempo-=full[i]);
    std::cout<<"\n n: "<<comp*nmx<<"\t empty: "<<full[0]<<"\t h:"<<max<<"\t i:"<<maxi<<"\n";
}
int main()
{
    treeNode* z[10];
    nil->l=nil;
    nil->p=nil;
    nil->r=nil;
    gen_words_small(comp);
    treeNode* xx[10];
    REP(i,10)
    {
        xx[i]=new treeNode(MP(i,a[i]),nil,nil,nil);
        RB_insert(xx[i]);

    }
    print_(root);
    RB_delete(root);
    print_(root);


    //system("PAUSE");
    return EXIT_SUCCESS;
}
