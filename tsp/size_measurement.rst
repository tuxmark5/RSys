==========================
Projekto dydžio vertinimas
==========================

Kadangi komanda neturi istorinės duomenų bazės, kurią galima
būtų panaudoti sistemos dydžio prognozavimui PROBE metodu, jį yra
bandoma atspėti prognozuojant kiek ir kokio dydžio klasių reikės.
Klasės pagal spėjamą dydį yra suskirstytos į tokias grupes:

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

    1.  *mažos*:

        +   5 duomenų klasės (paramos priemonė, paraiška, padalinys, IS,
            bazinė);
        +   abstraktus duomenų modelis;

    2.  *vidutinės*:

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

    3.  *didelės*:

        +   sąsaja su DB;
        +   rezultatų modelis;
        +   1 su n modelis;
        +   n su n modelis;
        +   planuojamų kiekių sąsaja;
        +   rezultatų sąsaja;

    4.  *labai didelės*:

        +   logika;
        +   pagrindinis langas;
        +   duomenų importavimas.

Iš viso – 9300 eilučių. Taip pat vertinant daroma prielaida, kad realizuojant
gali prireikti dar 20% eilučių tokiems atvejams, kaip komunikavimo tarp
klasių užtikrinimas, papildomos skaičiavimams reikalingos duomenų
struktūros ir panašiai. Vadinasi, galutinė sistemos versija turėtų turėti
apie 11160 eilučių. 

Post-mortem
-----------

Parašius sistemą ir suskaičiavus jos kodo eilučių skaičių,
gavosi, kad sistema turi 15496 kodo eilutes. Nuo pradinio vertinimo nukrypta
per 4336 eilutes arba per 38.85%. Vadinasi, kaip bebūtų gaila,
tikslo, jog įvertinti programos dydį 20% tikslumu įgyvendinti nepavyko.

Tokią didelę paklaidą lėmė kelios priežastys:

+   Nebuvo numatyti šie komponentai:

    +   Pagalbos sistema (~500 eilučių)
    +   Režimo sąsaja (kode dar vadinamas palete, ~500 eilučių)
    +   Naudotojų administravimas (~600 eilučių)
    +   Naudotojų administravimo sąsajos (~500 eilučių)
    +   Papildomi komponentai, palengvinantys sinchronizaciją tarp 
        naudotojo sąsajos ir duomenų modelių (~2000 eilučių)

+   Netinkamai įvertinti šių klasių dydžiai:

    +   įrankių juostų klasės viršijo 600 eilučių 
        (~400 eilučių skirtumas nuo prognozės)

Nors nuokrypis pakankamai didelis, tačiau komanda išlieka patenkinta tokiu rezultatu,
nes neturint jokių istorinių duomenų pavyko pakankamai tiksliai ne tik suplanuoti
būsimas klases, bet ir įvertinti jų dydį.
