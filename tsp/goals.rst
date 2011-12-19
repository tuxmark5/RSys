Komandos išsikelti tikslai
==========================

+   Suplanuotas programos dydis nuo realaus skiriasi ne daugiau 20 %.
+   Defektų tankis ne didesnis nei 1 defektas 100 kodo eilučių.
+   Suplanuoti 2 ciklo pabaigą 2 savaičių tikslumu.
+   Programavimo greitis ne mažesnis nei 50 eilučių per valandą.

Pagal šiuos tikslus komanda nusprendė sistemos kūrimo metu rinkti tokius
duomenis:

+   defektai, kurie „iškeliavo“ į versijų kontrolės sistemą;
+   laikas 5 minučių tikslumu.

Sprendimas fiksuoti tik tuos defektus, kurie pateko į versijų kontrolės
sistemą, priimtas dėl dviejų priežasčių:

+   komandos naudota IDE QtCreator sugeba realiu laiku parodyti vietas,
    kuriose yra tikėtinos kompiliavimo klaidos;







    
+   dalis komandos narių dėl mažos darbo su C++ patirties „sumalė“
    kodavimo, kompiliavimo ir testavimo stadijas į vieną. (Kartais
    per visas tris sugebėdavo „pareiti“ greičiau nei per 1 minutę.)


???
Taip pat, dėl antrosios priežasties, fiksuojant laiką buvo laikoma, kad
kodavimo, kompiliavimo ir modulių testavimo stadijos yra kodavimo
stadija. Testavimo stadija fiksuojant laiką buvo išskirta tik, kai
buvo vykdomas jau surinktos sistemos testavimas, arba jos dalių
kodo peržiūra.