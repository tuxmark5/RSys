========================
TSPi naudojimo ataskaita
========================

Komanda: *ReSoft*

Sistema: *RSys*

Komandos nariai:

+   Vytautas Astrauskas (PS2)
+   Martynas Budriūnas (PS3)
+   Justinas Jucevičius (PS3)
+   Egidijus Lukauskas (PS2)
+   Audrius Šaikūnas (PS3)

Komandos naudotos TSPi praktikos
================================

+   Komandos tikslų suformulavimas ir dokumentavimas.
+   Komunikavimo procedūrų apibrėžimas.
+   Produkto kūrimo strategijos ruošimas.
+   Produkto kūrimo plano ir tvarkaraščio ruošimas.
+   Kokybės planavimas ir valdymas.
+   Reikalavimų specifikacijos ruošimas.
+   Projektavimas.

Pastabos apie tai, kaip buvo vykdytos praktikos
===============================================

Komandos išsikelti tikslai
--------------------------

+   Suplanuotas programos dydis nuo realaus skiriasi ne daugiau 20 %.
+   Defektų tankis ne didesnis nei 1 defektas 100 kodo eilučių.
+   Suplanuoti 2 ciklo pabaigą 2 savaičių tikslumu.
+   Programavimo greitis ne mažesnis nei 50 eilučių per valandą.

Komunikavimo procedūrų apibrėžimas
----------------------------------

Komanda reguliariai susitikdavo kiekvieną ketvirtadienį prieš paskaitas.
Susitikimų metu buvo aptariami užsakovo atsakymai į klausimus, aiškinamasi
sudėtingesnės problemos (pavyzdžiui, dviprasmybės reikalavimuose),
suderinama kaip turėtų sąveikauti sistemos dalys. Formalios ataskaitos
per susitikimus nebuvo naudojamos, nes svarbiausią informaciją buvo
galima gauti efektyviau: kaip kam sekasi dirbti „matosi“ versijų
kontrolės sistemoje, informacija apie problemas buvo skelbiama iš
karto, vos tik jas pastebėjus bendravimo platformoje.

Ne susitikimų metu, komanda bendravo naudodama Google Wave bendravimo
platformą.

Produkto kūrimo strategijos ruošimas
------------------------------------

Renkantis strategiją, buvo nuspręsta, kad yra svarbūs šie dalykai:

+   galimybė dirbti visiškai atskirai (vienam žmogui atsiradusios problemos,
    nestabdo kitų darbo);
+   kiekvieno ciklo pabaigoje turima sistema, su kuria galima kažką
    padaryti;

TODO: Aprašyti ciklus. (Kūrimo strategija.)
TODO: Koncepcinis projektas. (Skaidymas į modulius ir klases.)

+   Produkto kūrimo strategijos ruošimas:
    
    +   paruošti koncepcinį projektą;
    +   parinkti kūrimo strategiją;
    +   produkto dydžio prognozavimas;

+   Kokybės planavimas ir valdymas:
    
    +   defektų kiekiai programų išeities tekstuose;
    +   testavimui ir kūrimui sugaištas laikas;

    TODO: Realiai iš šito nieko nesigavo, nes QtCreator rodo klaidas,
    nemoku programuoti C++0x.


Pastabos apie tai, kodėl kai kurios praktikos nebuvo vykdytos
=============================================================

+   *Rolių ir jų atsakomybių apibrėžimas ir priskyrimas* buvo vykdytas tik
    neformaliai. Buvo nuspręsta nenaudoti TSPi rolių, nes komandos
    narių sugebėjimai nesutapo su tuo ko reikia rolėms ir pasiskirstymas
    pagal roles būtų buvęs labai neefektyvus. (Pavyzdžiui, Vytautas
    rūpinosi įrankiais, kurie palaiko reikalavimų apdorojimo ir
    defektų fiksavimo procesus, o Audrius – kompiliatoriais,
    bibliotekomis ir panašiai, nors šios abi veiklos turėtų būti atliekamos
    palaikymo vadovo.) Kadangi komandos nariai yra pakankamai atsakingi,
    tai nebeliko poreikio formaliai apibrėžinėti kas, ką ir iki kada turi
    padaryti – pakakdavo susitarti žodžiu, o tai sutaupė nemažai laiko,
    kurį galima buvo panaudoti sistemos tobulinimui.

+   *Projekto progreso sekimas.* Šios praktikos buvo atsisakyta, dėl
    galimybės dirbti tolygiai nebuvimo. Pavyzdžiui, savaitę, kai buvo
    kokio nors dalyko kontrolinis, sistemos kūrimo komandos narys
    galėdavo paskirti tik kelias valandas, tuo tarpu, savaitę kurią
    nebūdavo kontrolinio – kelias dienas. Dėl to planavimas formaliai
    nebuvo vykdomas. Pastebėtos problemos buvo arba pranešamos
    visiems bendravimo platformoje, arba užfiksuojamos riktų
    stebėjimo sistemoje.

+   *Komandos proceso evoliucionavimo / pritaikymo plano paruošimas ir jo
    įgyvendinimas*

+   *Produkto kūrimo plano ir tvarkaraščio ruošimo* praktika nebuvo vykdyta
    dėl to, kad daugumai naudojamos technologijos buvo naujos, dėl ko
    planavimas tampa praktiškai neįmanomu. (Dabar galima būtų pasakyti,
    kad kai kurių veiklų reali užbaigimo data po planuotos būtų buvusi net
    pora savaičių vėliau.) Vietoj to, komanda stengėsi sudėlioti
    užduotis taip, kad problemos iškilusios vienam žmogui netrukdytų
    dirbti kitiems. Tam itin padėjo versijų kontrolės „šakų“ naudojimas.

+   *Rizikų įvertinimas ir valdymas.*

.. _KT:


Pastabos
========

Buvo fiksuojami tik tie defektai, kurie pateko į versijų kontrolės
sistemą. Toks sprendimas priimtas dėl dviejų priežasčių:

+   komandos naudota IDE QtCreator sugeba realiu laiku parodyti vietas,
    kuriose yra tikėtinos kompiliavimo klaidos;
+   dalis komandos narių dėl mažos darbo su C++ patirties „sumalė“
    kodavimo, kompiliavimo ir testavimo stadijas į vieną. (Kartais
    per visas tris sugebėdavo „pareiti“ greičiau nei per 1 minutę.)

Taip pat, dėl antrosios priežasties, fiksuojant laiką buvo laikoma, kad
kodavimo, kompiliavimo ir modulių testavimo stadijos yra kodavimo
stadija. Testavimo stadija fiksuojant laiką buvo išskirta tik, kai
buvo vykdomas jau surinktos sistemos testavimas, arba jos dalių
kodo peržiūra.

Skaičiuojant eilutes nebuvo kreipiamas dėmesys į jų turinį. Tai yra
komentarų bei tuščios eilutės irgi buvo įskaičiuotos.
