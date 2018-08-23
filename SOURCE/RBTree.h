#include <utility>
#include <map>
#include <iterator>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <list>
#include <stack>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
typedef vector<int> VI;
typedef long long LL;
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair
#define nmx (1<<16)
inline unsigned hashF(const std::string& m)
{
    unsigned long long key=0;
    int x=m.length();
    int y=min(x,23);
    // REP(i,y)key=123479*key+m[i];
    REP(i,y)key=1000000007*key+m[i];
    //key=141*key+x;
    //key%=1<<16;
    // key>>12;
    return key%nmx;//%nmx;
}
struct adegment{
int size;
int h;
};
struct treeNode
{
public:
    typedef std::pair<int,std::string> T;
    treeNode* l;
    treeNode* r;
    treeNode* p;
    T data;           ///< Dane
    //adegment _a;
    int color;///R0 B1
    int size;
    treeNode(treeNode* a, treeNode* b, treeNode* c) : l(NULL), r(NULL),p(NULL)
    {
        color=1;
    }
    treeNode(const std::pair<int,std::string>& d, treeNode* a, treeNode* b, treeNode* c) : l(a), r(b),p(c), data(d)
    {
        color=1;
    }
    treeNode(const std::pair<int,std::string>& d):data(d)
    {
        color=1;
    }
};

class BRTree
{
    treeNode* nil,*root;
    treeNode* treeSearch(treeNode* x,int k)
    {
        if(x==nil||k==x->data.first)return x;
        if(k<x->data.first)return treeSearch(x->l,k);
        else return treeSearch(x->l,k);
    }
    treeNode* treeMinimum(treeNode* x)
    {
        while (x->l!=nil)x=x->l;
        return x;
    }
    treeNode* treeMaximum(treeNode* x)
    {
        while (x->r!=nil)x=x->r;
        return x;
    }
    treeNode* treeSuccessor(treeNode* x)
    {
        if(x->r!=nil) return treeMinimum(x->r);
        treeNode* y=x->p;
        while(y!=nil&& x==y->r)
        {
            x=y;
            y=y->p;
        }
        return y;
    }
    void  treeInsert(treeNode* z)
    {
        treeNode* y=nil;
        treeNode* x=root;
        while(x!=nil)
        {
            y=x;
            if(z->data.first<x->data.first) x=x->l;
            else x=x->r;
        }
        z->p=y;
        if(y==nil)
            root=z;
        else if (z->data.first<y->data.first)
            y->l=z;
        else y->r=z;
    }
    treeNode* treeDelete(treeNode* z)
    {
        treeNode* y=nil;
        treeNode* x=nil;
        if((z->l==nil)||z->r==nil) y=z;
        else y=treeSuccessor(z);
        if(y->l!=nil) x=y->l;
        else x=y->r;
        if(x!=nil) x->p=y->p;
        if(y->p==nil) root=x;
        else if(y==y->p->l)y->p->l=x;
        else y->p->r=x;
        if(y!=z) z->data=y->data;///wszystkie pola z y
        return y;
    }
    void right_rot(treeNode* y)
    {
//zachowuje inorder
        treeNode* x=y->l;
        y->l=x->r;
        if(x->r!=nil)x->r->p=y;
        x->p=y->p;
        if(y->p==nil)root=x;
        else if (y==y->p->l)y->p->l=x;
        else y->p->r=x;
        x->r=y;
        y->p=x;
    }
    void left_rot(treeNode* x)
    {
        treeNode* y=x->r;
        x->r=y->l;
        if(y->l!=nil)y->l->p=x;
        y->p=x->p;
        if(x->p==nil)root=y;
        else if(x==x->p->l)x->p->l=y;
        else x->p->r=y;
        y->l=x;
        x->p=y;
    }
    void RB_insert(treeNode* x)
    {
        treeInsert(x);
///RED 0   BLACK 1
        x->color=0;
        treeNode* y=nil;
        while(x!=root&&x->p->color==0)   //root must be black or guardian with
        {
            if(x->p==x->p->p->l )
            {
                y=x->p->p->r;
                if(y->color==0)
                    ///PRZYPADEK_1
                {
                    x->p->color=1;
                    y->color=1;
                    x->p->p->color=0;
                    x=x->p->p;
                }
                else
                {
                    if(x==x->p->r)
                        ///PRZYPADEK_2
                    {
                        x=x->p;
                        left_rot(x);
                    }
                    ///PRZYPADEK_3
                    x->p->color=1;
                    x->p->p->color=0;
                    right_rot(x->p->p);
                }
            }///1,2,3
            else
                ///PRZYPADKI#
            {
                y=x->p->p->l;
                if(y->color==0)
                    ///PRZYPADEK_1
                {
                    x->p->color=1;
                    y->color=1;
                    x->p->p->color=0;
                    x=x->p->p;
                }
                else
                {
                    if(x==x->p->l)
                        ///PRZYPADEK_2
                    {
                        x=x->p;
                        right_rot(x);
                    }
                    ///PRZYPADEK_3
                    x->p->color=1;
                    x->p->p->color=0;
                    left_rot(x->p->p);
                }
            }///3,4,5

        }///while
        root->color=1;
    }
    void RB_delete_fixup(treeNode* x)
    {
        treeNode* w=nil;
        while(x!=root&&x->color==1)
        {
            if(x==x->p->l)
            {
                w=x->p->r;
                if(w->color==0)
                    ///PRZYPADEK_1
                {
                    w->color=1;
                    x->p->color=0;
                    left_rot(x->p);
                    w=x->p->r;
                }
                if(w->l->color==1&&w->r->color==1)
                    ///PRZYPADEK_2
                {
                    w->color=0;
                    x=x->p;
                }
                else
                {
                    if (w->r->color==1)
                        ///PRZYPADEK_3
                    {
                        w->l->color =1;
                        w->color=0;
                        right_rot(w);
                        w=x->p->r;
                    }
                    ///PRZYPADEK_4
                    w->color=x->p->color;
                    x->p->color=1;
                    w->r->color=1;
                    left_rot(x->p);
                    x=root;
                }
            }
            else
                ///PRZYPADEK# 1 2 3
            {
                w=x->p->l;
                if(w->color==0)
                    ///PRZYPADEK_1
                {
                    w->color=1;
                    x->p->color=0;
                    right_rot(x->p);
                    w=x->p->l;
                }
                if(w->r->color==1&&w->l->color==1)
                    ///PRZYPADEK_2
                {
                    w->color=0;
                    x=x->p;
                }
                else
                {
                    if (w->l->color==1)
                        ///PRZYPADEK_3
                    {
                        w->r->color =1;
                        w->color=0;
                        left_rot(w);
                        w=x->p->l;
                    }
                    ///PRZYPADEK_4
                    w->color=x->p->color;
                    x->p->color=1;
                    w->l->color=1;
                    right_rot(x->p);
                    x=root;
                }
            }//3 4 5
        }//while
        x->color=1;
    }
    treeNode* RB_delete(treeNode* z)
    {
        //if (z==nil)return z;
        treeNode* y=nil;
        treeNode* x=nil;
        if((z->l==nil)||z->r==nil) y=z;
        else y=treeSuccessor(z);
        if(y->l!=nil) x=y->l;
        else x=y->r;
        x->p=y->p;
        if(y->p==nil)
            root=x;
        else if(y==y->p->l)
            y->p->l=x;
        else y->p->r=x;
        if(y!=z)
            z->data=y->data;///kopiowanie danych
        if(y->color==1)RB_delete_fixup(x);
        return y;
    }
public:

