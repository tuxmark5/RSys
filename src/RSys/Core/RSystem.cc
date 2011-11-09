#include <RSys/Core/RData.hh>
#include <RSys/Core/RSystem.hh>

/********************************************* RS *********************************************/
/*                                          RSystem                                           */
/**********************************************************************************************/

Vacuum RSystem :: RSystem(RData* data):
  RElement(data),
  m_visible(true)
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

void RSystem :: setVisible(bool visible)
{
  m_visible = visible;
}

/**********************************************************************************************/
