#ifndef RSYS_CORE_RDIVISION_HH
#define RSYS_CORE_RDIVISION_HH

/**********************************************************************************************/
#include <RSys/Core/RUnit.hh>
#include <RSys/Util/RSignal.hh>
/********************************************* RS *********************************************/
/*                                         RDivision                                          */
/**********************************************************************************************/

class RDivision: public RUnit
{
  public:
    _F class          RCalculator;
    _F class          RData;
    _F class          TestRValidator;

  private:
    _M RMeasureHash    m_measureHash;
    _M RMeasureHash    m_measureHash1;  // planned measures
    _M RSystemHash     m_systemHash;

  public:
    _M Vacuum         RDivision(RData* data);
    _M Vacuum         RDivision(RDivision& division, RData* data);
    _V Vacuum         ~RDivision();
    _M double         measure(RMeasure* measure) const { return m_measureHash.value(measure, 0); }
    _M double         measure1(RMeasure* measure) const { return m_measureHash1.value(measure, 0); }
    _M bool           setMeasure(RMeasure* measure, double value);
    _M void           setMeasure1(RMeasure* measure, double value);
    _M void           setSystem(RSystem* system, double value);
    _M double         system(RSystem* system) const { return m_systemHash.value(system, 0); }

  public:
    _G(void,          onMeasureSet, RDivision* division, RMeasure* measure, double value);
    _G(void,          onMeasureUnset, RDivision* division, RMeasure* measure);
    _G(void,          onSystemSet, RDivision* division, RSystem* system, double value);
    _G(void,          onSystemUnset, RDivision* division, RSystem* system);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RDIVISION_HH */
