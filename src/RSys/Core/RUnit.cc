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
  if (m_data)
  {
    m_data->m_unitHash[m_type].remove(m_identifier, this);
    qDebug() << "UNIT DIES WITH" << m_type << m_identifier;
  }
}

/**********************************************************************************************/

QString RUnit :: fullName() const
{
  return QString("(%1) %2").arg(m_identifier, m_name);
}

/**********************************************************************************************/

bool RUnit :: setIdentifier(const QString& identifier)
{
  QString identifier1 = identifier.trimmed().toUpper();
  R_DATA_GUARD(!identifier1.isEmpty(), false,
    "Elemento identifikatorius negali būti tuščia eilutė.");
  R_DATA_GUARD(!m_data->m_unitHash[m_type].contains(identifier1), false,
    "Elementas su identifikatoriumi <b>%1</b> jau egzistuoja.", .arg(identifier1));

  m_data->m_unitHash[m_type].remove(m_identifier, this);
  m_identifier = identifier1;
  m_data->m_unitHash[m_type].insert(m_identifier, this);
  emit m_data->elementChanged(this, RData::TitleOrName);

  return true;
}

/**********************************************************************************************/

bool RUnit :: setName(const QString& name)
{
  QString name1 = name.trimmed();
  R_DATA_GUARD(!name1.isEmpty(), false,
    "Elemento pavadinimas negali būti tuščia eilutė.");
  m_name = name1;
  emit m_data->elementChanged(this, RData::TitleOrName);
  return true;
}

/**********************************************************************************************/
