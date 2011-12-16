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

Komandos narių naudotos PSP praktikos
=====================================

+   Bendras kodavimo standartas.

Pastabos apie tai, kaip buvo vykdytos praktikos
===============================================

Komandos išsikelti tikslai
--------------------------

+   Suplanuotas programos dydis nuo realaus skiriasi ne daugiau 20 %.
+   Defektų tankis ne didesnis nei 1 defektas 100 kodo eilučių.
+   Suplanuoti 2 ciklo pabaigą 2 savaičių tikslumu.
+   Programavimo greitis ne mažesnis nei 50 eilučių per valandą.

Pagal šiuos tikslus komanda nusprendė sistemos kūrimo metu rinkti tokius
duomenis:

+   defektai, kurie „iškeliavo“ į versijų kontrolės sistemą;
+   laikas minučių tikslumu.

Sprendimas fiksuoti tik tuos defektus, kurie pateko į versijų kontrolės
sistemą, priimtas dėl dviejų priežasčių:

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
    padaryti.

Buvo nuspręsta dirbti trimis ciklais:

1.  *bazinis ciklas* (planuota: 2011-11-01, baigtas: 2011-11-17):

    +   realizuota didžioji dalis naudotojo sąsajos;
    +   realizuotas apkrovų skaičiavimas;
    +   „įkompiliuotas“ duomenų importavimas (veikia tik su užsakovo
        atsiųstu duomenų failu, skaito duomenis iš pozicijų, kurios
        yra nurodytos tiesiogiai kode);

2.  *pagrindinis ciklas* (planuota: 2011-12-01, baigtas: 2011-12-08):

    +   realizuota sąsaja su duomenų baze;
    +   korektiškas duomenų importavimas;
    +   realizuotas visas pagrindinis ir papildomas funkcionalumas;

3.  *baigiamasis ciklas* (baigtas: 2011-12-20):

    +   užtikrinti visi reikalavimai;
    +   paruošta dokumentacija;
    +   pilnai realizuota naudotojo sąsaja.

Pagrindinė priežastis kodėl atsirado vėlavimas – Žmogaus-kompiuterio
sąveikos atsiskaitymams buvo norima naudoti ne maketus, o jau
realią sistemą, dėl ko kai kurias funkcijas teko realizuoti
anksčiau, nei buvo planuota, kas lėmė vėlesnes ciklų pabaigas.

Koncepcinis sistemos projektavimas buvo daromas ne rašant atskirą
dokumentą, o iš karto kuriant reikiamus C++ antraščių failus.
Buvo nuspręsta, kad sistemą sudarys tokie moduliai:

+   *Core* – dalykinės srities duomenų struktūros;
+   *Import* – duomenų importavimas iš ``*.xls`` failo;
+   *Interface* – naudotojo sąsaja;
+   *Logic* – duomenų analizės funkcionalumas;
+   *Parse* – importuotų duomenų validavimas ir konvertavimas į
    vidines duomenų struktūras;
+   *Store* – sąveika su duomenų bazėmis;
+   *Tests* – modulių testai;
+   *Util* – visai tai, kas netinka kitur.

Kadangi komanda neturėjo istorinės duomenų bazės, kurią galima
būtų panaudoti sistemos dydžio prognozavimui PROBE metodu, jį buvo
bandoma atspėti prognozuojant kiek ir kokio dydžio klasių reikės.
Klasės pagal spėjamą dydį buvo suskirstytos į tokias grupes:

+   maža – 20 eilučių antraštės failas ir 100 eilučių
    realizacijos failas;
+   vidutinė – 30 eilučių antraštės failas ir 200 eilučių
    realizacijos failas;
+   didelė – 40 eilučių antraštės failas ir 500 eilučių
    realizacijos failas;
+   labai didelė – 60 eilučių antraštės failas ir 800 eilučių
    realizacijos failas.

Čia, kodo eilutėmis yra laikomos visos, nepriklausomai nuo jų turinio
(tuščios, su komentarais irgi įskaičiuojamos). Planuojant buvo nuspręsta,
kad sistemoje turėtų būti tokios klasės:

    1.  mažos:

        +   5 duomenų klasės (paramos priemonė, paraiška, padalinys, IS,
            bazinė);
        +   abstraktus duomenų modelis;

    2.  vidutinės:

        +   priemonių sąsaja;
        +   priemonių administravimo sąsaja;
        +   sistemų sąsaja;
        +   sistemų administravimo sąsaja;
        +   istorinių duomenų sąsaja;
        +   prisijungimo sąsaja;
        +   intervalų paieškos sąsaja;
        +   importavimo sąsaja;
        +   įrankių juostos sąsaja;
        +   BasicExcel testai;
        +   importavimo testai;
        +   diagramos komponentas;

    3.  didelės:

        +   sąsaja su DB;
        +   rezultatų modelis;
        +   1 su n modelis;
        +   n su n modelis;
        +   planuojamų kiekių sąsaja;
        +   rezultatų sąsaja;

    4.  labai didelės:

        +   logika;
        +   pagrindinis langas;
        +   duomenų importavimas.

Iš viso – 9300 eilučių. Taip pat buvo daroma prielaida, kad realizuojant
gali prireikti dar 20% eilučių tokiems atvejams, kaip komunikavimo tarp
klasių užtikrinimas, papildomos skaičiavimams reikalingos duomenų
struktūros ir panašiai. Taigi galutinė sistemos versija turėtų turėti
apie 11160 eilučių. Suskaičiavus gavosi, kad sistema turi 14744 kodo
eilutes. Paklaida atsirado dėl to, kad vėliau buvo nuspręsta į sistemą
integruoti pagalbos sistemą bei prireikė papildomų duomenų modelių
sinchronizacijai tarp duomenų struktūrų ir naudotojo sąsajos. Taip
pat atsirado dvi nenumatytos sąsajos: naudotojų administravimo ir
rėžimo.

Reikalavimų specifikacijos ruošimas
===================================

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

Projektavimas
=============

Dėl naudoto projektavimo būdo (C++ antraščių failai) koncepcinis ir
detalusis projektavimas susiliejo į vieną.

TODO
====

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
