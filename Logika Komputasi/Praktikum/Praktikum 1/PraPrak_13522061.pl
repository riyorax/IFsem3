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
    

kakak(X,Y):-
    saudara(X,Y),
    usia(X,A),
    usia(Y,B),
    A>B.

keponakan(X,Y):-
    anak(X,Z),
    saudara(Y,Z).

mertua(X,Y):-
    anak(Z,X)
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
    \+menikah(X,_).

anakbungsu(X,Y):-
    anak(X,Y),
    \+kakak(X,_).

yatimpiatu(X):-
    \+anak(X,_).

/*BAGIAN II: Rekursivitas*/
/*Exponent*/
exponent(X,0,1).
exponent(X,Y,Z):-
    A is Y-1,
    exponent(X,A,B),
    Z is X*B.

/*Population*/

/*Perrin*/
perrin(0,3).
perrin(1,0).
perrin(2,2).
perrin(N,X):-
    A is N-1,
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
min([H|T],H):-T=[],!
min([H|T],A):-
    min(T,B),
    H<=B,
    A is H,!
min([H|T],A):-
    min(T,B),
    H>B,
    A is B,!

max([H|T],H):-T=[],!
max([H|T],A):-
    max(T,B),
    H>=B,
    A is H,!
max([H|T],A):-
    max(T,B),
    H<B,
    A is B,!

range(List,Range):-
    min(List,Min),
    max(List,Max),
    Range is Max-Min.

count([H|T],1):-T=[],!
count([H|T],Count):-
    count(T,X),
    Count is 1+X.

sum([H|T],H):-T=[],!
sum([H|T],Sum):-
    sum(T,X),
    Sum is H+X.
