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

  public:
    _M Vacuum           RMeasure(RData* data);
    _M QString          identifier() const { return m_identifier; }
    _M QString          name() const { return m_name; }
    _M void             setIdentifier(const QString& identifier);
    _M void             setName(const QString& name);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RMEASURE_HH */
