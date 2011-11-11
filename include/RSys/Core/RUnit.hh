#ifndef RSYS_CORE_RUNIT_HH
#define RSYS_CORE_RUNIT_HH

/**********************************************************************************************/
#include <QtCore/QVector>
#include <RSys/Core/RElement.hh>
/********************************************* RS *********************************************/
/*                                           RUnit                                            */
/**********************************************************************************************/

class RUnit: public RElement
{
  public:
    _T QVector<double>  UsageVector;

  public:
    _M QString          m_identifier;
    _M QString          m_name;
    _M UsageVector      m_usage0;
    _M UsageVector      m_usage1; // not sure about this one

  public:
    _M Vacuum           RUnit(RData* data);
    _M QString          identifier() const { return m_identifier; }
    _M QString          name() const { return m_name; }
    _M void             setIdentifier(const QString& identifier);
    _M void             setName(const QString& name);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RUNIT_HH */
