=====================================
Kodo peržiūros ataskaita (2011-12-05)
=====================================

Atlikta komponento **Core** peržiūra, kurios metu užfiksuoti tokie defektai:

+   Blogas apžvalgos sąsajos saugumo deskriptorius lemdavo, kad administratoriaus 
    apribojimai apžvalgos sąsajai nieko nereikšdavo (defektas **#77**).

    +   Klaidą rado: Audrius, Martynas
    +   Vieta: include/RSys/Core/RUser.hh
    +   Lygis: svarbus (P2)

+   Įvedus blogus duomenis į sistemų administravimo sąsają, šis nepateikdavo 
    jokio klaidą paaiškinančio pranešimo (defektas **#78**).

    +   Klaidą rado: Audrius (užfiksuota peržiūros metu), Egidijus (užfiksuota testuojant)
    +   Vieta: src/RSys/Core/RDivision.cc
    +   Lygis: estetinis (P3)

Post-mortem
-----------

Nors oficialiai įforminta tik viena kodo peržiūra, tačiau tokių iš tiesų
buvo atliekama ir daugiau: kodo peržiūras ypač palengvino atlikti Git
versijų kontrolės sistema, kuri leido neperžiūrinėti viso sistemos
kodo nuo pradžios iki galo, o tik paskutinius pakeitimus aktualiose vietose.

Prieš rašant sistemą, buvo suplanuota reguliariai visiems komandos
nariams atlikinėti peržiūras, tačiau vėliau tokios praktikos buvo
atsisakyta peržiūrint tik esminius sistemos komponentus. Tokio
pakeitimo priežastys:

+   per didelis kodo specifiškumas;
+   per didelis sistemos dydis;
+   itin skirtingas komandos narių C++ programavimo kalbos įvaldymo lygis.

