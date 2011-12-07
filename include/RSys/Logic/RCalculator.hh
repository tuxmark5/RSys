#ifndef RSYS_LOGIC_RCALCULATOR_HH
#define RSYS_LOGIC_RCALCULATOR_HH

/**********************************************************************************************/
#include <RSys/Logic/RResults.hh>
#include <RSys/Core/RUnit.hh>
/**********************************************************************************************/
#define MIN_USAGE 1e-4 // m_usage reikšmės, mažesnės už šią, paverčiamos nuliu
/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

class RCalculator: public QObject
{
  Q_OBJECT

  private:
    _T QHash<RUnit*, double>              UnitHash;
    _T RResults::IntervalFun              IntervalFun;
    _T RUnit::UsageMap                    UsageMap;
    _T RUnit::UsageVector                 UsageVector;

  private:
    _M RData*           m_data;
    _M IntervalFun      m_intervalFun;
    _M int              m_numIntervals;
    _M bool             m_extrapolationEnabled: 1;

  private:
    /**
     * Visoms duotoms priemonėms priskiriamas padalinys ir jo naudojamos
     * sistemos.
     *
     * @param division  padalinys
     * @param measures  priemonės
     */
    _M void             updateMeasures(RDivision* division, RMeasureHash& measures);
    _M void             updateUsageChanges(RSubmissionPtrList* submissions);
    // TODO: Galbūt prireiks mažiausiai apkrauto intervalo paieškai:
    // _M void             updateUsageChanges(UnitHash* units, RSubmission* submission);
    _M void             updateUsages(RUnitPtrList* units);
    _M void             updateUsages(UsageMap& usageMap, UsageMap& usageChangeMap);
    _M void             calculateIntervals();
    _M void             calculateIntervals(UnitHash* units, UsageVector& usage);
    _M double           calculateUsage(RInterval interval, UsageMap& usageMap);
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

  public:
    _M Vacuum           RCalculator(RData* data);
    _M Vacuum           ~RCalculator();
    _M void             update();
    _M void             setIntervalFun(IntervalFun intervalFun, int numIntervals);

  public slots:
    _M void             setExtrapolationEnabled(bool enabled);
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RCALCULATOR_HH */
