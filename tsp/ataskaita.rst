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

TODO:
    Vytautui - quality.rst

+   Naujų rolių apibrėžimas:
    +   Failas: *roles.pdf*
+   Pasiskirtymas rolėmis:
    +   Failas: *roles.pdf*
+   Komandos tikslų suformulavimas ir dokumentavimas:
    +   Failas: *goals.pdf*
+   Rolių tikslų suformulavimas ir dokumentavimas.
    +   Failas: *goals.pdf*
+   Versijų kontrolė:
    +   Galutiniame ruošinyje yra pateikta viso projekto GIT repozitorija
+   Komunikavimo procedūrų apibrėžimas:
    +   Failas: *communication.pdf*
+   Produkto kūrimo strategijos ruošimas.
    +   Failas: *strategy.pdf*
+   Projektavimas.
    +   Failas: *project.pdf*
+   Produkto kūrimo plano ir tvarkaraščio ruošimas.
    +   Failas: *weekly_plan.ods*
+   Reikalavimų valdymas:
    +   Failas: *requirements.pdf*. Prie pateikto ruošinio pridėta spausdina kopija.
+   Savaitinių susitikimų organizavimas ir protokolavimas:
    +   Failai: *ReSoft_2011-XX-XX.txt*. Jie kas savaitę buvo siunčiami TSP instruktoriui.
+   Defektų fiksavimas:
    +   Failas: *defects.ods*
+   Laiko fiksavimas:
    +   Failas: *AudriausLFF.ods*
    +   Failas: *EgidijausLFF.ods*
    +   Failas: *JustinoLFF.ods*
    +   Failas: *MartynoLFF.ods*
    +   Failas: *VytautoLFF.ods*
+   Kodo peržiūra:
    +   Failas: *code_review.pdf*
+   Bendras kodavimo standartas:
    +   Failas: *EAST_STD.txt*
+   Sistemos dydžio vertinimas:
    +   Failas: *size_measurement.pdf*
+   Kokybės planavimas ir valdymas.
    +   Failas: *quality.pdf*


Pastabos apie tai, kaip buvo vykdytos praktikos
===============================================



Reikalavimų specifikacijos ruošimas
-----------------------------------

Programos kūrimo metu buvo naudojami nesusisteminti reikalavimai
(Žmogaus ir kompiuterio sąveikos darbai, užsakovo atsakymai į
klausimus). Vėliau, trečio ciklo metu, reikalavimai buvo susisteminti,
sukelti į reikalavimų valdymo įrankį
`rmtoo <http://www.flonatel.de/projekte/rmtoo/>`_ ir atlikta jų
peržiūra pasinaudojant įrankio pateikiamomis priemonėmis
(reikalavimų pavaizdavimu grafu). Tada, pagal sugeneruotą reikalavimų
specifikaciją, buvo atlikta sistemos peržiūra – ar ji atitinka
nurodytus reikalavimus.

*Pastaba:* Naudotas reikalavimų specifikavimo įrankis nėra
internacionalizuotas, todėl nebuvo galimybės išversti terminų į
lietuvių kalbą. Taip pat, kadangi įrankis pritaikytas naudoti su
SCRUM metodika, jame reikalavimams reikia nurodyti papildomą
informaciją („Priority“, „Owner“, „Invented by“, …),
kurią skaitant šią reikalavimų specifikaciją reikėtų ignoruoti.

Kokybės planavimas ir valdymas
------------------------------

+   Kokybės planavimas ir valdymas:
    
    +   defektų kiekiai programų išeities tekstuose;
    +   testavimui ir kūrimui sugaištas laikas;
    +   kaip buvo vykdomos peržiūros (dokumentų, reikalavimų, kodo,
        dviejų žvejų)

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


