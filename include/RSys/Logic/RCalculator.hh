#ifndef RSYS_LOGIC_RCALCULATOR_HH
#define RSYS_LOGIC_RCALCULATOR_HH

/**********************************************************************************************/
#include <RSys/Core/RUnit.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Logic/RValidList.hh>
/**********************************************************************************************/
#define MIN_USAGE 1e-4 // m_usage reikšmės, mažesnės už šią, paverčiamos nuliu
#define MAX_PREDICTION_LENGTH 10 // kiek daugiausiai metų žvelgti į praeitį prognozuojant
/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

class RCalculator: public QObject
{
  Q_OBJECT

  private:
    _T RMeasure::UnitHash             UnitHash;
    _T RMeasure::UsageMap             UsageMap;
    _T RUnit::UsageVector             UsageVector;
    _T RValidList<RMeasurePtrList>    ValidMeasurePtrList;
    _T RValidList<RSubmissionPtrList> ValidSubmissionPtrList;
    _T RValidList<RDivisionPtrList>   ValidDivisionPtrList;
    _T RValidList<RSystemPtrList>     ValidSystemPtrList;
    _T RValidList<RUnitPtrList>       ValidUnitPtrList;
    _T QMap<QDate, RSubmissionPtr>    SubmissionMap;
    _T unsigned long long             Fractions;

    /**
     * Informacija apie priemonės apkrovų įrašus jų teisingumo patikrinimui.
     */
    struct MeasureInfo
    {
      SubmissionMap           m_usefulSubmissions; // smulkiausi korektiški įrašai
                                                   // pagal intervalo pradžią
      QMap<QDate, QDate>      m_invalidIntervals;  // kur yra susikertančių intervalų
      QVector<RSubmissionPtr> m_splitSubmissions;  // kurie buvo patikslinti
    };

  private:
    _M RData*                         m_data;
    _M bool                           m_usePlanedData;
    _M ValidMeasurePtrList            m_validMeasures;
    _M ValidSubmissionPtrList         m_validSubmissions;
    _M ValidDivisionPtrList           m_validDivisions;
    _M ValidSystemPtrList             m_validSystems;
    _M RIntervalFun                   m_intervalFun[2];
    _M int                            m_numIntervals[2];
    _M bool                           m_interpolationEnabled: 1;

  private:
    /**
     * Visoms duotoms priemonėms priskiriamas padalinys ir jo naudojamos
     * sistemos.
     *
     * @param division  padalinys
     * @param measures  priemonės
     */
    _S void             updateMeasures(RDivisionPtr& division, RMeasureHash& measures);
    _S void             updateUsageMap(UsageMap& usageMap, SubmissionMap& submissions);
    _S void             checkSplitSubmissions(MeasureInfo& info);

    /**
     * Nustato, jog intervalą kertantys įrašai yra neteisingi, juos išmeta iš
     * sąrašo bei, jei reikia, praplečia duotąjį intervalą pagal išmestus.
     *
     * @param from        intervalo pradžia; jei buvo išmestas intervalas,
     *                    kurio pradžios data mažesnė už from, ji priskiriama
     *                    from
     * @param to          intervalo pabaiga, neimtinai; jei buvo išmestas
     *                    intervalas, kurio pabaigos data nemažesnė už to, ji,
     *                    pridėjus vieną dieną, priskiriama to
     * @param submissions nesikertančių intervalų įrašai, tarp kurių ieškoma
     *                    priklausančių/kertančių/apimančių [from; to)
     * @return true, jei buvo išmestas nors vienas intervalas; false, jei ne
     */
    _S bool             invalidateInRange(QDate& from, QDate& to,
                                          SubmissionMap& submissions);
    _M void             calculateIntervals(int whichUsage);
    _M void             calculateIntervals(UnitHash& units, UsageVector& usage,
                                           int whichUsage);
    _M double           calculateUsage(RInterval interval, UsageMap& usageMap);
    _M double           predictUsage(RInterval interval, UsageMap& usageMap);
    _M void             zeroUsages(RUnitPtrList* units, int whichUsage);
    _S void             findLowUsageIntervals(ValidUnitPtrList* units,
                                              QVector<Fractions>& fractions,
                                              Fractions fractionsNeeded, QDate& date);
    _S bool             submissionLengthComparator(const RSubmissionPtr& a,
                                                   const RSubmissionPtr& b)
      { return a->date0().daysTo(a->date1()) < b->date0().daysTo(b->date1()); }

