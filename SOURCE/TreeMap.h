#include "szablon.h"
#define nmx (1<<16)

/// A class to package the data into so it has the left and right hook for the tree.
struct superNode;
struct treeNode { //: CCount
    typedef std::pair<int,std::string> T;
    treeNode* l;   ///< WskaŸnik na kolejny element na liœcie/pierœcieniu
    treeNode* r;   ///< WskaŸnik na poprzedni element nal liœcie/pierœcieniu
    treeNode* p;
    T data;           ///< Dane
    int _size;
    superNode* datapointer;
    ///int _h;
    int color;///r0 b1

    treeNode(treeNode* a, treeNode* b, treeNode* c) : l(NULL), r(NULL),p(NULL) {
        color=1;
        _size=1;
        ///_h=1;
    }
    treeNode(const std::pair<int,std::string>& d, treeNode* a, treeNode* b, treeNode* c) : l(a), r(b),p(c), data(d) {
        color=1;
        _size=1;
    }
    treeNode(const std::pair<int,std::string>& d):data(d) {
        color=1;
        _size=1;
    }
};
struct superNode {
    treeNode* nil;
    treeNode* root;
    superNode() : nil(NULL), root(NULL) {}
    superNode(treeNode* a, treeNode* b) : nil(a), root(b) {}
};












inline unsigned hashF(const std::string& m) {
    unsigned long long key=0;
    int x=m.length();
    REP(i,x)key=1000000007*key+m[i];
    return key%nmx;//%nmx;
}
///treeNode* treeMinimum(treeNode* x,treeNode* nil,treeNode*root);
treeNode* teeSearch(treeNode* x,int k,treeNode*nil,treeNode*root) {
    if(x==nil||k==x->data.first)return x;
    if(k<x->data.first)return teeSearch(x->l,k,nil,root);
    else return teeSearch(x->l,k,nil,root);
}
treeNode* treeMinimum(treeNode* x,treeNode*nil,treeNode*root) {
    while (x->l!=nil)x=x->l;
    return x;
}
treeNode* treeMaximum(treeNode* x,treeNode*nil,treeNode*root) {
    while (x->r!=nil)x=x->r;
    return x;
}
treeNode* treePredescor(treeNode* x,treeNode*nil,treeNode*root) {
    if(x->l!=nil) return treeMaximum(x->l,nil,root);
    treeNode* y=x->p;
    while(y!=nil&& x==y->l) {
        x=y;
        y=y->p;
    }
    return y;
}
treeNode* treeSuccessor(treeNode* x,treeNode*nil,treeNode*root) {
    if(x->r!=nil) return treeMinimum(x->r,nil,root);
    treeNode* y=x->p;
    while(y!=nil&& x==y->r) {
        x=y;
        y=y->p;
    }
    return y;
}

class TreeMap {
    friend class TreeMapDetail;
public:
    typedef int Key;
    typedef std::string Val;

protected:
    ////
public:
    typedef treeNode/*<Key, Value>*/ Node;
    Node* root;   ///< The root of the tree
    Node* nil;
    superNode bank;
public:
    typedef size_t size_type;
    typedef std::pair<Key, Val> P;

    TreeMap();
    TreeMap( const TreeMap& );
    ~TreeMap();
    treeNode* treeSearch(treeNode* x,int k);
    //treeNode* treeMinimum(treeNode* x);
    //treeNode* treeMaximum(treeNode* x);
    void  treeInsert(treeNode* z);
    treeNode* treeSuccessor(treeNode* x);
    void right_rot(treeNode* y);
    void left_rot(treeNode* x);
    void RB_insert(treeNode* x);
    void RB_delete_fixup(treeNode* x);
    treeNode* RB_delete(treeNode* z);
    treeNode* OS_select(treeNode* x,int i);
    int OS_rank(treeNode* x);
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag,
            std::pair<Key, Val> > {
    public:
        typedef std::pair<Key, Val> T;

    protected:
        /// Points to the tree element
        Node* node;
        friend class TreeMap;

        const_iterator(Node* x) : node(x) {}
    public:
        const_iterator() {}
        const_iterator(const const_iterator& a) : node(a.node) {}

        inline const T& operator*() const {
            return node->data;
        }

        inline const T* operator->() const {
            return &(node->data);
        }

        // preincrement
        /*inline*/ const_iterator& operator++();
        // postincrement
        /*inline*/ const_iterator operator++(int);
        // predecrement
        /*inline*/ const_iterator& operator--();
        // postdecrement
        /*inline*/ const_iterator operator--(int);

        inline bool operator==(const const_iterator& a) const {
            return node == a.node;
        }

        inline bool operator!=(const const_iterator& a) const {
            return node != a.node;
        }
    };

