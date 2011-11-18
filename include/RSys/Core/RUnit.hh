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
  _F class RResults;

  public:
    _T QVector<double>     UsageVector;
    _T QMap<QDate, double> RUsageMap;

  public:
    _E Type
    {
      Division  = 0,
      Measure   = 1,
      System    = 2
    };

  private:
    _M RUsageMap        m_usageChangeMap; // paraiškų per dieną skaičiaus pokytis
    _M RUsageMap        m_usageMap;       // paraiškų per dieną pradedant nuo datos
  public:
    _M Type             m_type;
    _M QString          m_identifier;
    _M QString          m_name;
    _M int              m_numRefs;
    _M UsageVector      m_usage; // MARTYNO FIELD

  public:
    _M Vacuum           RUnit(Type type, RData* data);
    _M Vacuum           RUnit(RUnit& unit, RData* data);
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
