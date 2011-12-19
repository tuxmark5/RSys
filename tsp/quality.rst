==============================
Kokybės planavimas ir valdymas
==============================

Kriterijai
==========

Kriterijai, kuriuos tenkinanti sistema, laikoma kokybiška.

+   Paskutinio testavimo metu nerasta nei vieno kritinio defekto
    (kritinis defektas – defektas, dėl kurio sistema sminga, arba
    yra pažeidžiami duomenys).
+   Kompiliavimo metu kompiliatorius nepraneša nei vieno perspėjimo
    (ang. „warning“).
+   Vykdant esmines užduotis su sistema, „valgrind“ sistema neturi
    rodyti jokių pranešimų apie atminties valdymo problemas.

Veiklos
=======

Veiklos, kurios turi būti vykdomos siekiant užtikrinti sistemos kokybę.

+   Kiekvieno ciklo pabaigoje kiekvienas komandos narys turi sistemos
    testavimui skirti bent po dvi valandas.
+   Kiekvieną artefaktą, be autoriaus turi būti peržiūrėjęs
    dar bent vienas komandos narys.

Post-mortem
===========

Planuodami, tai, kaip užtikrinsime sistemos kokybę, labiausiai
tikėjomės ją užtikrinti vykdydami efektyvias peržiūras. Deja, dėl
labai skirtingų sugebėjimų programuoti C++, gavosi, kad ne visi
galėjo lygiaverčiai jas vykdyti: praktiškai visą sistemos kodą
yra peržiūrėjęs Audrius, kiti – žymiai mažiau. Su dokumentų
peržiūra sekėsi žymiai geriau: kiekvienas vykdantis pakartotinę
peržiūrą, sugebėdavo rasti nebent rašybos klaidų.

Užsibrėžtą tikslą ne daugiau nei 1 defektas 50 kodo eilučių, komandai
pavyko įgyvendinti. Iš viso buvo rasti 124 defektai ir parašytos
15496 kodo eilutės, tai yra vidutiniškai 1 defektas 124 kodo eilutėms.
Deja, čia džiaugtis nėra labai kuo, nes tiksle nurodytas defektų
tankis nėra gautas pasinaudojant kokiais nors ankstesnių darbų
vertinimais, o buvo grynas spėjimas.

Nors sistema visų apsibrėžtų kokybės kriterijų ir netenkina
(kompiliuojant kompiliatorius rodo perspėjimus bei vykdant esmines
užduotis „valgrind“ rodo, kad su atmintimi nėra dirbama visiškai
tvarkingai), mes būtume linkę pačią sistemą laikyti pakankamai
kokybišką, nes visi įspėjimai yra randami bibliotekų, kurias
naudoja mūsų sistema, kode.
