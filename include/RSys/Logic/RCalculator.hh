#ifndef RSYS_LOGIC_RCALCULATOR_HH
#define RSYS_LOGIC_RCALCULATOR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

class RCalculator
{
  private:
    _T QMap<RUnit*, double>               RUnitMap;

  private:
    _M RData*           m_data;

  private:
    _M void             updateMeasures(RDivision* division, RMeasureMap& measures);
    _M void             updateUsages(RSubmissionList* submissions);
    _M void             updateUsageChanges(RUnitMap* units, RSubmission* submission);
    _M void             updateUsages(RUnitList* units);

  public:
    _M Vacuum           RCalculator(RData* data);
    _M Vacuum           ~RCalculator();
    _M void             update();
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RCALCULATOR_HH */
