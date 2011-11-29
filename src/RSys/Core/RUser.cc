#include <QtCore/QRegExp>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RUser.hh>

/**********************************************************************************************/
QRegExp g_userRegExp("\\w+");
/********************************************* RS *********************************************/
/*                                           RUser                                            */
/**********************************************************************************************/

Vacuum RUser :: RUser(RData* data):
  RElement(data),
  m_password("12345"),
  m_created(true)
{
}

/**********************************************************************************************/

Vacuum RUser :: RUser(RUser& other, RData* data):
  RElement(other, data),
  m_userName(other.m_userName),
  m_password(other.m_password),
  m_properties(other.m_properties),
  m_created(other.m_created)
{
}

/**********************************************************************************************/

Vacuum RUser :: ~RUser()
{
}

/**********************************************************************************************/

RUser* RUser :: createUser(RData* data)
{
  RUser* user = new RUser(data);

  user->m_created = false;
  return user;
}

/**********************************************************************************************/

int RUser :: property(const QString& name) const
{
  return m_properties.value(name, 0);
}

/**********************************************************************************************/

void RUser :: remove()
{
  R_GUARD(m_created, Vacuum);

  (*m_data)[onSql](R_S("DROP ROLE %1;").arg(m_userName));
  m_created = false;
}

/**********************************************************************************************/

void RUser :: setDescription(const QString& description)
{
  m_description = description;
}

/**********************************************************************************************/

void RUser :: setPassword(const QString& password)
{
  m_password = password;
  if (m_created)
    (*m_data)[onSql](R_S("ALTER ROLE %1 WITH PASSWORD '%2';").arg(m_userName, m_password));
}

/**********************************************************************************************/

void RUser :: setProperty(const QString& name, int value)
{
  (*m_data)[propertySet](this, name, value);
  if (value == 0)
    m_properties.remove(name);
  else
    m_properties.insert(name, value);
}

/**********************************************************************************************/

void RUser :: setUserName(const QString& userName)
{
  R_GUARD(userName.size() > 2, Vacuum);
  R_GUARD(g_userRegExp.exactMatch(userName), Vacuum);

  if (!m_created)
  {
    (*m_data)[onSql](R_S("CREATE ROLE %1 WITH PASSWORD %2;").arg(userName, m_password));
    m_created = true;
  }
  else
  {
    (*m_data)[onSql](R_S("ALTER ROLE %1 RENAME TO %2;").arg(m_userName, userName));
  }

  m_userName = userName;
}

/**********************************************************************************************/
