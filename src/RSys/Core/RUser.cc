#include <QtCore/QRegExp>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RUser.hh>

/**********************************************************************************************/
QRegExp g_userRegExp("[A-Za-z0-9]+");
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

RUser* RUser :: createSuperUser(RData* data)
{
  RUser* user = new RUser(data);

  user->m_userName      = "user";
  user->m_description   = "user";
  user->m_properties.insert("div",    2);
  user->m_properties.insert("mea",    2);
  user->m_properties.insert("meaA",   2);
  user->m_properties.insert("sys",    2);
  user->m_properties.insert("sysA",   2);
  user->m_properties.insert("sub",    2);

  user->m_properties.insert("dM",     2);
  user->m_properties.insert("sM",     2);
  user->m_properties.insert("res",    1);
  user->m_properties.insert("sum",    1);
  user->m_properties.insert("imp",    1);
  return user;
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
  (*m_data)[onSql]((void*) this, 0, R_S("ALTER ROLE %1 WITH PASSWORD '%2';")
    .arg(m_userName, m_password.replace("'", "''")));
}

/**********************************************************************************************/

void RUser :: setProperty(const QString& name, int value)
{
  R_GUARD(m_properties.value(name, 0) != value, Vacuum);

  (*m_data)[propertySet](this, name, value);
  if (value == 0)
    m_properties.remove(name);
  else
    m_properties.insert(name, value);
}

/**********************************************************************************************/

void RUser :: setUserName(const QString& userName)
{
  m_userName = userName;
}

/**********************************************************************************************/

void RUser :: setUserNameE(const QString& userName)
{
  QString userName1 = userName.toLower();

  R_DATA_GUARD(m_userName.isNull(), Vacuum,
    "Dėl DB apribojimų vartotojo vardų keisti neleidžiama.");
  R_DATA_GUARD(userName1.size() >= 4, Vacuum,
    "Per trumpas naudotojo vardas. Minimalus leistinas ilgis yra 4 simboliai.");
  R_DATA_GUARD(g_userRegExp.exactMatch(userName1), Vacuum,
    "Naudotojo varde gali būti tik mažosios ir didžiosios lotyniškos raidės bei skaitmenys");
  R_DATA_GUARD(!m_data->user(userName1), Vacuum,
    "Toks naudotojas jau egzistuoja");

  m_created   = true;
  m_userName  = userName1;
}

/**********************************************************************************************/
