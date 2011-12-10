#ifndef RSYS_LOGIC_RCALCULATOR_HH
#define RSYS_LOGIC_RCALCULATOR_HH

/**********************************************************************************************/
#include <RSys/Logic/RResults.hh>
#include <RSys/Core/RUnit.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Logic/RValidList.hh>
/**********************************************************************************************/
#define MIN_USAGE 1e-4 // m_usage reikšmės, mažesnės už šią, paverčiamos nuliu
/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

class RCalculator: public QObject
{
  Q_OBJECT

  private:
    _T RMeasure::UnitHash                 UnitHash;
    _T RResults::IntervalFun              IntervalFun;
    _T RMeasure::UsageMap                 UsageMap;
    _T RUnit::UsageVector                 UsageVector;

  private:
    _M RData*                         m_data;
    _M RValidList<RMeasurePtrList>    m_measures;
    _M RValidList<RDivisionPtrList>   m_divisions;
    _M RValidList<RSystemPtrList>     m_systems;
    _M RValidList<RSubmissionPtrList> m_submissions;
    _M IntervalFun                    m_intervalFun;
    _M int                            m_numIntervals;
    _M bool                           m_extrapolationEnabled: 1;

  private:
    /**
     * Visoms duotoms priemonėms priskiriamas padalinys ir jo naudojamos
     * sistemos.
     *
     * @param division  padalinys
     * @param measures  priemonės
     */
    _M void             updateMeasures(RDivision* division, RMeasureHash& measures);
    _M void             updateUsages(RSubmissionPtrList* submissions);
    _M void             calculateIntervals();
    _M void             calculateIntervals(UnitHash& units, UsageVector& usage);
    _M double           calculateUsage(RInterval interval, UsageMap& usageMap);
    _M double           predictUsage(RInterval interval, UsageMap& usageMap);
    _M double           daysUsage(QDate day, UsageMap& usageMap);
    _M void             zeroUsages(RUnitPtrList* units);

    /**
     * Nuspėja apkrovą intervale, remiantas gretimų intervalų apkrovomis.
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
    _M double           polynomialExtrapolation(QDate prevDate, double prevUsage,
                                                QDate startDate, double mainUsage,
                                                QDate endDate, double nextUsage,
                                                QDate nextDate, QDate date);

    /**
     * Suformuoja ankstesnio metodo iškvietimą intervalui [it.key(); date).
     *
     * @param it    iteratoriu į nagrinėjamą intervalą
     * @param begin struktūros, turinčios it, pradžios iteratorius
     * @param end   struktūros, turinčios it, pabaigos iteratorius
     * @param date  data, iki kurios (ne imtinai) reikia numatyti apkrovas
     * @return numanoma apkrova [it.key(); date) intervale
     */
    _M double           polynomialExtrapolation(UsageMap :: iterator it,
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
    _M bool             polynomialExtrapolation(int segment1, double segment1Integral,
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
    _M double          integrate(double coefficients[3], int from, int to);

    /**
     * Išsprendžia 3 tiesinių lygčių sistemą.
     *
     * @param matrix   lygties matrica, 3x4; metodas gali keisti jos turinį
     * @param solution sistemos sprendinys
     *
     * @return true, jei egzistuoja vienas sprendinys; false, jei keli arba 0
     */
    _M bool             solveSystemOfLinearEquations(double matrix[3][4],
                                                     double solution[3]);

    /**
     *  Patikrina, ar kvadratinė funkcija duotame intervale yra neneigiama.
     *
     * @param coefficients funkcijos koeficientai
     * @param from         intervalo pradžia
     * @param to           intervalo pabaiga
     */
    _M bool             nonNegativeInInterval(double coefficients[3], int from, int to);

    /**
     * Nustato, kuriam sezonui priklauso duota data.
     *
     * @param date data
     * @return 0, jei žiema, 1 – pavasaris, 2 – vasara, 3 – ruduo
     */
    _S int              seasonOf(QDate date);

  public:
    _M Vacuum           RCalculator(RData* data);
    _M Vacuum           ~RCalculator();
    _M void             update();
    _M void             setIntervalFun(IntervalFun intervalFun, int numIntervals);

    /**
     * Randa mažiausiai apkrautą padalinio ar sistemos intervalą.
     * Apribojama, kuriame dienų intervale ieškoti bei koks dienų kiekis
     * reikalingas ieškomame intervale atsižvelgiant į sezoną.
     *
     * @param unit           sistema ar paramos priemonė, kurios mažiausiai
     *                       apkrauto intervalo ieškome
     * @param interval       intervalas, kuriame ieškoti (imtinai)
     * @param daysBySeasons  rodyklė į 4 skaičius, kurie atitinka reikalavimus
     *                       gauto mažiausios apkrovos intervalo ilgiui, jei
     *                       jis priklauso atitinkamai žiemos, pavasario,
     *                       vasaros, rudens sezonams; skaičiumi 0 nurodoma,
     *                       kad atitinkamo sezono rastame intervale turi nebūti
     * @return tas intervale interval esantis dienų intervalas (imtinai), kurio
     *         apkrova pagal valandas mažiausia, tačiau atitinka nurodytus
     *         daysBySeasons ilgio reikalavimus; jei yra keli tokie intervalai,
     *         grąžina anksčiausią; jei nėra nė vieno, grąžina nulinių datų
     *         intervalą
     */
    _M RInterval        findLowUsageInterval(RUnit* unit, RInterval interval,
                                             int daysBySeasons[4]);

  public slots:
    _M void             setExtrapolationEnabled(bool enabled);
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RCALCULATOR_HH */
