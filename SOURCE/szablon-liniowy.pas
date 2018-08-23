(* Zadanie SZA (Szablon)
 * Autor: Jakub Radoszewski
 * Data: 15.06.2005
 * Program o z�o�ono�ci czasowej i pami�ciowej O(n),
 * obliczaj�cy d�ugo�ci szablon�w on-line.
 *)

const MAX_LEN = 500000;

(* Deklaracje zmiennych globalnych. *)
var
  pref_suf : array[0..MAX_LEN] of LongInt;
                             {Tablica d�ugo�ci najd�u�szych prefikso-sufiks�w}
                             {tak zwana funkcja prefiksowa).}
  sl : array[1..MAX_LEN] of Char; {Rozwa�ane s�owo.}
  n : LongInt; {D�ugo�� rozwa�anego s�owa.}
  j, b, q : LongInt; {Zmienne pomocnicze programu g��wnego.}
  zakres : array[0..MAX_LEN] of LongInt;
                             {Zakresy s�owa, kt�re mo�na pokry� poszczeg�lnymi}
                             {prefiksami s�owa, jako szablonami.}
  szablony : array[0..MAX_LEN] of LongInt;
                             {Najkr�tsze szablony dla kolejnych}
                             {prefiks�w s�owa.}

procedure odczyt;
var ch : Char;
begin
  n := 0;
  while not Eoln(input) do
  begin
    Read(ch);
    Inc(n);
    sl[n] := ch
  end {while}
end; {odczyt}

(* Procedura wyliczaj�ca warto�ci funkcji prefiksowej
 * dla podanego w parametrze s�owa. *)
procedure licz_pref_suf;
var k, q : LongInt;
begin
	k := 0;
  (* Inicjalizacja funkcji prefiksowej. *)
	pref_suf[0] := 0;
  pref_suf[1] := 0;
  
  (* Wyliczanie kolejnych warto�ci funkcji prefiksowej. *)
	for q := 2 to n do
	begin
    (* Niezmiennik: najd�u�szy prefikso-sufiks prefiksu danego
    s�owa o d�ugo�ci q ma d�ugo�� k. *)
		while (k > 0) and (sl[k + 1] <> sl[q]) do
      k := pref_suf[k];
		if sl[k + 1] = sl[q] then
      Inc(k);
		pref_suf[q] := k
	end {for}
end; {licz_pref_suf}


begin
  (* Odczyt s�owa i wyliczenie funkcji prefiksowej. *)
  odczyt;
  licz_pref_suf;

  (* Obliczanie najkr�tszych szablon�w dla prefiks�w s�owa,
  wykonywane on-line. *)
  for j := 1 to n do
  begin
    szablony[j] := j;
    zakres[j] := j
  end; {for}
  
  (* P�tla po wszystkich, d�u�szych ni� jeden, prefiksach
  danego s�owa - w j-tym kroku rozwa�amy j-ty prefiks. *)
  for j := 2 to n do
  begin
    b := pref_suf[j];
    if b > 0 then
    begin
      (* Sprawdzamy, czy szablon najd�u�szego prefikso-sufiksu
      danego prefiksu s�owa jest dobrym szablonem dla aktualnego
      prefiksu: *)
      q := szablony[b];
      if zakres[q] >= j - q then
      begin
        (* je�eli tak, to wybieramy jego jako szablon, *)
        szablony[j] := q;
        zakres[q] := j
      end {if}
      (* je�eli nie, to ju� jest ustawione szablony[i]=i. *)
    end {if}
  end; {for}
  
  (* Wypisanie wyniku *)
  WriteLn(szablony[n])
end. {program}
