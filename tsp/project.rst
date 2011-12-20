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
nuspręsta tolimesnį (eskizinį) projektavimą perkelti į C++ antraščių
failus. T.y. projektuoti kodu.

Post-mortem
-----------

Toks projektavimo būdas itin gerai pasiteisino: reikalingos sąsajos būdavo
apibrėžiamos komandos susitikimų metu pilnai išsiaiškinant jų esmę. Kadangi
projekto eigoje teko keisti pirma apibrėžtas sąsajas, tai leido
sutaupyti daug laiko (nes jei būtų sąsajos aprašytos atskirame dokumente,
tai be pačių sąsajų dar būtų tekę keisti pačius dokumentus).

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

Stabiliausia apibrėžta sąsaja – **Import**, kurios nereikėjo nė
karto keisti ir kuri buvo sukurta dar spalio 27 d. (git kodo revizija
``799572c59936b80d8f57c9f05c0da963d6e82fcb``).
