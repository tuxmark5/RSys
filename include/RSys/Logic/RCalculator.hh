#ifndef RSYS_LOGIC_RCALCULATOR_HH
#define RSYS_LOGIC_RCALCULATOR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

class RCalculator
{
  public:
    _M Vacuum           RCalculator();
    _M Vacuum           ~RCalculator();
    _M QVector<double>  calcUsages(RDivision* division, QDate from, QDate to);
    _M QVector<double>  calcUsages(RSystem* system, QDate from, QDate to);
};

/**********************************************************************************************/

#endif /* RSYS_LOGIC_RCALCULATOR_HH */