    /// An iterator.
    class iterator : public const_iterator {
        iterator(Node* x) : const_iterator(x) {}
        friend class TreeMap;

    public:
        iterator() {}
        iterator(const const_iterator& a) : const_iterator(a) {}
        iterator(const iterator& a) {
            node = a.node;
        }

        inline T& operator*() const {
            return node->data;
        }
        inline T* operator->() const {
            return &(node->data);
        }

        iterator& operator++() {
            // preincrement
            ++(*(const_iterator*)this);
            return (*this);
        }

        iterator operator++(int) {
            // postincrement
            iterator temp = *this;
            ++*this;
            return temp;
        }

        iterator& operator--() {
            // predecrement
            --(*(const_iterator*)this);
            return (*this);
        }

        iterator operator--(int) {
            // postdecrement
            iterator temp = *this;
            --*this;
            return temp;
        }
    };

    /// Returns an iterator addressing the first element in the map
    iterator begin();
    /// Returns a const_iterator addressing the first element in the map
    const_iterator begin() const;

    /// Returns an iterator that addresses the location succeeding the last element in a map
    iterator end();
    /// Returns a const_iterator that addresses the location succeeding the last element in a map
    const_iterator end() const;

    /// Inserts an element into the map.
    /// @returns A pair whose bool component is true if an insertion was
    ///          made and false if the map already contained an element
    ///          associated with that key, and whose iterator component coresponds to
    ///          the address where a new element was inserted or where the element
    ///          was already located.
    std::pair<iterator, bool> insert(const std::pair<Key, Val>& entry);

    /// Inserts an element into the map.
    /// This method assumes there is no value asociated with
    /// such a key in the map.
    iterator unsafe_insert(const std::pair<Key, Val>& entry);

    /// Returns an iterator addressing the location of the entry in the map
    /// that has a key equivalent to the specified one or the location succeeding the
    /// last element in the map if there is no match for the key.
    iterator find(const Key& k);
    const_iterator find(const Key& k) const;

    //bool belongs( const Key& k) const;

    /// Inserts an element into a map with a specified key value
    /// if one with such a key value does not exist.
    /// @returns Reference to the value component of the element defined by the key.
    Val& operator[](const Key& k);

    /// Tests if a map is empty.
    bool empty( ) const;

    /// Returns the number of elements in the map.
    size_type size() const;

    /// Returns the number of elements in a map whose key matches a parameter-specified key.
    size_type count(const Key& _Key) const;

    /// Removes an element from the map.
    /// @returns The iterator that designates the first element remaining beyond any elements removed.
    iterator erase(iterator i);

    /// Removes a range of elements from the map.
    /// The range is defined by the first and last iterators
    /// first is the first element removed and last is the element just beyond the last elemnt removed.
    /// @returns The iterator that designates the first element remaining beyond any elements removed.
    iterator erase(iterator first, iterator last);

    /// Removes an element from the map.
    /// @returns The number of elements that have been removed from the map.
    ///          Since this is not a multimap itshould be 1 or 0.
    size_type erase(const Key& key);

    /// Erases all the elements of a map.
    void clear( );

    /// Returns true if this map's internal structure is identical to another map's structure.
    bool struct_eq(const TreeMap& another) const;
    /// Returns true if this map contains exactly the same key-value pairs as the another map.
    bool info_eq(const TreeMap& another) const;

    /// Returns true if this map contains exactly the same key-value pairs as the another map.
    inline bool operator==(const TreeMap& a) const {
        return info_eq(a);
    }

    /// Assignment operator copy the source elements into this object.
    TreeMap& operator=(const TreeMap& );
};
/// A helper class.
class TreeMapDetail { //Helper
protected:
    friend class TreeMap;

    /// Stupid example of a method that modifies a protected field in
    /// the TreeMap class. Feel free to remove this method or add new
    /// ones here.
    static void erase(TreeMap* tm, const TreeMap::Key& k) {
        tm->root=NULL; // we just modified a protected field in tree map
    }
};
//////////////////////////////////////////////////////////////////////////////
// TreeMap and TreeMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

