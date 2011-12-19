Komandos išsikelti tikslai
==========================

+   Suplanuotas programos dydis nuo realaus skiriasi ne daugiau 20 %.
+   Defektų tankis ne didesnis nei 1 defektas 50 kodo eilučių.
+   Suplanuoti ciklų pabaigas bent 2 savaičių tikslumu.
+   Programavimo greitis ne mažesnis nei 50 eilučių per valandą.

Pagal šiuos tikslus komanda nusprendė sistemos kūrimo metu rinkti tokius
duomenis:

+   defektai, kurie „iškeliavo“ į versijų kontrolės sistemą;
+   laikas 5 minučių tikslumu.

Sprendimas fiksuoti tik tuos defektus, kurie pateko į versijų kontrolės
sistemą, priimtas dėl vienos esminės priežasties - komandos naudota IDE
QtCreator sugeba realiu laiku parodyti vietas, kuriose yra tikėtinos 
kompiliavimo klaidos;

Post-mortem
-----------

Plačiau apie:
+   planavimo tikslumą žr. *size_measurement.pdf*
+   defektų tankį žr. *quality.pdf*
+   ciklų planavimą žr. *strategy.pdf*


Rolių išsikelti tikslai
=======================

+   Komandos lyderio tikslai:
    +   Kiekvieną savaitę informuoti instruktorių apie komandos progresą
    +   Išspręsti visas su komanda ir darbų pasidalijimu iškilusias problemas
+   Vidinės kokybės vadovo tikslai
    +   Priversti parašyti komandą modulių testus esminiams moduliams,
        kurių testavimas yra galimas
+   Išorinės kokybės vadovo tikslai
    +   Nuodugniai peržiūrėti visus kuriamus artefaktus
+   Planavimo vadovo tikslai
    +   Kiekvieną savaitę planuoti ateinančios savaitės darbus
+   Reikalavimų vadovo tikslai
    +   Užfiksuoti visus iš užsakovo gautus atsakymus į klausimus dėl funkcionalumo
        kaip reikalavimus


Post-mortem
-----------

+   Komandos lyderiui pavyko įvykdyti visus užsibrėžtus tikslus (nors ir 
    vienas susitikimas neįvyko, tačiau projektas dažnai būdavo aptarinėjamas
    ir ne susitikimų metu).
+   Vidinės kokybės vadovui taip pat sekėsi sėkmingai ištestuoti esminius
    testuojamus modulius: duomenų importui ir skanavimui buvo parašyti modulių
    testai, kurie atlikus esminius sistemos pakeitimus padėdavo greitai
    ir efektyviai surasti naujai iškilusias problemas.
+   Išorinės kokybės vadovas nuolatos peržiūrinėdavo į repozitoriją keliaujančių
    artefaktų pakeitimus ir taip dažnai realiu laiku rasdavo įvairius
    defektus susijusius su produkto kokybe.
+   Nors ir planuoti ne visada sekėsi pakankamai tiksliai, planavimo vadovas
    kiekvieną savaitę iškart po komandos susitikimų stengdavosi užregistruoti
    aptartus planus komandos susitikimuose.
+   Reikalavimų vadovas taip pat pakankamai efektyviai vykdė savo rolę:
    gauti atsakymai iš užsakovo būdavo visą laiką išsiunčiami visiems komandos
    nariams ir tai leisdavo reikalavimų vadovui be pankankamai didelio
    delsimo užregistruoti naujus reikalavimus, tačiau taip būdavo ne visada,
    nes dažnai norint pilnai suvokti gauto atsakymo prasmę tekdavo kartu
    bent daliai grupės susirinkti ir aptarti gautą atsakymą. Todėl reikalavimų
    registravimas kai kuriais atvejais šiek tiek vėluodavo.
