#ifndef RSYS_CORE_RABSTRACT_DATA_HH
#define RSYS_CORE_RABSTRACT_DATA_HH

/**********************************************************************************************/
#include <RSys/Util/RSignal.hh>
/********************************************* RS *********************************************/
/*                                       RAbstractData                                        */
/**********************************************************************************************/

class RAbstractData: public RSignal
{
  public:
    _M Vacuum         RAbstractData();
    _V Vacuum         ~RAbstractData();
    _V void           operator = (const RAbstractData& data) = 0;
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RABSTRACT_DATA_HH */
