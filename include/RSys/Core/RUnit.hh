#ifndef RSYS_CORE_RUNIT_HH
#define RSYS_CORE_RUNIT_HH

/**********************************************************************************************/
#include <QtCore/QVector>
#include <RSys/Core/RElement.hh>
/**********************************************************************************************/
extern RUsage g_emptyUsage;
/********************************************* RS *********************************************/
/*                                           RUnit                                            */
/**********************************************************************************************/

class RUnit: public RElement
{
  public:
    _F class RCalculator;

  public:
    _T QVector<RUsage>     UsageVector;
    _T QMap<QDate, double> RUsageMap;

  public:
    _E Type
    {
      Division  = 0,
      Measure   = 1,
      System    = 2
    };

  private:
    _M Type               m_type;
    _M QString            m_identifier;
    _M QString            m_name;
    _M UsageVector        m_usage; // MARTYNO FIELD

    _M RUsageMap          m_usageCntChangeMap; // paraiškų per dieną skaičiaus pokytis
    _M RUsageMap          m_usageCntMap;       // paraiškų per dieną pradedant nuo datos
    _M RUsageMap          m_usageHrsChangeMap; // paraiškų apdorojimo valandų per dieną skaičiaus pokytis
    _M RUsageMap          m_usageHrsMap;       // paraiškų apdorojimo valandų per dieną pradedant nuo datos

    _M int                m_viewMode;
    _M bool               m_visible:  1;

  public:
    _M Vacuum             RUnit(Type type, RData* data);
    _M Vacuum             RUnit(RUnit& unit, RData* data);
    _V Vacuum             ~RUnit();
    _M RUnit*             buddy() const { return static_cast<RUnit*>(m_buddy); }
    _M QString            fullName() const;
    _M QString            identifier() const { return m_identifier; }
    _M bool               isVisible() const { return m_visible; }
    _M QString            name() const { return m_name; }
    _V void               purge();
    _M bool               setIdentifier(const QString& identifier);
    _M bool               setName(const QString& name);
    _M void               setViewMode(int viewMode);
    _M void               setVisible(bool visible);
    _M void               setVisibleRaw(bool visible);
    _M int                type() const { return m_type; }
    _M const UsageVector& usage() const { return m_usage; }
    _M const RUsage&      usageAt(int x) const { return x < m_usage.size() ? m_usage.at(x) : g_emptyUsage; }
    _M int                viewMode() const { return m_viewMode; }

  public:
    _G(void,              viewModeChanged, RUnit* unit);
    _G(void,              visibilityChanged, RUnit* unit);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RUNIT_HH */
