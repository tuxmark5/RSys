#ifndef RSYS_CORE_RMEASURE_HH
#define RSYS_CORE_RMEASURE_HH

/**********************************************************************************************/
#include <RSys/Core/RElement.hh>
/********************************************* RS *********************************************/
/*                                          RMeasure                                          */
/**********************************************************************************************/

class RMeasure: public RElement
{
  public:
    _M RID              m_groupId;
    _M QString          m_identifier;
    _M QString          m_name;
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RMEASURE_HH */
