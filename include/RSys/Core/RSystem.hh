#ifndef RSYS_CORE_RSYSTEM_HH
#define RSYS_CORE_RSYSTEM_HH

/**********************************************************************************************/
#include <RSys/Core/RUnit.hh>
/********************************************* RS *********************************************/
/*                                          RSystem                                           */
/**********************************************************************************************/

class RSystem: public RUnit
{
  public:
    _M Vacuum           RSystem(RData* data);
    _M Vacuum           RSystem(RSystem& system, RData* data);
    _V Vacuum           ~RSystem();
    _M RSystem*         buddy() const { return static_cast<RSystem*>(m_buddy); }
    _M void             remove();
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RSYSTEM_HH */
