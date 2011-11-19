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
    _T QMap<RUnit*, double>               RUnitMap;
    _T RResults::IntervalFun              IntervalFun;
    _T RUnit::RUsageMap                   RUsageMap;

  private:
    _M RData*           m_data;
    _M IntervalFun      m_intervalFun;
    _M int              m_numIntervals;

  private:
    _M void             updateMeasures(RDivision* division, RMeasureMap& measures);
    _M void             updateUsages(RSubmissionList* submissions);
    _M void             updateUsageChanges(RUnitMap* units, RSubmission* submission);
    _M void             updateUsages(RUnitList* units);
    _M void             calculateIntervals();
    _M void             calculateIntervals(RUnitList* units);
    _M double           calculateUsage(RInterval interval, RUsageMap& usageMap);

  public:
    _M Vacuum           RCalculator(RData* data);
    _M Vacuum           ~RCalculator();
    _M void             update();
    _M void             setIntervalFun(IntervalFun intervalFun, int numIntervals);
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RCALCULATOR_HH */
