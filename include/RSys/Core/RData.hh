#ifndef RSYS_CORE_RDATA_HH
#define RSYS_CORE_RDATA_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                           RData                                            */
/**********************************************************************************************/

// TODO: iterators /
class RData
{
  private:
   // _M RDivisionList  m_divisions;
    _M RMeasureList   m_measures;
   // _M RSystemList    m_systems;

  public:
    _V RDivision*     division(RID id)  const = 0;
    _V RMeasure*      measure(RID id)   const = 0;
    _V int            numDivisions()    const = 0;
    _V int            numMeasures()     const = 0;
    _V int            numSystems()      const = 0;
    _V RSystem*       system(RID id)    const = 0;
    _V void           update(RElement* element) = 0;
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RDATA_HH */
