#include <RSys/Core/RData.hh>
#include <RSys/Core/RElement.hh>

/********************************************* RS *********************************************/
/*                                          RElement                                          */
/**********************************************************************************************/

Vacuum RElement :: RElement(RData* data):
  m_data(data),
  m_buddy(0),
  m_id(0),
  m_valid(true),
  m_visible(true)
{
}

/**********************************************************************************************/

Vacuum RElement :: RElement(RElement& element, RData* data):
  m_data(data),
  m_buddy(&element),
  m_id(element.m_id),
  m_valid(element.m_valid),
  m_visible(element.m_visible)
{
  element.m_buddy = this;
}

/**********************************************************************************************/

Vacuum RElement :: ~RElement()
{
  if (m_buddy)
  {
    m_buddy->m_buddy = 0;
    m_buddy = 0;
  }
}

/**********************************************************************************************/

void RElement :: setValid(bool valid)
{
  m_valid = valid;
}

/**********************************************************************************************/

void RElement :: setVisible(bool visible)
{
  m_visible = visible;
  emit m_data->elementChanged(this, RData::Visibility);
}

/**********************************************************************************************/

