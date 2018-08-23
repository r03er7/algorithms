#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
struct Komp
{
string MAC;
string IP;
string opis;
};
typedef vector<Komp> Lista;
void OczytListy( char *, Lista & );
void OdpytajKomp( char *, Komp );
int Oszukany( char *, Komp);
void doRaportu( char *, ostream & );
main()
{
Lista ListaKomp;
char * nazwaL="lista.komputerow.txt";
char * nazwaP="wynik.odpytania.txt";
OczytListy( nazwaL, ListaKomp );
for( int i=0; i<ListaKomp.size(); i++ )
{
OdpytajKomp( nazwaP, ListaKomp[i] );
if ( Oszukany( nazwaP, ListaKomp[i] ) )
doRaportu( nazwaP, cout );
}
return 0;
}
void OczytListy( char * nazwa, Lista & lista)
{
Komp bufor;
ifstream plik( nazwa );
while( 1 )
{
plik >> bufor.MAC >> bufor.IP;
getline( plik, bufor.opis );
if( plik.eof() ) break;
lista.push_back( bufor );
}
plik.close();
}
void OdpytajKomp( char * nazwa, Komp komp )
{
string pytanie;
pytanie = "nbtstat -A " + komp.IP + " > " + nazwa;
system( pytanie.c_str() );
}
int Oszukany ( char * nazwa, Komp komp)
{
string linia;
ifstream plik(nazwa);
while( getline(plik, linia) )
{
if( linia.find("Adres MAC") != string::npos )
{
if( linia.find(komp.MAC) != string::npos ) return 0;
else return 1;
}
}
plik.close();
return 0;
}
void doRaportu( char * nazwa, ostream & raport)
{
ifstream plik( nazwa );
string buf;
raport << "-------------------------\n"
" Podejrzany komputer\n-------------------------\n";
while( !(getline(plik, buf).eof()) )
{ raport << buf << "\n"; }
plik.close();
}
