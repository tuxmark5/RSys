#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>

/********************************************* RS *********************************************/
/*                                         RDivision                                          */
/**********************************************************************************************/

Vacuum RDivision :: RDivision(RData* data):
  RElement(data),
  m_visible(true)
{
}

/**********************************************************************************************/

void RDivision :: setIdentifier(const QString& identifier)
{
  m_identifier = identifier;
  //m_data->update(this);
}

/**********************************************************************************************/

void RDivision :: setMeasure(RMeasure* measure, double value)
{
  if (value <= 0.0)
    m_measureMap.remove(measure);
  else
    m_measureMap.insert(measure, value);
}

/**********************************************************************************************/

void RDivision :: setMeasure1(RMeasure* measure, double value)
{
  if (value <= 0.0)
    m_measureMap1.remove(measure);
  else
    m_measureMap1.insert(measure, value);
}

/**********************************************************************************************/

void RDivision :: setName(const QString& name)
{
  m_name = name;
  //m_data->update(this);
}

/**********************************************************************************************/

void RDivision :: setSystem(RSystem* system, bool value)
{
  if (!value)
    m_systemMap.remove(system);
  else
    m_systemMap.insert(system, value);
}

/**********************************************************************************************/

void RDivision :: setVisible(bool visible)
{
  m_visible = visible;
}

/**********************************************************************************************/
