#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

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
const double EPS = 10e-9;
int sgn(LL x) { if (x==0LL) return 0; return (x>0LL) ? 1 : -1;}
inline bool IsZero(double x){ return x>=-EPS && x<=EPS; }
int sgn(double x){ return IsZero(x)?0:(x < 0 ? -1 : 1); }
int sgn(int x){ return !x?0:(x < 0 ? -1 : 1); }
LL GCD(LL a,LL b) { 
	while(b) swap(a%=b,b);
	return a;
}
struct BigNum {
#define REDUCE() while(len>1 && !cyf[len-1]) len--;
    static const int BASE=1000000000, BD=9;
    int len, al;
    LL* cyf;
	BigNum(int v=0, int l=2) : len(1), al(l), cyf(new LL[l]) {
		REP(x,al) cyf[x]=0;
		if ((cyf[0]=v)>=BASE) przen(1);
    }
	BigNum(const BigNum &a) : len(a.len), al(len), cyf(new LL[al]) {
		REP(x,al) cyf[x]=a.cyf[x];
    }
    ~BigNum(){delete cyf;}
    void Res(int l) {
		if (l>al) {
			LL* n = new LL[l=max(l,2*al)];
			REP(x,l) n[x] = x>=al ? 0 : cyf[x];
			delete cyf;
			cyf = n;
			al = l;
		}
    }
    void przen(int p) {
		int	x=0;
		for(;x<p || cyf[x]<0 || cyf[x]>=BASE;x++) {
			Res(x+2);
			if(cyf[x]<0){LL i=(-cyf[x]-1)/BASE+1; cyf[x]+=i*BASE; cyf[x+1]-=i;}else
			if(cyf[x]>=BASE){LL i=cyf[x]/BASE; cyf[x]-=i*BASE; cyf[x+1]+=i;}
		}
		len=max(len,x+1);
		REDUCE();
    }
#define OPER1(op) bool operator op (const BigNum &a) const

OPER1(==) {
		if(a.len!=len) return 0;
		REP(x,len) if(cyf[x]!=a.cyf[x]) return 0;
		return 1;
    }
   OPER1(<) { 
		if(len!=a.len) return len<a.len;
		int x=len-1;
		while(x && a.cyf[x]==cyf[x]) x--;
		return cyf[x]<a.cyf[x];
	}
    OPER1(>) { return a<*this; }
    OPER1(<=) { return !(a<*this); }
    OPER1(>=) { return !(*this<a); }
    OPER1(!=) { return !(*this==a); }

BigNum &operator=(int a) {
		REP(x,len) cyf[x]=0;
		len=1;
		if (cyf[0]=a>=BASE) przen(1);
		return *this;
    }
    void operator+=(int a){cyf[0]+=a; przen(1);}
    void operator-=(int a){cyf[0]-=a; przen(1);}
    void operator*=(int a){REP(x,len) cyf[x]*=a; przen(len);}
    int operator/=(int a) {
		LL w=0;
		FORD(p,len-1,0){w=w*BASE+cyf[p]; cyf[p]=w/a; w%=a;}
		REDUCE();
		return w;
    }
    int operator%(int a) {
		LL w=0;
		FORD(p,len-1,0) w=(w*BASE+cyf[p])%a;
		return w;
    }
#define OPER2(op) BigNum& operator op (const BigNum &a)
  OPER2(+=) {
		Res(a.len);
		REP(x,a.len) cyf[x]+=a.cyf[x];
		przen(a.len);
		return *this;
  }
	OPER2(-=) {
		REP(x,a.len) cyf[x]-=a.cyf[x]; 
		przen(a.len);
		return *this;
    }
    OPER2(*=) {
  	BigNum c(0,len+a.len);
		REP(x,a.len) {
			REP(y,len) c.cyf[y+x]+=cyf[y]*a.cyf[x];
			c.przen(len+x);
		}
		*this=c;
		return *this;
	}
    OPER2(/=) { 
		int n=max(len-a.len+1,1);
		BigNum d(0,n), prod;
		FORD(i,n-1,0) {
			int l=0, r=BASE-1;
			while(l<r) {
				int	m=(l+r+1)/2;
				if (*this < prod+(a*m<<i))
					r=m-1;
				else
					l=m;
			}
			prod+=a*l<<i;
			d.cyf[i]=l;
			if (l) d.len = max(d.len, i+1);
		}
		*this=d;
		return *this;
    }
    OPER2(%=) {
		BigNum v=*this;
		v/=a;
		v*=a;
		*this -= v;
		return *this;
	}
    OPER2(=) {
		Res(a.len);
		FORD(x, len-1, a.len) cyf[x]=0;
		REP(x,a.len) cyf[x]=a.cyf[x];
		len=a.len;
		return *this;
 }
    void read(const VI &v,int p) {
		*this=0;
		FORD(x,SIZE(v),0) {
			*this *= p;
		    *this += v[x];
		}
	}
    BigNum &operator=(string a) {
		int s=a.length();
		*this=0;
		Res(len=s/BD+1);
		REP(x,s) cyf[(s-x-1)/BD]=10*cyf[(s-x-1)/BD]+a[x]-'0';
		REDUCE();
		return *this;
    }
    void write() const {
		printf("%d", int(cyf[len-1]));
		FORD(x,len-2,0) printf("%0*d", BD, int(cyf[x]));
	}
	void write(char *buf) const {
		int p = sprintf(buf, "%d", int(cyf[len-1]));
		FORD(x,len-2,0) p += sprintf(buf+p, "%0*d", BD, int(cyf[x]));
    }
	VI write(int pod) const {
		VI w;
		BigNum v;
		v=*this;
		while(v.len>1 || v.cyf[0]) w.PB(v/=pod);
		return w;
    }
	BigNum &operator>>=(int n) {
		if(n>=len) n=len;
		REP(x,len-n) cyf[x]=cyf[x+n];
		FOR(x,len-n,n) cyf[x]=0;
		len-=n;
		if(len==0) len=1;
		return *this;
	}
	BigNum &operator<<=(int n) {
		if(cyf[0]==0 && len==1) return *this;
		Res(len+n);
		FORD(x,len-1,0) cyf[x+n]=cyf[x];
		REP(x,n) cyf[x]=0;
		len+=n;
		return *this;
	}
    BigNum sqrt() {
		int n=(len+1)/2;
		BigNum a(0,n), sq;
		FORD(i,n-1,0) {
		    int l=0, r=BASE-1;
			while(l<r) {
				int m=(l+r+1)/2; 
				if (*this < sq+(a*2*m<<i)+(BigNum(m)*m<<2*i))
				    r=m-1;
				else
					l=m;
			}
		    sq+=(a*2*l<<i)+(BigNum(l)*l<<2*i);
		    a.cyf[i]=l; a.len=n;
		}
		return a;
   }
#define OPER3(op) BigNum operator op(const BigNum &a) \
	const {BigNum w=*this;  w op ## = a;  return w; }
#define OPER4(op) BigNum operator op(int a) \
	{BigNum w = *this; w op ## = a; return w; }
    OPER3(+);
	OPER3(-);
    OPER3(*);
    OPER3(/);
    OPER3(%);
    OPER4(<<);
	OPER4(>>);
};
struct Integer{
    BigNum x;
    int Sgn;
	Integer(const BigNum &a, int s=1) {x = a; Sgn = (a == BigNum(0)) ? 0 : !s ? 1 : s;}
    Integer(int a = 0){x = BigNum(abs(a)); Sgn = sgn(a);}
    Integer operator-() const {return Integer(x, -Sgn);}
    bool operator<(const Integer &b) const{
      if (Sgn != b.Sgn) return Sgn < b.Sgn;
	  return (Sgn == -1) ? b.x < x : x < b.x;
    }
    bool operator==(const Integer &b) const{return Sgn == b.Sgn && x == b.x;}
#define OPER5(op) Integer operator op (const Integer &b) const 
#define OPER6(op) Integer &operator op ## = (const Integer &b) \
	{return *this = *this op b;}
	OPER5(+) {
      if (Sgn == -1) return -(-(*this) + (-b));
      if (b.Sgn >= 0) return Integer(x + b.x, min(1, Sgn + b.Sgn));
      if (x < b.x) return Integer(b.x - x, -1);
      return Integer(x - b.x, x > b.x);
    }
    OPER5(-) {return *this + (-b);}
    OPER5(*){ return Integer(x*b.x, Sgn*b.Sgn);} 
	OPER5(/){ return Integer(x/b.x, Sgn*b.Sgn);} 
    OPER5(%){ return Sgn == -1 ? Integer((b.x - (x % b.x)) % b.x) : Integer(x % b.x); }
    OPER6(+)
	OPER6(-)
	OPER6(*)
    OPER6(/)
    OPER6(%)
    void write() const{if (Sgn==-1) printf("-"); x.write();}
};

BigNum NatGCD(const BigNum &a, const BigNum& b) { 
	return b == BigNum(0) ? a : NatGCD(b, a % b);
} 
struct Frac {
	Integer a, b;
	Frac(const Integer &aa = 0,const Integer &bb = 1) {
		a = aa;
		b = bb;
		if(b < 0) {
			a = -a; 
			b = -b;
		}
		Integer d = Integer(NatGCD(aa.x, bb.x));
		a /= d; 
		b /= d;
	}
	bool operator<(const Frac &x) const { 
		return a*x.b < x.a*b;
	}
	bool operator==(const Frac &x) const { 
		return a == x.a && b == x.b;
	}
#define OPER7(op) Frac operator op (const Frac &x) const 
#define OPER8(op) Frac &operator op ## =(const Frac &b) \
{return *this = *this op b;}
	OPER7(+) { 
		return Frac(a * x.b + b * x.a, b * x.b);
	}
	OPER7(-) { 
		return Frac(a * x.b - b * x.a, b * x.b);
	}
	OPER7(*) { 
		return Frac(a * x.a, b * x.b);
	}
	OPER7(/) { 
		return Frac(a * x.b, b * x.a);
	}
	OPER8(+)
	OPER8(-)
	OPER8(*)
	OPER8(/)
	bool isZero(){
		return a==Integer(0);
	}
	void write(){
		a.write();
		printf("/");
		b.write();
	}
};
int main() {
	Frac a(10, 15);
	Frac b(30, 56);
	cout << "a = ";
	a.write();
	cout << endl << "b = ";
	b.write();
	cout << endl << "a+b = ";
	(a+b).write();
	cout << endl << "a-b = ";
	(a-b).write();
	cout << endl << "a*b = ";
	(a*b).write();
	cout << endl << "a/b = ";
	(a/b).write();
	return 0;
}
