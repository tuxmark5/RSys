#ifndef RSYS_CORE_RDIVISION_HH
#define RSYS_CORE_RDIVISION_HH

/**********************************************************************************************/
#include <RSys/Core/RElement.hh>
/********************************************* RS *********************************************/
/*                                         RDivision                                          */
/**********************************************************************************************/

class RDivision: public RElement
{
  public:
    _M QString        m_identifier;
    _M QString        m_name;
    _M RSystemVector  m_systems;
    _M RMeasureMap    m_measureMap;
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RDIVISION_HH */
