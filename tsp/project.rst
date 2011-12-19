Sistemos koncepcinis projektas
==============================

Per grupinį susitikimą, nuspręsta sistemą padalinti į tokius komponentus:
+   *Core* – dalykinės srities duomenų struktūros;
+   *Import* – duomenų importavimas iš ``*.xls`` failo;
+   *Interface* – naudotojo sąsaja;
+   *Logic* – duomenų analizės funkcionalumas;
+   *Parse* – importuotų duomenų validavimas ir konvertavimas į
    vidines duomenų struktūras;
+   *Store* – sąveika su duomenų bazėmis;
+   *Tests* – modulių testai;
+   *Util* – visai tai, kas netinka kitur.

Kadangi sistemos 


Post-mortem
-----------


Dėl naudoto projektavimo būdo (C++ antraščių failai) koncepcinis ir
detalusis projektavimas susiliejo į vieną.


Koncepcinis sistemos projektavimas buvo daromas ne rašant atskirą
dokumentą, o iš karto kuriant reikiamus C++ antraščių failus.
Buvo nuspręsta, kad sistemą sudarys tokie moduliai:
