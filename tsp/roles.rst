=====
Rolės
=====

Kadangi tarp komandos narių yra itin skirtingas techninių žinių lygis 
(pvz. tik 2 komandos nariai yra itin gerai įvaldę C++ programavimo kalbą,
1 komandos narys yra gerai įvaldęs lietuvių kalbos kultūros taisykles),
tai standartinės TSPi rolės tokio pobūdžio komandai yra netinkamos.
Todėl yra pateikiamos alternatyvios rolės, iš kurių dalis atitinka
standartines TSPi roles:

+   **Komandos lyderis** (Audrius Šaikūnas). Atsakingas už:

    +   **savaitinių susitikimų organizavimą ir protokolavimą;**
    +   **kūrimo darbų priskyrimą;**
    +   **programavimo aplinkos (kompiliatorių, bibliotekų) paruošimą**.

    Kadangi šis komandos narys turi didžiausią patirtį programuojant
    C++, tai veiklos, tiesiogiai susijusios su šia programavimo kalba, ir
    yra perduodamos komandos lyderiui.

+   **Vidinės kokybės vadovas** (Vytautas Astrauskas). Atsakingas už:

    +   **testavimo organizavimą**;
    +   **defektų registravimą** (defektus turi fiksuoti visi komandos
        nariai, tačiau, radus defektą, apie jį turi būti pranešama
        vidinės kokybės vadovui, kuris, išanalizavęs defekto
        prigimtį, jį užregistruoja);
    +   **kodo kokybės valdymas** (priežiūra, kad kodas atitiktų
        kodavimo standartą).

+   **Išorinės kokybės vadovas** (Martynas Budriūnas). Atsakingas už:

    +   **grafinės sąsajos kokybės užtikrinimą** (naudotojo sąsajos
        peržiūrą ir priežiūrą, kad joje naudojama metafora
        atitiktų dalykinę sritį bei kalbos kultūros taisykles ir
        naudotojo sąsajos panaudojamumo principus);
    +   **dokumentacijos kokybės užtikrinimą**;
    +   **reikalavimų specifikacijos kokybės užtikrinimą**;

    Kadangi šis komandos narys turi didžiausią kalbos kultūros
    žinių kiekį, tai visi artefaktai, kuriuose gali atsirasti tokio
    pobūdžio klaidų, turi būti pateikiami išorinės kokybės
    vadovui, kad šis atliktų peržiūrą ir ištaisytų klaidas,
    kurių kiti komandos nariai gali nepastebėti.

+  **Planavimo vadovas** (Justinas Jusevičius). Atsakingas už:

    +    **planavimo organizavimą**;
    +    **laiko sekimą** (remiantis komandos narių LFF formomis reikia
         apskaičiuoti, kokio dydžio paklaida yra tarp planuoto ir
         realaus laiko, skirto darbams atlikti);
    +    **ciklų planavimas** (remiantis komandos narių nuomonėmis
         reikia suplanuoti 3 darbų atlikimo ciklus);

+    **Reikalavimų vadovas** (Egidijus Lukauskas). Atsakingas už:

    +   **reikalavimų specifikacijos ruošimą**;
    +   **reikalavimų registravimą** (reikia nuolatos stebėti iš užsakovo
        gaunamus atsakymus ir pagal tai registruoti naujus reikalavimus);
    +   **reikalavimų testavimą** (reikia stebėti sistemos kūrimo
        progresą ir fiksuoti, kurie reikalavimai yra įgyvendinti, o
        kurie ne, bei apie tai pranešti komandos lyderiui ir planavimo
        vadovui).

Post-mortem
-----------

Po trijų mėnesių darbo su šiomis rolėmis, galima pakankamai tvirtai
teigti, jog toks rolių išskirstymas buvo pakankamai efektyvus. Ypač
efektyviai suveikė papildytos komandos lyderio, vidinės kokybės vadovo
ir išorinės kokybės vadovo rolės. Šiek tiek daugiau problemų buvo
su planavimo ir reikalavimų vadovų rolėmis, nes norint tinkamai
atlikti šias roles tekdavo stipriai įsigilinti į kuriamos sistemos
architektūros detales, kas turint nedaug C++ programavimo kalbos
patirties buvo pakankamai sudėtinga. Dėl šios priežasties planavimo
ir reikalavimų vadovai pakankamai aktyviai dalyvaudavo savaitiniuose
susitikimuose siekdami tinkamai įgyvendinti jiems pavestus darbus.
Taip pat turbūt verta paminėti, kad komandos apsibrėžtos rolės iki galo
„nepadengė“ visų darbų, kurie yra paskiriami rolėms pagal TSPi.
Pavyzdžiui, įrankio, skirto darbui su reikalavimais, paruošimas darbui
turėtų būti palaikymo vadovo atsakomybė, bet šis darbas komandoje
nebuvo priskirtas nei vienai iš rolių – todėl, atsiradus poreikiui,
jį padarė vidinės kokybės vadovas, nes turėjo šiek tiek patirties
iš ankstesnių programų sistemų inžinerijos darbų.
