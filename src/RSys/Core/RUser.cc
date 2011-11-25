#include <RSys/Core/RUser.hh>

/********************************************* RS *********************************************/
/*                                           RUser                                            */
/**********************************************************************************************/

Vacuum RUser :: RUser(RAdminData* data):
  m_adminData(data)
{
}

/**********************************************************************************************/

//Vacuum           RUser(RSubmission& other, RData* data);

/**********************************************************************************************/

Vacuum RUser :: ~RUser()
{
}

/**********************************************************************************************/

int RUser :: property(const QString& name) const
{
  return m_properties.value(name, 0);
}

/**********************************************************************************************/

void RUser :: setProperty(const QString& name, int value)
{
  //(*m_adminData)[propertyChange](this, name, value);
  if (value == 0)
    m_properties.remove(name);
  else
    m_properties.insert(name, value);
}

/**********************************************************************************************/
