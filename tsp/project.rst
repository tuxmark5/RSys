Sistemos koncepcinis projektas
==============================

Per grupinį susitikimą, nuspręsta sistemą padalinti į tokius komponentus:

+   **Core** – dalykinės srities duomenų struktūros;
+   **Import** – duomenų importavimas iš ``*.xls`` failo;
+   **Interface** – naudotojo sąsaja;
+   **Logic** – duomenų analizės funkcionalumas;
+   **Parse** – importuotų duomenų validavimas ir konvertavimas į
    vidines duomenų struktūras;
+   **Store** – sąveika su duomenų bazėmis;
+   **Tests** – modulių testai;
+   **Util** – visai tai, kas netinka kitur.

Kadangi sistema bus kuriama naudojantis C++ programavimo kalba, tai
nuspręsta tolimesnį (eskizinį) projektavimą perkeltį į C++ antračių
failus. T.y. projektuoti kodu.

Post-mortem
-----------

Toks projektavimo būdas itin gerai pasiteisino: reikalingi interfeisai būdavo
apibrėžiami komandos susitikimų metu pilnai išsiaiškinant jų esmę. Kadangi
projekto eigoje teko keisti pirma apibrėžtus interfeisus, tai leido
sutaupyti daug laiko (nes jei būtų interfeisai aprašyti atskirame dokumente,
tai be pačių interfeisų dar būtų tekę keisti pačius dokumentus).

Sistemos komponentus pavyko sukurti taip, kad šie būtų kiek įmanoma
mažiau susiję vieni su kitais.

Gautos komponentų priklausomybės:

+   **Core** komponentas yra visiškai nepriklausomas.
+   **Import** komponentas yra visiškai nepriklausomas.
+   **Parse** komponentas priklauso tik nuo **Core** ir **Import**.
+   **Logic** komponentas priklauso tik nuo **Core**
+   **Store** komponentas priklauso tik nuo **Core**
+   **Interface** komponentas priklauso nuo visų kitų komponentų, nes
    jo vaidmuo yra apjungti sukurtus komponentus į naudotojui prieinamą
    grafinę sąsają.

Stabiliausias apibrėžtas interfeisas - **Import**, kurio nereikėjo nė karto keisti ir
kuris buvo sukurtas dar spalio 27 d. (git kodo revizija 
*799572c59936b80d8f57c9f05c0da963d6e82fcb*).
