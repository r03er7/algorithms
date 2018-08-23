#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

// Dwa z najczesciej uzywanych typow o dlugich nazwach - ich skrocenie jest bardzo istotne
typedef vector<int> VI;
typedef long long LL;

// W programach bardzo rzadko mozna znalezc w pelni zapisana instrukcje petli. Zamiast niej, wykorzystywane sa trzy nastepujace makra:
// FOR - petla zwiekszajaca zmienna x od b do e wlacznie
#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
// FORD - petla zmniejszajaca zmienna x od b do e wlacznie
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
// REP - petla zwiekszajaca zmienna x od 0 do n. Jest ona bardzo czesto wykorzystywana do konstruowania i przegladania struktur danych
#define REP(x, n) for(int x = 0; x < (n); ++x)
// Makro VAR(v,n) deklaruje nowa zmienna o nazwie v oraz typie i wartosci zmiennej n. Jest ono czesto wykorzystywane podczas operowania na iteratorach struktur danych z biblioteki STL, ktorych nazwy typow sa bardzo dlugie
#define VAR(v, n) __typeof(n) v = (n)
// ALL(c) reprezentuje pare iteratorow wskazujacych odpowiednio na pierwszy i za ostatni element w strukturach danych STL. Makro to jest bardzo przydatne chociazby w przypadku korzystania z funkcji sort, ktora jako parametry przyjmuje pare iteratorow reprezentujacych przedzial elementow do posortowania.
#define ALL(c) (c).begin(), (c).end()
// Ponizsze makro sluzy do wyznaczania rozmiaru struktur danych STL. Uzywa sie go w programach, zamiast pisac po prostu x.size() z uwagi na fakt, iz wyrazenie x.size() jest typu unsigned int i w przypadku porownywania z typem int, w procesie kompilacji generowane jest ostrzezenie.
#define SIZE(x) ((int)(x).size())
// Bardzo pozyteczne makro, sluzace do iterowania po wszystkich elementach w strukturach danych STL.
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
// Skrot - zamiast pisac push_back podczas wstawiania elementow na koniec struktury danych, takiej jak vector, wystarczy napisac PB
#define PB push_back
// Podobnie - zamiast first bedziemy pisali po prostu ST
#define ST first
// a zamiast second - ND.
#define ND second
// Stala EPS jest uzywana w wielu algorytmach geometrycznych do porownywania wartosci bliskich zera
const double EPS = 10e-9;
int sgn(LL x) { if (x==0LL) return 0; return (x>0LL) ? 1 : -1;}
// Funkcja sprawdza, czy podana liczba jest dostatecznie bliska 0
inline bool IsZero(double x){ return x>=-EPS && x<=EPS; }
int sgn(double x){ return IsZero(x)?0:(x < 0 ? -1 : 1); }
int sgn(int x){ return !x?0:(x < 0 ? -1 : 1); }
// Funkcja sluzaca do wyznaczania najwiekszego wspolnego dzielnika dwoch liczb
LL GCD(LL a,LL b) { 
	while(b) swap(a%=b,b);
	return a;
}
// Implementacja struktury BigNum, realizujacej arytmetyke wielkich liczb
struct BigNum {
// Makro sluzace do eliminowania wiodacych zer
#define REDUCE() while(len>1 && !cyf[len-1]) len--;
// Podstawa, przy ktorej wykonywane sa obliczenia oraz liczba zer w podstawie
    static const int BASE=1000000000, BD=9;
// Zmienna len reprezentuje aktualna dlugosc liczby (liczbe cyfr), a al wielkosc zaalokowanej pamieci do przechowywania cyfr liczby
    int len, al;
// Wskaznik do tablicy cyfr liczby
    LL* cyf;
// Konstruktor liczby o wartosci v i zaalokowanej pamieci dla l cyfr
	BigNum(int v=0, int l=2) : len(1), al(l), cyf(new LL[l]) {
		REP(x,al) cyf[x]=0;
		if ((cyf[0]=v)>=BASE) przen(1);
    }
// Konstruktor, przypisujacy wartosc innej liczby typu BigNum
	BigNum(const BigNum &a) : len(a.len), al(len), cyf(new LL[al]) {
		REP(x,al) cyf[x]=a.cyf[x];
    }
// Destruktor
    ~BigNum(){delete cyf;}
// Funkcja przyjmuje jako parametr zapotrzebowanie na liczbe cyfr i jesli zapotrzebowanie jest wieksze od aktualnego rozmiaru tablicy cyfr, to dokonuje realokacji
    void Res(int l) {
		if (l>al) {
			LL* n = new LL[l=max(l,2*al)];
			REP(x,l) n[x] = x>=al ? 0 : cyf[x];
			delete cyf;
			cyf = n;
			al = l;
		}
    }
// Funkcja dokonuje przenoszenia do starszych cyfr nadmiaru powstalego na skutek wykonywania operacji. Jest to jedyne miejsce w calej strukturze, gdzie wykonuje sie ta operacje. Parametr okresla liczbe cyfry, do ktorej nalezy wykonac przenoszenie nadmiaru
    void przen(int p) {
		int	x=0;
		for(;x<p || cyf[x]<0 || cyf[x]>=BASE;x++) {
			Res(x+2);
// W razie potrzeby wykonaj zapozyczenie od starszej cyfry...
			if(cyf[x]<0){LL i=(-cyf[x]-1)/BASE+1; cyf[x]+=i*BASE; cyf[x+1]-=i;}else
// lub wykonaj przeniesienie powstalego nadmiaru
			if(cyf[x]>=BASE){LL i=cyf[x]/BASE; cyf[x]-=i*BASE; cyf[x+1]+=i;}
		}
		len=max(len,x+1);
		REDUCE();
    }
// Od tego miejsca zaczyna sie implementacja operatorow. Przepisywanie tej czesci kodu nie jest wymagane - nalezy przepisywac tylko te operatory, z ktorych sie korzysta. Niektore operatory korzystaja z innych - w takich przypadkach, przy kazdym operatorze napisane jest, implementacji jakich operatorow on wymaga
// Ponizsze makro pozwala skrocic zapis naglowkow operatorow
#define OPER1(op) bool operator op (const BigNum &a) const

// Operatory porownawcze	
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
// Operator ten wymaga implementacji operatora <(BigNum)
    OPER1(>) { return a<*this; }
// Operator ten wymaga implementacji operatora <(BigNum)
    OPER1(<=) { return !(a<*this); }
// Operator ten wymaga implementacji operatora <(BigNum)
    OPER1(>=) { return !(*this<a); }
// Operator ten wymaga implementacji operatora ==(BigNum)
    OPER1(!=) { return !(*this==a); }

// Operacje dla liczb typu int
BigNum &operator=(int a) {
		REP(x,len) cyf[x]=0;
		len=1;
		if (cyf[0]=a>=BASE) przen(1);
		return *this;
    }
    void operator+=(int a){cyf[0]+=a; przen(1);}
    void operator-=(int a){cyf[0]-=a; przen(1);}
    void operator*=(int a){REP(x,len) cyf[x]*=a; przen(len);}
// Ponizszy operator zwraca jako wynik reszte z dzielenia liczby typu BigNum przez liczbe typu int
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
// Operacje wylacznie na liczbach typu BigNum
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
// Operator ten wymaga implementacji nastepujacych operatorow: <(BigNum), +=(BigNum), *=(BigNum), +(BigNum), *(BigNum), <<(int), <<=(int)
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
// Operator ten wymaga implementacji nastepujacych operatorow: <(BigNum), +=(BigNum), *=(BigNum), +(BigNum), *(BigNum), <<(BigNum), <<=(BigNum)
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
// Operatory sluzace do wczytywania i wypisywania liczb
// Funkcja przypisuje liczbie BigNum wartosc liczby z przekazanego wektora, zapisanej przy podstawie p
// Operator ten wymaga implementacji +=(int), *=(int)
    void read(const VI &v,int p) {
		*this=0;
		FORD(x,SIZE(v),0) {
			*this *= p;
		    *this += v[x];
		}
	}
// Funkcja przypisuje liczbie BigNum wartosc liczby z napisu zapisanego przy podstawie 10
// Operator ten wymaga implementacji =(int)
    BigNum &operator=(string a) {
		int s=a.length();
		*this=0;
		Res(len=s/BD+1);
		REP(x,s) cyf[(s-x-1)/BD]=10*cyf[(s-x-1)/BD]+a[x]-'0';
		REDUCE();
		return *this;
    }
// Funkcja wypisuje wartosc liczby BigNum zapisanej przy podstawie 10
    void write() const {
		printf("%d", int(cyf[len-1]));
		FORD(x,len-2,0) printf("%0*d", BD, int(cyf[x]));
	}
// Funkcja wypisuje do przekazanego bufora wartosc liczby zapisanej przy podstawie 10
	void write(char *buf) const {
		int p = sprintf(buf, "%d", int(cyf[len-1]));
		FORD(x,len-2,0) p += sprintf(buf+p, "%0*d", BD, int(cyf[x]));
    }
// Funkcja zwraca wektor cyfr liczby zapisanej przy podstawie pod. Funkcja ta wymaga implementacji /=(int), =(BigNum)
	VI write(int pod) const {
		VI w;
		BigNum v;
		v=*this;
		while(v.len>1 || v.cyf[0]) w.PB(v/=pod);
		return w;
    }
// Operator przesuniecia w prawo o n cyfr
	BigNum &operator>>=(int n) {
		if(n>=len) n=len;
		REP(x,len-n) cyf[x]=cyf[x+n];
		FOR(x,len-n,n) cyf[x]=0;
		len-=n;
		if(len==0) len=1;
		return *this;
	}
// Operator przesuniecia w lewo
	BigNum &operator<<=(int n) {
		if(cyf[0]==0 && len==1) return *this;
		Res(len+n);
		FORD(x,len-1,0) cyf[x+n]=cyf[x];
		REP(x,n) cyf[x]=0;
		len+=n;
		return *this;
	}
// Funkcja wyznaczajaca pierwiastek calkowity z liczby
// Funkcja ta wymaga implementacji <(BigNum), +=(BigNum), *=(BigNum), <<=(int), +(BigNum), *(BigNum), <<(int)
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
// Makra pozwalajace na skrocenie zapisu naglowkow ponizszych operatorow
#define OPER3(op) BigNum operator op(const BigNum &a) \
	const {BigNum w=*this;  w op ## = a;  return w; }
#define OPER4(op) BigNum operator op(int a) \
	{BigNum w = *this; w op ## = a; return w; }
// Operator wymaga implementacji +=(BigNum)
    OPER3(+);
// Operator wymaga implementacji -=(BigNum)
	OPER3(-);
// Operator wymaga implementacji *=(BigNum)
    OPER3(*);
// Operator wymaga implementacji <(BigNum), +=(BigNum), *=(BigNum), /=(BigNum), +(BigNum), *(BigNum), <<(int)
    OPER3(/);
// Operator wymaga implementacji <(BigNum), +=(BigNum), -=(BigNum), *=(BigNum), /=(BigNum), %=(BigNum), +(BigNum), *(BigNum)
    OPER3(%);
// Operator wymaga implementacji <<=(int)
    OPER4(<<);
// Operator wymaga implementacji >>=(int)
	OPER4(>>);
};
// Implementacja liczb calkowitych bazujaca na typie BigNum
struct Integer{
    BigNum x;
// Znak liczby (-1 dla liczby ujemnej, 0 dla zera, 1 dla liczby dodatniej)
    int Sgn;
// Konstruktor, przyjmujacy jako parametry wartosc bezwzgledna oraz znak tworzonej liczby
	Integer(const BigNum &a, int s=1) {x = a; Sgn = (a == BigNum(0)) ? 0 : !s ? 1 : s;}
// Konstruktor tworzacy zmienna rowna liczbie a
    Integer(int a = 0){x = BigNum(abs(a)); Sgn = sgn(a);}
// Operator zwraca liczbe o przeciwnym znaku
    Integer operator-() const {return Integer(x, -Sgn);}
// Operatory porownawcze
    bool operator<(const Integer &b) const{
      if (Sgn != b.Sgn) return Sgn < b.Sgn;
	  return (Sgn == -1) ? b.x < x : x < b.x;
    }
    bool operator==(const Integer &b) const{return Sgn == b.Sgn && x == b.x;}
// Makra pozwalajace na skrocenie zapisu naglowkow operatorow
#define OPER5(op) Integer operator op (const Integer &b) const 
#define OPER6(op) Integer &operator op ## = (const Integer &b) \
	{return *this = *this op b;}
// Operator +(Integer)
	OPER5(+) {
      if (Sgn == -1) return -(-(*this) + (-b));
      if (b.Sgn >= 0) return Integer(x + b.x, min(1, Sgn + b.Sgn));
      if (x < b.x) return Integer(b.x - x, -1);
      return Integer(x - b.x, x > b.x);
    }
// Operator -(Integer), wykorzystuje +(Integer)
    OPER5(-) {return *this + (-b);}
// Operator *(Integer)
    OPER5(*){ return Integer(x*b.x, Sgn*b.Sgn);} 
// Operator /(Integer)
	OPER5(/){ return Integer(x/b.x, Sgn*b.Sgn);} 
// Operator %(Integer), wykorzystuje -(Integer)
    OPER5(%){ return Sgn == -1 ? Integer((b.x - (x % b.x)) % b.x) : Integer(x % b.x); }
// Operator +=(Integer), wykorzystuje +(Integer)
    OPER6(+)
// Operator -=(Integer), wykorzystuje -(Integer)
	OPER6(-)
// Operator *=(Integer), wykorzystuje *(Integer)
	OPER6(*)
// Operator /=(Integer), wykorzystuje /(Integer)
    OPER6(/)
// Operator %=(Integer), wykorzystuje %(Integer)
    OPER6(%)
// Funkcja wypisuje liczbe Integer zapisana przy podstawie 10 na standardowe wyjscie
    void write() const{if (Sgn==-1) printf("-"); x.write();}
};

// Funkcja wyznaczajaca najwiekszy wspolny dzielnik dwoch liczb. 
// Jest ona uzywana do skracania ulamkow
BigNum NatGCD(const BigNum &a, const BigNum& b) { 
	return b == BigNum(0) ? a : NatGCD(b, a % b);
} 
// Implementacja liczb ulamkowych, bazujaca na typie Integer oraz BigNum
struct Frac {
// Licznik a oraz mianownik b ulamka
	Integer a, b;
// Konstruktor typu Frac, tworzy liczbe o zadanym liczniku i mianowniku
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
// Operatory porownawcze
	bool operator<(const Frac &x) const { 
		return a*x.b < x.a*b;
	}
	bool operator==(const Frac &x) const { 
		return a == x.a && b == x.b;
	}
// Makra pozwalajace na skrocenie zapisu naglowkow operatorow
#define OPER7(op) Frac operator op (const Frac &x) const 
#define OPER8(op) Frac &operator op ## =(const Frac &b) \
{return *this = *this op b;}
// Operator +(Frac)
	OPER7(+) { 
		return Frac(a * x.b + b * x.a, b * x.b);
	}
// Operator -(Frac)
	OPER7(-) { 
		return Frac(a * x.b - b * x.a, b * x.b);
	}
// Operator *(Frac)
	OPER7(*) { 
		return Frac(a * x.a, b * x.b);
	}
// Operator /(Frac)
	OPER7(/) { 
		return Frac(a * x.b, b * x.a);
	}
// Operator +=(Frac), wykorzystuje +(Integer)
	OPER8(+)
// Operator -=(Frac), wykorzystuje -(Integer)
	OPER8(-)
// Operator *=(Frac), wykorzystuje *(Integer)
	OPER8(*)
// Operator /=(Frac), wykorzystuje /(Integer)
	OPER8(/)
// Funkcja zwraca prawde, jesli dany ulamek jest rowny 0
	bool isZero(){
		return a==Integer(0);
	}
// Funkcja wypisujaca ulamek postaci licznik/mianownik zapisany przy podstawie 
// 10 na standardowe wyjscie
	void write(){
		a.write();
		printf("/");
		b.write();
	}
};
int main() {
// Skonstruuj dwie liczby typu Frac
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
