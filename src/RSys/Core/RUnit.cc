#include <RSys/Core/RData.hh>
#include <RSys/Core/RUnit.hh>

/**********************************************************************************************/
RUsage g_emptyUsage;
/********************************************* RS *********************************************/
/*                                           RUnit                                            */
/**********************************************************************************************/

Vacuum RUnit :: RUnit(Type type, RData* data):
  RElement(data),
  m_type(type),
  m_viewMode(-1),
  m_visible(true)
{
}

/**********************************************************************************************/

Vacuum RUnit :: RUnit(RUnit& unit, RData* data):
  RElement            (unit, data),
  m_type              (unit.m_type),
  m_identifier        (unit.m_identifier),
  m_name              (unit.m_name),
  m_usage             (unit.m_usage),
  m_lowestUsage       (unit.m_lowestUsage),
  m_viewMode          (unit.m_viewMode),
  m_visible           (unit.m_visible)
{
}

/**********************************************************************************************/

Vacuum RUnit :: ~RUnit()
{
  R_NZ(m_data)->m_unitHash[m_type].remove(m_identifier, this);
}

/**********************************************************************************************/

QString RUnit :: fullName() const
{
  return QString("(%1) %2").arg(m_identifier, m_name);
}

/**********************************************************************************************/

void RUnit :: purge()
{
  R_GUARD(m_data, Vacuum);

  m_data->m_unitHash[m_type].remove(m_identifier, this);
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
  m_identifier  = identifier1;
  m_null        = false;
  m_data->m_unitHash[m_type].insert(m_identifier, this);
  emit m_data->elementChanged(this, RData::TitleOrName);

  m_data->modify();
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

  m_data->modify();
  return true;
}

/**********************************************************************************************/

void RUnit :: setViewMode(int viewMode)
{
  m_viewMode = viewMode;
  (*m_data)[viewModeChanged](this);
}

/**********************************************************************************************/

void RUnit :: setVisible(bool visible)
{
  m_visible = visible;
  emit m_data->visibilityChanged(this);
  (*m_data)[visibilityChanged](this);
}

/**********************************************************************************************/

void RUnit :: setVisibleRaw(bool visible)
{
  m_visible = visible;
  (*m_data)[visibilityChanged](this);
}

/**********************************************************************************************/
