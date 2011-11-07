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
    _M RMeasureMap    m_measureMap;
    _M RSystemMap     m_systemMap;

  public:
    _M Vacuum         RDivision(RData* data);
    _M QString        identifier() const { return m_identifier; }
    _M QString        name() const { return m_name; }
    _M void           setIdentifier(const QString& identifier);
    _M void           setName(const QString& name);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RDIVISION_HH */
