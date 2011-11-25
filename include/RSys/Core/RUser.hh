#ifndef RSYS_CORE_RUSER_HH
#define RSYS_CORE_RUSER_HH

/**********************************************************************************************/
#include <RSys/Core/RElement.hh>
#include <RSys/Util/RSignal.hh>
/********************************************* RS *********************************************/
/*                                           RUser                                            */
/**********************************************************************************************/

class RUser
{
  public:
    _T QHash<QString, int> Properties;

  protected:
    _M RAdminData*      m_adminData;
    _M QString          m_userName;
    _M Properties       m_properties;

  public:
    _M Vacuum           RUser(RAdminData* data);
    //_M Vacuum           RUser(RSubmission& other, RData* data);
    _V Vacuum           ~RUser();
    _M int              divisionAcc()     const { return m_properties.value("div", 0); }
    _M int              measureAcc()      const { return m_properties.value("mea", 0); }
    _M int              measureAdmAcc()   const { return m_properties.value("meaA", 0); }
    _M int              systemAcc()       const { return m_properties.value("sys", 0); }
    _M int              systemAdmAcc()    const { return m_properties.value("sysA", 0); }
    _M int              submissionAcc()   const { return m_properties.value("sub", 0); }

    _M bool             divisionModeAcc() const { return m_properties.value("dM", 0); }
    _M bool             systemModeAcc()   const { return m_properties.value("sM", 0); }
    _M bool             resultsAcc()      const { return m_properties.value("res", 0); }
    _M bool             summaryAcc()      const { return m_properties.value("sum", 0); }

    _M int              property(const QString& name) const;
    _M void             setProperty(const QString& name, int value);

  public:
    _G(void,            propertyChange, RUser* user, const QString& prop, int newValue);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RUSER_HH */
