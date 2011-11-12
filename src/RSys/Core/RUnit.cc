#include <RSys/Core/RData.hh>
#include <RSys/Core/RUnit.hh>

/********************************************* RS *********************************************/
/*                                           RUnit                                            */
/**********************************************************************************************/

Vacuum RUnit :: RUnit(RData* data):
  RElement(data)
{
}

/**********************************************************************************************/

void RUnit :: setIdentifier(const QString& identifier)
{
  m_identifier = identifier;
  emit m_data->elementChanged(this, RData::TitleOrName);
}

/**********************************************************************************************/

void RUnit :: setName(const QString& name)
{
  m_name = name;
  emit m_data->elementChanged(this, RData::TitleOrName);
}

/**********************************************************************************************/
