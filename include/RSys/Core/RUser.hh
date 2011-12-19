#ifndef RSYS_CORE_RUSER_HH
#define RSYS_CORE_RUSER_HH

/**********************************************************************************************/
#include <RSys/Core/RElement.hh>
#include <RSys/Util/RSignal.hh>
/********************************************* RS *********************************************/
/*                                           RUser                                            */
/**********************************************************************************************/

class RUser: public RElement
{
  public:
    _T QHash<QString, int> Properties;

  protected:
    _M QString          m_userName;
    _M QString          m_password;
    _M QString          m_description;
    _M Properties       m_properties;
    _M bool             m_created: 1;

  public:
    _M Vacuum           RUser(RData* data);
    _M Vacuum           RUser(RUser& other, RData* data);
    _V Vacuum           ~RUser();

    _S RUser*           createSuperUser(RData* data);
    _S RUser*           createUser(RData* data);
    _M QString          description() const { return m_description; }
    _M QString          userName() const { return m_userName; }

    _M void             setDescription(const QString& description);
    _M void             setPassword(const QString& password);
    _M void             setUserName(const QString& userName);
    _M void             setUserNameE(const QString& userName);

    _M int              divisionAcc()     const { return m_properties.value("div", 0); }
    _M int              groupAcc()        const { return m_properties.value("grp", 0); }
    _M int              measureAcc()      const { return m_properties.value("mea", 0); }
    _M int              measureAdmAcc()   const { return m_properties.value("meaA", 0); }
    _M int              systemAcc()       const { return m_properties.value("sys", 0); }
    _M int              systemAdmAcc()    const { return m_properties.value("sysA", 0); }
    _M int              submissionAcc()   const { return m_properties.value("sub", 0); }

    _M bool             adminAcc()        const { return m_properties.value("usr", 0); }
    _M bool             divisionModeAcc() const { return m_properties.value("dM", 0); }
    _M bool             systemModeAcc()   const { return m_properties.value("sM", 0); }
    _M bool             resultsAcc()      const { return m_properties.value("res", 0); }
    _M bool             summaryAcc()      const { return m_properties.value("sum", 0); }

    _M int              property(const QString& name) const;
    _M void             remove();
    _M void             setProperty(const QString& name, int value);

  public:
    _G(void,            onSql,          void* source, int type, const QString& sql);
    _G(void,            propertySet,    RUser* user, const QString& prop, int newValue);
    _G(void,            propertyUnset,  RUser* user, const QString& prop);
};

/**********************************************************************************************/

#endif /* RSYS_CORE_RUSER_HH */
