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

Vacuum RUnit :: RUnit(RUnit& unit, RData* data):
  RElement(unit, data),
  m_type(unit.m_type),
  m_identifier(unit.m_identifier),
  m_name(unit.m_name)
{
}

/**********************************************************************************************/

Vacuum RUnit :: ~RUnit()
{
  m_data->m_unitHash[m_type].remove(m_identifier, this);
}

/**********************************************************************************************/

QString RUnit :: fullName() const
{
  return QString("(%1) %2").arg(m_identifier, m_name);
}

/**********************************************************************************************/

void RUnit :: setIdentifier(const QString& identifier)
{
  m_data->m_unitHash[m_type].remove(m_identifier, this);
  m_identifier = identifier.toUpper();
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
