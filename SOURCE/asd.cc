#include "TreeMap.h"
int const comp=1;
string a[nmx];
int HashTab[nmx];
void gen_words_small(int comp) {
    string s[54];
    int full[300];
    REP(i,300)full[i]=0;
    REP(i,26)s[i]="a";
    s[26]=" ";
    REP(i,26) {
        s[i][0]+=i;
        a[i]=s[i];
    }
    FOR(i,27,52)s[i]="A";
    FOR(i,27,52) {
        s[i][0]+=i-27;
        a[i]=s[i];
    }
    a[26]=s[26];
    FOR(i,53,comp*nmx-1) {
        if((i%17)) a[i]=a[rand()%i]+s[(rand()%i)%53];
        else a[i]=a[rand()%i];
    }
    int suma=0;
    int max=0;
    int maxi=0;
    REP(i,nmx)HashTab[i]=0;
    REP(i,300)full[i]=0;

    REP(i,comp*nmx) {
        int key=hashF(a[i]);
        ++HashTab[key];
    }
    REP(i,nmx) {
        int x=HashTab[i];
        if(x>299)x=299;
        ++full[x];
        //if(!(i%2000))std::cout<<i<<"\n";
    }
    REP(i,nmx) {
        if(HashTab[i]>max) {
            max=HashTab[i];
            // std::cout<<i<<"\n";
            maxi=i;
        }
    }


    int tempo=comp*nmx;
    REP(i,comp*nmx) {
        if(hashF(a[i])==maxi) {
            //std::cout<<"\n"<<i<<"\t"<<a[i]<<"\t";
        }
    }
    REP(i,min(max+1,300))std::cout<<"\n"<<i<<"\t"<<full[i]<<"\t";//<<(tempo-=full[i]);
    std::cout<<"\n n: "<<comp*nmx<<"\t empty: "<<full[0]<<"\t h:"<<max<<"\t i:"<<maxi<<"\n";
}
//////////////////////////////////////////////////////////////////////////////
// Tests
//////////////////////////////////////////////////////////////////////////////

/// A helper function that outputs a key-value pair.
void printa(const std::pair<int, std::string>& p) {
    std::cout<<p.first<<", "<<p.second<<std::endl;
}
void print(treeNode* x) {
    std::cout<<"\t"<<x->data.first<<"\t"<<x->_size<<"\t"<<x->color<<"\t"<<x->data.second<<"\t\t"<<x->l->data.second<<"\t"<<x->r->data.second<<std::endl;
}
void inorder_treeWalk(treeNode* x,treeNode* nil) {
    if(!(x ==nil)) {
        std::cout<<"L";
        inorder_treeWalk(x->l,nil);
        print(x);

        std::cout<<"r";
        inorder_treeWalk(x->r,nil);
    }
}
void print_(treeNode*x,treeNode* nil) {
    std::cout<<"\nWALK"<<"\t"<<"KEY"<<"\t"<<"SIZE"<<"\t"<<"COLOR"<<"\tIT\t\t"<<"LEFT"<<"\t"<<"RIGHT"<<std::endl;
    inorder_treeWalk(x,nil);
}
void test() {
    // A typedef used by the test.
    typedef std::map<int, std::string> TEST_MAP;
    //typedef SmallMap<int, std::string> TEST_MAP;
    //typedef TreeMap TEST_MAP;

    std::cout << "Testy uzytkownika" << std::endl;

    TEST_MAP m;

    m[2] = "Merry";
    m[4] = "Jane";
    m[8] = "Korwin";
    m[4] = "Magdalena";

    for_each(m.begin(), m.end(), printa );
    //system("PAUSE");

}
int main() {
    gen_words_small(comp);
    TreeMap xx;
    map<int,string>m;
    FOR(i,140,1600) {
        //xx.insert(MP(hashF(a[i]),a[i]));
        m[hashF(a[i])]=a[i];
        xx[hashF(a[i])]=a[i];
    }



    xx[8]="korwinssss";
    m[8]="korwinssss";
//xx.insert(MP(8,"korwin"));
//xx[8]="korwinssss";
//FOREACH(it,xx)cout<<(*it).ND;
//FOREACH(it,m)cout<<(*it).ND;
    VAR(it1, (xx).begin());
    VAR(it2, (m).begin());
    FOR(i,1600,2500) {
        //xx.insert(MP(hashF(a[i]),a[i]));
        if(xx.erase(i)!=m.erase(i))cout<<"dif"<<endl;

    }
    int co=0;
    for(; it2 != (m).end(); ++it1,++it2)if( (*it1).ND!=(*it2).ND) {
            cout<<"mm:  "<< (*it1).ND<<" "<<(*it1).ST<<"\t\tm: "<<(*it2).ND<<" "<<(*it2).ST<<endl;
        }

    return EXIT_SUCCESS;
}