    /**
     * Nuspėja apkrovą intervale, remiantis gretimų intervalų apkrovomis.
     *
     * Randa tokią 2 laipsnio polinominę funkciją f(x), kad jos integralai duotuose
     * intervaluose atitiktų duotas apkrovas, ir grąžina apskaičiuotą reikiamo
     * intervalo integralą.
     * Jei [startDate; endDate) intervale f(x) įgyja neigiamą reikšmę, jame
     * apkrovas paskirstome tolygiai. Taip pat tolygiai apkrovos skirstomos ir
     * jei f(x) rasti nepavyksta.
     *
     * @param prevDate  intervalo, esančio iškart prieš nagrinėjamą, pradžia
     * @param prevUsage intervalo iškart prieš nagrinėjamą vidutinė dienos apkrova
     * @param startDate intervalo, kurio dalies apkrovą norime nuspėti, pradžia
     * @param mainUsage nagrinėjamo intervalo vidutinis dienos apkrovimas
     * @param endDate   intervalo, esančio iškart po nagrinėjamo, pradžia
     * @param nextUsage intervalo iškart po nagrinėjamo vidutinė dienos apkrova
     * @param date      diena iš [startDate; endDate), iki kurios (ne imtinai)
     *                  reikia numatyti suminę apkrovą
     * @return numanoma apkrova [startDate; date) intervale
     */
    _S double           polynomialInterpolation(QDate prevDate, double prevUsage,
                                                QDate startDate, double mainUsage,
                                                QDate endDate, double nextUsage,
                                                QDate nextDate, QDate date);

    /**
     * Suformuoja ankstesnio metodo iškvietimą intervalui [it.key(); date).
     *
     * @param it    iteratorius į nagrinėjamą intervalą
     * @param begin struktūros, turinčios it, pradžios iteratorius
     * @param end   struktūros, turinčios it, pabaigos iteratorius
     * @param date  data, iki kurios (ne imtinai) reikia numatyti apkrovas
     * @return numanoma apkrova [it.key(); date) intervale
     */
    _S double           polynomialInterpolation(UsageMap :: iterator it,
                                                UsageMap :: iterator begin,
                                                UsageMap :: iterator end,
                                                QDate date);
    /**
     * Randa 2 laipsnio polinominę funkciją pagal duotus nuosekliai einančių
     * atkarpų integralus.
     *
     * Pastaba: tikriausiai būtų patogu pasirašyti bendrą atvejį, atkarpas
     * paduodant kaip QVector<QPair<double, double> >, o rezultatą sudedant į
     * QVector<double> – kai iškils toks poreikis, reikės taip ir padaryti.
     *
     * @param segment1         pirmos atkarpos pabaigos taškas; atkarpa [0; segment1)
     * @param segment1Integral pirmos atkarpos integralas
     * @param segment2         antros atkarpos pabaigos taškas; atkarpa [segment1; segment2)
     * @param segment2Integral antros atkarpos integralas
     * @param segment3         trečios atkarpos pabaigos taškas; atkarpa [segment2; segment3)
     * @param segment3Integral trečios atkarpos integralas
     * @param coefficients     rodyklė į 3 elementų masyvą gautos funkcijos koeficientams
     * @return true, jei koeficientus rasti pavyksta; false priešingu atveju
     */
    _S bool             getPolynom(int segment1, double segment1Integral,
                                   int segment2, double segment2Integral,
                                   int segment3, double segment3Integral,
                                   double coefficients[3]);

    /**
     * Apskaičiuoja duotos 2 laipsnio polinominės funkcijos apibrėžtinį integralą.
     *
     * @param coefficients  rodyklė į funkcijos koeficientus
     * @param from          intervalo, kuriame integruojame, pradžia
     * @param to            intervalo, kuriame integruojame, pabaiga
     * @return apskaičiuotas apibrėžtinis integralas
     */
    _S double          integrate(double coefficients[3], int from, int to);

    /**
     * Išsprendžia 3 tiesinių lygčių sistemą.
     *
     * @param matrix   lygties matrica, 3x4; metodas gali keisti jos turinį
     * @param solution sistemos sprendinys
     *
     * @return true, jei egzistuoja vienas sprendinys; false, jei keli arba 0
     */
    _S bool             solveSystemOfLinearEquations(double matrix[3][4],
                                                     double solution[3]);

    /**
     *  Patikrina, ar kvadratinė funkcija duotame intervale yra neneigiama.
     *
     * @param coefficients funkcijos koeficientai
     * @param from         intervalo pradžia
     * @param to           intervalo pabaiga
     */
    _S bool             nonNegativeInInterval(double coefficients[3], int from, int to);

