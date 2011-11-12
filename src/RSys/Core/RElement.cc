#include <RSys/Core/RData.hh>
#include <RSys/Core/RElement.hh>

/********************************************* RS *********************************************/
/*                                          RElement                                          */
/**********************************************************************************************/

Vacuum RElement :: RElement(RData* data):
  m_data(data),
  m_id(0),
  m_visible(true)
{
}

/**********************************************************************************************/

void RElement :: setVisible(bool visible)
{
  m_visible = visible;
  emit m_data->elementChanged(this, RData::Visibility);
}

/**********************************************************************************************/

