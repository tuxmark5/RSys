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
yra peržiūrėjęs Audrius, kiti – žymiai mažiau.
