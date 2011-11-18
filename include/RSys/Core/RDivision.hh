#ifndef RSYS_CORE_RDIVISION_HH
#define RSYS_CORE_RDIVISION_HH

/**********************************************************************************************/
#include <RSys/Core/RUnit.hh>
#include <RSys/Logic/RResults.hh>
/********************************************* RS *********************************************/
/*                                         RDivision                                          */
/**********************************************************************************************/

class RDivision: public RUnit
{
  _F class RResults;

  public:
    _M RMeasureMap    m_measureMap;
    _M RMeasureMap    m_measureMap1;  // planned measures
    _M RSystemMap     m_systemMap;

  public:
    _M Vacuum         RDivision(RData* data);
    _M Vacuum         RDivision(RDivision& division, RData* data);
    _V Vacuum         ~RDivision();
    _M void           setMeasure(RMeasure* measure, double value);
    _M void           setMeasure1(RMeasure* measure, double value);
    _M void           setSystem(RSystem* system, double value);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RDIVISION_HH */
