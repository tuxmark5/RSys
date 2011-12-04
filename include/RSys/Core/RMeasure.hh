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

    _M RDivisionHash    m_divisionUsage;
    _M RSystemHash      m_systemUsage;

  public:
    _M Vacuum           RMeasure(RData* data);
    _M Vacuum           RMeasure(RMeasure& measure, RData* data);
    _V Vacuum           ~RMeasure();
    _M RMeasure*        buddy() const { return static_cast<RMeasure*>(m_buddy); }
    _M void             remove();

  public:
    _G(void,            measureRemoval, RMeasure* measure);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RMEASURE_HH */
