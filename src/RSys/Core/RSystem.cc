#include <RSys/Core/RData.hh>
#include <RSys/Core/RSystem.hh>

/********************************************* RS *********************************************/
/*                                          RSystem                                           */
/**********************************************************************************************/

Vacuum RSystem :: RSystem(RData* data):
  RElement(data)
{
}

/**********************************************************************************************/

void RSystem :: setIdentifier(const QString& identifier)
{
  m_identifier = identifier;
  //m_data->update(this);
}

/**********************************************************************************************/

void RSystem :: setName(const QString& name)
{
  m_name = name;
  //m_data->update(this);
}

/**********************************************************************************************/
