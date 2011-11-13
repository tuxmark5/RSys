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
    _E Type
    {
      Division  = 0,
      Measure   = 1,
      System    = 2
    };

  public:
    _M Type             m_type;
    _M QString          m_identifier;
    _M QString          m_name;
    _M int              m_numRefs;

    _M UsageVector      m_usage0;
    _M UsageVector      m_usage1; // not sure about this one

  public:
    _M Vacuum           RUnit(Type type, RData* data);
    _V Vacuum           ~RUnit();
    _M QString          identifier() const { return m_identifier; }
    _M QString          name() const { return m_name; }
    _M void             release() { m_numRefs--; }
    _M void             retain() { m_numRefs++; }
    _M void             setIdentifier(const QString& identifier);
    _M void             setName(const QString& name);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RUNIT_HH */
