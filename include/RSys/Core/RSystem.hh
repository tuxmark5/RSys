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

  public:
    _M Vacuum           RSystem(RData* data);
    _M QString          identifier() const { return m_identifier; }
    _M QString          name() const { return m_name; }
    _M void             setIdentifier(const QString& identifier);
    _M void             setName(const QString& name);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RSYSTEM_HH */
