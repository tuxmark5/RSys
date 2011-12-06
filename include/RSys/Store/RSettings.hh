#ifndef RSYS_STORE_RSETTINGS_HH
#define RSYS_STORE_RSETTINGS_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                         RSettings                                          */
/**********************************************************************************************/

class RSettings
{
  public:
    _S QString            keyForUnit(RUnit* unit);
    _S void               loadUnitSettings(RData* data);
    _S void               loadUnitSettings(RUnitPtrList* units);
    _S void               saveUnitSettings(RData* data);
    _S void               saveUnitSettings(RUnitPtrList* units);
};

/**********************************************************************************************/

#endif /* RSYS_STORE_RSETTINGS_HH */
