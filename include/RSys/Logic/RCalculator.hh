#ifndef RSYS_LOGIC_RCALCULATOR_HH
#define RSYS_LOGIC_RCALCULATOR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <RSys/Logic/RResults.hh>
#include <RSys/Core/RUnit.hh>
/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

class RCalculator
{
  private:
    _T QHash<RUnit*, double>              RUnitHash;
    _T RResults::IntervalFun              IntervalFun;
    _T RUnit::RUsageMap                   RUsageMap;

  private:
    _M RData*           m_data;
    _M IntervalFun      m_intervalFun;
    _M int              m_numIntervals;

  private:
    _M void             updateMeasures(RDivision* division, RMeasureHash& measures);
    _M void             updateUsages(RSubmissionPtrList* submissions);
    _M void             updateUsageChanges(RUnitHash* units, RSubmission* submission);
    _M void             updateUsages(RUnitPtrList* units);
    _M void             calculateIntervals();
    _M void             calculateIntervals(RUnitPtrList* units);
    _M double           calculateUsage(RInterval interval, RUsageMap& usageMap);

    /**
     * Nuspėja apkrovą intervale, remiantas gretimų intervalų apkrovomis.
     *
     * Randa tokią 2 laipsnio polinominę funkciją f(x), kad jos integralai duotuose
     * intervaluose atitiktų duotas apkrovas, ir grąžina apskaičiuotą reikiamo
     * intervalo integralą.
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
    _M double           polynomialExterpolation(QDate prevDate, double prevUsage,
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
    _M double           polynomialExterpolation(RUsageMap :: iterator it,
                                                RUsageMap :: iterator begin,
                                                RUsageMap :: iterator end,
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

    public:
      _M Vacuum           RCalculator(RData* data);
      _M Vacuum           ~RCalculator();
      _M void             update();
      _M void             setIntervalFun(IntervalFun intervalFun, int numIntervals);
  };

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RCALCULATOR_HH */