    /**
     * Nustato, kuriam sezonui priklauso duota data.
     *
     * @param date data
     * @return 0, jei žiema, 1 – pavasaris, 2 – vasara, 3 – ruduo
     */
    _S int              seasonOf(QDate date);

    /**
     * Patikrina, ar duoto įrašo intervalas kerta (priklauso) kurį nors (kuriam
     * nors) iš blogų intervalų. Jei kerta, modifikuoja blogus intervalus taip,
     * kad įtrauktų ir jį. Tam nutikus, pažymi duomenis kaip neteisingus, bei
     * ieško su juo besikertančių intervalų tarp naudojamų, su kuriais padaro
     * tą patį.
     *
     * @param submission tikrinamas įrašas
     * @param info       informacija apie paramos priemonės duomenis
     * @return true, jei intervalai kertasi; false priešingu atveju
     */
    _S bool             intersect(RSubmissionPtr submission, MeasureInfo info);

    /**
     * Nuspėja tiesinės funkcijos reikšmę taške x, kai žinomos jos reikšmės
     * su atsitiktine paklaida taškuose 0, 1, ..., m.
     *
     * @param y   funkcijos reikšmės taškuose 0, 1, ..., m
     * @param x   taškas, kurio reikšmės norime
     * @return    tikėtina funkcijos reikšmė taške x
     */
    _S double linearRegression(const QVector<double>& y, double x);

  public:
    _M Vacuum           RCalculator(RData* data, bool usePlanedData);
    _M Vacuum           ~RCalculator();

    /**
     * Atnaujina visus skaičiavimams naudojamus duomenis ir perskaičiuoja
     * rezultatus.
     * Reikia iškviesti pasikeitus/atsiradus naujiems apdorotų paraiškų
     * kiekiams, sąryšiams tarp priemonių ir padalinių, padalinių ir sistemų.
     */
    _M void             update();

    /**
     * Nustato intervalų generatorių, kuriam reikia suformuluoti rezultatus
     * ir juos atnaujina.
     * Reikia iškviesti pasikeitus nagrinėjamam intervalui. Jei pasikeitė
     * nagrinėjamų priemonių pasirinkimai (RMeasure::isVisible() reikšmės)
     * taip pat pakanka iškviesti šį metodą (tiktų ir update(), bet šis
     * žymiai efektyvesnis.
     * Gauti rezultatai pasiekiami kviečiant RUnit::usageAt(x) metodą, kur
     * x – intervalo numeris iš intervalo [0; numIntervals - 1].
     *
     * @param intervalFun  funkcija, generuojanti [pradžia; pabaiga) intervalus,
     *                     kuriems skaičiuojamos apkrovos; intervalai gaunami
     *                     iškvietus intervalFun(0), intervalFun(1), ...,
     *                     intervalFun(numIntervals - 1)
     * @param numIntervals keliems intervalams apskaičiuoti apkrovą, naudojant
     *                     intervalFun
     */
    _M void             setIntervalFun(RIntervalFun intervalFun, int numIntervals);

    /**
     * Randa mažiausios apkrovos padalinių ir sistemų intervalą.
     * Apribojama, kuriame dienų intervale ieškoti bei koks dienų kiekis
     * reikalingas ieškomame intervale atsižvelgiant į sezoną.
     * Po šio metodo iškvietimo kiekvienam padaliniui/sistemai rasti intervalai
     * pasiekiami RUnit::lowestUsage(). Šis metodas grąžins tą intervale
     * interval esantį dienų intervalą (imtinai), kuriame apkrova pagal valandas
     * mažiausia, tačiau atitinka nurodytus daysBySeasons ilgio reikalavimus.
     * Jei yra keli tokie intervalai, grąžina anksčiausią; jei nėra nė vieno,
     * grąžina nulinių datų intervalą.
     *
     * @param interval       intervalas, kuriame ieškoti (imtinai)
     * @param daysBySeasons  rodyklė į 4 skaičius, kurie atitinka reikalavimus
     *                       gauto mažiausios apkrovos intervalo ilgiui, jei
     *                       jis priklauso atitinkamai žiemos, pavasario,
     *                       vasaros, rudens sezonams; skaičiumi 0 nurodoma,
     *                       kad atitinkamo sezono rastame intervale turi nebūti
     */
      _M void           findLowUsageIntervals(RInterval interval,
                                              int daysBySeasons[4]);

  public slots:
    _M void             setInterpolationEnabled(bool enabled);
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RCALCULATOR_HH */
