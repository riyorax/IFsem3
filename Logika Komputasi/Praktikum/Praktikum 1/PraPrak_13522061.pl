/*BAGIAN I: Fakta, Rule, dan Query*/
/*Fakta*/
pria(athif).
pria(henri).
pria(michael).
pria(robert).
pria(bagas).
pria(daniel).
pria(rupert).
pria(dillon).
pria(hanif).
pria(fio).

wanita(joli).
wanita(margot).
wanita(jena).
wanita(elysia).
wanita(ana).
wanita(jeni).
wanita(emma).

usia(athif,60).
usia(joli,58).
usia(henri,48).
usia(margot,43).
usia(michael,28).
usia(robert,32).
usia(bagas,29).
usia(jena,27).
usia(fio,30).
usia(jeni,28).
usia(ana,23).
usia(daniel,7).
usia(rupert,6).
usia(emma,6).
usia(dillon,63).
usia(elysia,500).
usia(hanif,47).

menikah(athif,joli).
menikah(joli,athif).
menikah(dillon,elysia).
menikah(elysia,dillon).
menikah(henri,margot).
menikah(margot,henri).
menikah(jena,fio).
menikah(fio,jena).
menikah(jeni,fio).
menikah(fio,jeni).

anak(margot,athif).
anak(margot,joli).
anak(michael,athif).
anak(michael,joli).
anak(hanif,dillon).
anak(hanif,elysia).
anak(robert,henri).
anak(robert,margot).
anak(bagas,henri).
anak(bagas,margot).
anak(jena,henri).
anak(jena,margot).
anak(jeni,hanif).
anak(ana,hanif).
anak(daniel,fio).
anak(daniel,jena).
anak(rupert,fio).
anak(rupert,jena).
anak(emma,fio).
anak(emma,jeni).

/*Rule*/
saudara(X,Y):-
    anak(X,Z),
    anak(Y,Z),
    X \= Y.

saudaratiri(X,Y):-
    anak(X,A),
    anak(X,B),
    anak(Y,C),
    anak(Y,D),
    A \= B,
    C \= D,
    A = C,
    B \= D.

kakak(X,Y):-
    saudara(X,Y),
    usia(X,A),
    usia(Y,B),
    A>B.

keponakan(X,Y):-
    anak(X,Z),
    saudara(Y,Z).

mertua(X,Y):-
    anak(Z,X),
    menikah(Y,Z).

nenek(X,Y):-
    wanita(X),
    anak(Z,X),
    anak(Y,Z).

keturunan(X,Y):-
    anak(X,Y).
keturunan(X,Y):-
    anak(X,Z),
    keturunan(Z,Y).

lajang(X):-
    pria(X),
    \+menikah(X,_).

lajang(X):-
    wanita(X),
    \+menikah(X,_).

anakbungsu(X,Y):-
    anak(X,Y),
    \+kakak(X,_).

yatimpiatu(X):-
    pria(X),
    \+anak(X,_).

yatimpiatu(X):-
    wanita(X),
    \+anak(X,_).

/*BAGIAN II: Rekursivitas*/
/*Exponent*/
exponent(_,0,1).
exponent(X,Y,Z):-
    A is Y-1,
    exponent(X,A,B),
    Z is X*B.

/*Population*/
population(P,_,0,_,P).
population(P,R,T,C,X):-
    NewT is T-1,
    B is T mod 2,
    B =:= 0,
    NewC is C+1,
    NewP is P*R-NewC,
    population(NewP,R,NewT,NewC,X),!.
    
population(P,R,T,C,X):-
    NewT is T-1,
    B is T mod 2,
    B =:= 1,
    NewC is C+1,
    NewP is P*R+NewC,
    population(NewP,R,NewT,NewC,X),!.

/*Perrin*/
perrin(0,3).
perrin(1,0).
perrin(2,2).
perrin(N,X):-
    A is N-2,
    B is N-3,
    perrin(A,X1),
    perrin(B,X2),
    X is X1+X2.

/*HCF*/
hcf(0,A,A):-!.
hcf(A,B,X):-
    A>=B,
    X1 is A-B,
    hcf(X1,B,X),!.
hcf(A,B,X):-
    A<B,
    X1 is B-A,
    hcf(X1,A,X),!.

/*BAGIAN III: List*/
/*List Statistic*/
min([H|T],H):-T=[],!.
min([H|T],A):-
    min(T,B),
    H=<B,
    A is H,!.
min([H|T],A):-
    min(T,B),
    H>B,
    A is B,!.

max([H|T],H):-T=[],!.
max([H|T],A):-
    max(T,B),
    H>=B,
    A is H,!.
max([H|T],A):-
    max(T,B),
    H<B,
    A is B,!.

range(List,Range):-
    min(List,Min),
    max(List,Max),
    Range is Max-Min.

count([],0):-!.
count([_|T],Count):-
    count(T,X),
    Count is 1+X.

sum([],0):-!.
sum([H|T],Sum):-
    sum(T,X),
    Sum is H+X.

/*List Manipulation*/

getIndex([H|T],SearchedElement,Index):-
    H = SearchedElement,!,
    Index is 1.
getIndex([H|T],SearchedElement,Index):-
    H \= SearchedElement,
    getIndex(T,SearchedElement,NewIndex),
    Index is NewIndex + 1.  

getElement(List, 1, Result):-
    List = [H|T],
    Result is H,!.
getElement(List, Index, Result):-
    List = [H|T],
    A is Index - 1,
    getElement(T, A, Result).

setElement(List, 1, Element, NewList) :-
    List = [H|T],
    NewList = [Element|T],!.
setElement(List, Index, Element, NewList) :-
    List = [H|T],
    A is Index - 1,
    setElement(T, A, Element, Temp),
    NewList = [H|Temp].

swap(List,Index,Index, List):-!.
swap(List,Index1,Index2,NewList):-
    Index2 < Index1,
    swap(List,Index2,Index1,NewList).
swap(List,Index1,Index2,NewList):-
    getElement(List,Index1,X1),
    getElement(List,Index2,X2),
    setElement(List,Index1,X2,TempList1),
    setElement(TempList1,Index2,X1,NewList),!.

slice(_,Start,End,[]) :-
    Start >= End.
slice([], _, _, []).
slice([H|T],1,End,[H|Result]) :-
    Next is End - 1,
    slice(T,1,Next,Result).
slice([H|T],Start,End,Result) :-
    Start > 1,
    NewStart is Start - 1,
    NewEnd is End - 1,
    slice(T,NewStart,NewEnd,Result).