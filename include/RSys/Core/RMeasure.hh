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
    _T QMap<QDate, double>         UsageMap;
    _T QHash<RUnit*, double>       UnitHash;

  private:
    _M RID              m_groupId;
    _M UnitHash         m_unitUsage;
    _M UsageMap         m_usageMap;       // paraiškų per dieną pradedant nuo datos

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
