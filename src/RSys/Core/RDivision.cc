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

void RDivision :: setName(const QString& name)
{
  m_name = name;
  //m_data->update(this);
}

/**********************************************************************************************/

void RDivision :: setVisible(bool visible)
{
  m_visible = visible;
}

/**********************************************************************************************/
