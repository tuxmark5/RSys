#ifndef RSYS_CORE_RSYSTEM_HH
#define RSYS_CORE_RSYSTEM_HH

/**********************************************************************************************/
#include <RSys/Core/RElement.hh>
/********************************************* RS *********************************************/
/*                                          RSystem                                           */
/**********************************************************************************************/

class RSystem: public RElement
{
  public:
    _M QString          m_identifier;
    _M QString          m_name;
    _M RDivisionVector  m_divisions;
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RSYSTEM_HH */
