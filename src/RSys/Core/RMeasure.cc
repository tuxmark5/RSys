#include <RSys/Core/RData.hh>
#include <RSys/Core/RMeasure.hh>

/********************************************* RS *********************************************/
/*                                          RMeasure                                          */
/**********************************************************************************************/

Vacuum RMeasure :: RMeasure(RData* data):
  RElement(data)
{
}

/**********************************************************************************************/

void RMeasure :: setIdentifier(const QString& identifier)
{
  m_identifier = identifier;
  m_data->update(this);
}

/**********************************************************************************************/

void RMeasure :: setName(const QString& name)
{
  m_name = name;
  m_data->update(this);
}

/**********************************************************************************************/
