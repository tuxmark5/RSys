#ifndef RSYS_CORE_RMEASURE_HH
#define RSYS_CORE_RMEASURE_HH

/**********************************************************************************************/
#include <RSys/Core/RUnit.hh>
/********************************************* RS *********************************************/
/*                                          RMeasure                                          */
/**********************************************************************************************/

class RMeasure: public RUnit
{
  public:
    _F class RCalculator;
    _F class RData;

  private:
    _M RID              m_groupId;

    _M RSystemMap       m_systemUsage;
    _M RDivisionMap     m_divisionUsage;

  public:
    _M Vacuum           RMeasure(RData* data);
    _M Vacuum           RMeasure(RMeasure& measure, RData* data);
    _V Vacuum           ~RMeasure();
    _M RMeasure*        buddy() const { return static_cast<RMeasure*>(m_buddy); }
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RMEASURE_HH */