    BRTree()
    {
        nil=new treeNode(MP(100,"nil"),NULL,NULL,NULL);
        root=nil;
    };
    treeNode* mini()
    {
        treeNode* x=treeMinimum(root);
        return x;
    }
    treeNode* next(int a)
    {
        treeNode* x=treeSearch(root,a);
        if(x==nil)return 0;
        else x=treeSuccessor(x);
        if(x==nil)return 0;
        return x;
    }
    treeNode* next(treeNode* a)
    {
        treeNode* x=a;
        x=treeSuccessor(x);
        if(x==nil)return 0;
        return x;
    }
    void add(int a,string b)
    {
        treeNode * cos=treeSearch(root,a);
        if(cos==nil)
        {
            treeNode* xx=new treeNode(MP(a,b),nil,nil,nil);
            RB_insert(xx);
        }
        else cos->data.second=b;
    };
    void sub(int a)
    {
        treeNode* y=treeSearch(root,a);
        if(y!=nil)RB_delete(y);
    }

    void print(treeNode* x)
    {
        std::cout<<"\t_\t"<<x->data.first<<"\t_\t"<<x->data.second<<"\t_\t"<<x->color<<"\t_ "<<x->data.second<<"\t"<<x->l->data.second<<"\t"<<x->r->data.second<<std::endl;
    }
    void inorder_treeWalk(treeNode* x)
    {
        if(!(x ==nil))
        {
            std::cout<<"L";
            inorder_treeWalk(x->l);
            print(x);

            std::cout<<"r";
            inorder_treeWalk(x->r);
        }
    }
    void fore()
    {
        treeNode* x=treeMinimum(root);
        while(x!=nil)
        {
            cout<<x->data.ST<<" "<<x->data.ND<<endl;
            x=treeSuccessor(x);
        }

    }
    void print_(treeNode*x)
    {
        std::cout<<"\nWALK"<<"\t_\t"<<"KEY"<<"\t_\t"<<"VAL"<<"\t_\t"<<"COLOR"<<"\t_ IT\t"<<"LEFT"<<"\t"<<"RIGHT"<<std::endl;
        inorder_treeWalk(root);
    }
    int i=0;
    void simple_treewalk(treeNode*x)
    {
        if(!(x==nil))
        {
            simple_treewalk(x->l);
            cout<<x->data.ST<<" "<<x->data.ND;
            (++i%5)?cout<<"\t":cout<<"\n";
            simple_treewalk(x->r);
        }
    }
};
