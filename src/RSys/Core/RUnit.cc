#include <RSys/Core/RData.hh>
#include <RSys/Core/RUnit.hh>

/********************************************* RS *********************************************/
/*                                           RUnit                                            */
/**********************************************************************************************/

Vacuum RUnit :: RUnit(Type type, RData* data):
  RElement(data),
  m_type(type)
{
}

/**********************************************************************************************/

Vacuum RUnit :: ~RUnit()
{
  m_data->m_unitHash[m_type].remove(m_identifier, this);
}

/**********************************************************************************************/

void RUnit :: setIdentifier(const QString& identifier)
{
  m_data->m_unitHash[m_type].remove(m_identifier, this);
  m_identifier = identifier;
  m_data->m_unitHash[m_type].insert(m_identifier, this);
  emit m_data->elementChanged(this, RData::TitleOrName);
}

/**********************************************************************************************/

void RUnit :: setName(const QString& name)
{
  m_name = name;
  emit m_data->elementChanged(this, RData::TitleOrName);
}

/**********************************************************************************************/