TreeMap::TreeMap() {
    nil=new treeNode(MP(0,"#nil"),NULL,NULL,NULL);
    //root=nil;
    root=new treeNode(MP(INF,"$root"),nil,nil,nil);
    root->_size=0;
    nil->l=root;
    nil->p=root;
    nil->r=root;
    nil->_size=0;
    nil->color=1;
    bank.nil=nil;
    bank.root=root;
    nil->datapointer=&bank;
    root->datapointer=&bank;
};
TreeMap::TreeMap( const TreeMap& m ) {
    treeNode* nil=new treeNode(MP(100,"nil"),NULL,NULL,NULL);
    treeNode* root=nil;
    nil->l=nil;
    nil->p=nil;
    nil->r=nil;
    nil->_size=0;
};
TreeMap::~TreeMap() {
    clear();
};
treeNode* TreeMap::treeSearch(treeNode* x,int k) {
    if(x==nil||k==x->data.first)return x;
    if(k<x->data.first)return treeSearch(x->l,k);
    else return treeSearch(x->l,k);
}
//treeNode* TreeMap::treeMinimum(treeNode* x)
//{
//    while (x->l!=nil)x=x->l;
//    return x;
//}
//treeNode* TreeMap::treeMaximum(treeNode* x)
//{
//   while (x->r!=nil)x=x->r;
// return x;
//}
treeNode* TreeMap::treeSuccessor(treeNode* x) {
    if(x->r!=nil) return treeMinimum(x->r,nil,root);
    treeNode* y=x->p;
    while(y!=nil&& x==y->r) {
        x=y;
        y=y->p;
    }
    return y;
}
void  TreeMap::treeInsert(treeNode* z) {
    treeNode* y=nil;
    treeNode* x=root;
    while(x!=nil) {
        y=x;
        ///WZBOGACANIE
        ++x->_size;
        ///
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
void TreeMap::right_rot(treeNode* y) {
//zachowuje inorder
    treeNode* x=y->l;
    y->l=x->r;
    if(x->r!=nil)x->r->p=y;
    x->p=y->p;
    if(y->p==nil)root=x;
    else if (y==y->p->l)
        y->p->l=x;
    else y->p->r=x;
    x->r=y;
    y->p=x;

    ///WZBOGACANIE
    x->_size=y->_size;
    y->_size=y->l->_size+y->r->_size+1;

}
void TreeMap::left_rot(treeNode* x) {
    treeNode* y=x->r;
    x->r=y->l;
    if(y->l!=nil)
        y->l->p=x;
    y->p=x->p;
    if(x->p==nil)
        root=y;
    else if(x==x->p->l)
        x->p->l=y;
    else x->p->r=y;
    y->l=x;
    x->p=y;
    ///WZBOGACANIE
    y->_size=x->_size;
    x->_size=x->l->_size+x->r->_size+1;
}
void TreeMap::RB_insert(treeNode* x) {
    treeInsert(x);
///RED 0   BLACK 1
    x->color=0;
    treeNode* y=nil;
    while(x!=root&&x->p->color==0) { //root must be black or guardian with
        if(x->p==x->p->p->l ) {
            y=x->p->p->r;
            if(y->color==0)
                ///PRZYPADEK_1
            {
                x->p->color=1;
                y->color=1;
                x->p->p->color=0;
                x=x->p->p;
            } else {
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
            } else {
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
void TreeMap::RB_delete_fixup(treeNode* x) {
    treeNode* w=nil;
    while(x!=root&&x->color==1) {
        if(x==x->p->l) {
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
            } else {
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
        } else
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
            } else {
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
treeNode* TreeMap::RB_delete(treeNode* z) {
    ///if (z==nil)return z;
    treeNode* y=z;
    while(y!=nil) {
        --y->_size;
        y=y->p;
    }
    ///
    treeNode* x=nil;
    y=nil;
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
        z->data=y->data;
    if(y->color==1)RB_delete_fixup(x);
    return y;
}
treeNode* TreeMap::OS_select(treeNode* x,int i) {
    int r=x->l->_size+1;
    if(i==r)return x;
    else if(i<r) return OS_select(x->l,i);
    else return OS_select(x->r,i-r);
}
int TreeMap::OS_rank(treeNode* x) {
    int r=x->l->_size+1;
    treeNode* y=x;
    while(y!=root) {
        if(y==y->p->r) {
            r=r+y->p->l->_size+1;
            y=y->p;
        }
    }
    return r;
}
std::pair<TreeMap::iterator, bool> TreeMap::insert(const std::pair<Key, Val>& entry) {
    treeNode* x=treeSearch(root,entry.first);
    if(x->data.second==entry.second) {
        iterator i(x);
        return std::MP(i, (bool)false);
    }
    treeNode* xx=new treeNode(entry,nil,nil,nil);
    xx->datapointer=&bank;
    RB_insert(xx);
    iterator i(xx);
    return std::MP(i, (bool)true);
}
TreeMap::iterator TreeMap::unsafe_insert(const std::pair<Key, Val>& entry) {
    ///@todo  Finnish this
    treeNode* xx=new treeNode(entry,nil,nil,nil);
    xx->datapointer=&bank;
    RB_insert(xx);
    iterator i(xx);
    return i;
}
TreeMap::iterator TreeMap::find(const Key& k) {
    ///@todo Implement this
    //treeNode*x=treeSearch(root,k);
    treeNode* x=root;
    while(k!=x->data.first){
    if(x==nil)break;
    if(k<x->data.first)x=x->l;
    else x=x->r;
    }

    cerr<<"find  "<<x->data.ST<<" "<<x->data.ND<<endl;
    cerr<<"find  "<<nil->data.ST<<" "<<nil->data.ND<<endl;
if(x==nil)return end();
    iterator i(x);
    return i;
}
TreeMap::const_iterator TreeMap::find(const Key& k) const {

    //sth wrong
    const_iterator i=find(k);
    return i;
}
TreeMap::Val& TreeMap::operator[](const Key& k) {
    ///@todo Implement this
   treeNode* x=root;
    while(k!=x->data.first){
    //cerr<<"[]  "<<x->data.ST<<" "<<x->data.ND<<endl;
    if(x==nil){//cerr<<"przerwanie";
    break;}
    if(k<x->data.first)x=x->l;
    else x=x->r;
    };
    //cerr<<(x==nil);//<<root->p;
    //cerr<<"cotojest";
    if(x==nil)
     {
//cerr<<"dodawanko";
        treeNode* xx=new treeNode(MP(k,"WOW"),nil,nil,nil);
    xx->datapointer=&bank;
    RB_insert(xx);
        ///insert(MP(k,""));
        return xx->data.second;
    }
    else return (x->data.ND);

}
bool TreeMap::empty( ) const {
    return root==nil;
}
TreeMap::size_type TreeMap::size( ) const {
    return root->_size;
}
TreeMap::size_type TreeMap::count(const Key& _Key) const {
    return nil!=find(_Key).node;  // this is not a multimap
}
TreeMap::iterator TreeMap::erase(TreeMap::iterator i) {
iterator ii=i;
++ii;
    if(RB_delete(i.node))
    return ii;
    else return i;
}
TreeMap::iterator TreeMap::erase(TreeMap::iterator f, TreeMap::iterator l) {
    ///@todo Implement this
    assert(0);
    return end();
}
TreeMap::size_type TreeMap::erase(const Key& key) {
    treeNode* x=treeSearch(root,key);
if(x==nil)return 0;
    RB_delete(x);
    return 1;
}
void TreeMap::clear( ) {
    TreeMapDetail::erase(this, 0);
    ///@todo Implement this
    // assert(0);
}
bool TreeMap::struct_eq(const TreeMap& another) const {
    ///@todo Implement this
    assert(0);
    return false;
}
bool TreeMap::info_eq(const TreeMap& another) const {
    ///@todo Implement this
    assert(0);
    return false;
}
TreeMap::const_iterator& TreeMap::const_iterator::operator ++() {
    ///@todo

    treeNode*x=node;
    treeNode*nil=node->datapointer->nil;
    treeNode*root=node->datapointer->root;
    if (x->data.first==INF)return *this;
    if(x->r!=nil) node=treeMinimum(x->r,nil,root);
    else {
        treeNode* y=x->p;
        while(y!=nil&& x==y->r) {
            x=y;
            y=y->p;
        }
        node=y;
    }
    return *this;
}
TreeMap::const_iterator TreeMap::const_iterator::operator++(int) {
    ///@todo Implement this
    return *this;
}
TreeMap::const_iterator& TreeMap::const_iterator::operator--() {
    treeNode* x=treePredescor(node,node->datapointer->nil,node->datapointer->root);
    if(x->data.first<=node->data.first)node=x;
    return *this;
}
TreeMap::const_iterator TreeMap::const_iterator::operator--(int) {
    ///@todo Implement this
    return *this;
}
TreeMap& TreeMap::operator=(const TreeMap& other) {
    ///@todo Implement this
    return *this;
}
TreeMap::iterator TreeMap::begin() {
    ///@todo Implement this
    return iterator(treeMinimum(root,nil,root));
}
TreeMap::const_iterator TreeMap::begin() const {
    ///@todo Implement this
    //return iterator(treeMinimum(root));
    return const_iterator(treeMinimum(root,nil,root));
}
TreeMap::iterator TreeMap::end() {
    ///@todo Implement this
    return iterator(treeMaximum(root,nil,root));
}
TreeMap::const_iterator TreeMap::end() const {
    ///@todo Implement this
    return const_iterator(treeMaximum(root,nil,root));
}
