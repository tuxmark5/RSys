#include <RSys/Core/RData.hh>
#include <RSys/Core/RElement.hh>

/********************************************* RS *********************************************/
/*                                          RElement                                          */
/**********************************************************************************************/

Vacuum RElement :: RElement(RData* data):
  m_data(data),
  m_buddy(0),
  m_id(0),
  m_null(true),
  m_valid(true)
{
}

/**********************************************************************************************/

Vacuum RElement :: RElement(RElement& element, RData* data):
  m_data(data),
  m_buddy(&element),
  m_id(element.m_id),
  m_null(element.m_null),
  m_valid(element.m_valid)
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

void RElement :: remove()
{
}

/**********************************************************************************************/

void RElement :: setId(RID id)
{
  m_id = id;
}

/**********************************************************************************************/

void RElement :: setValid(bool valid)
{
  m_valid = valid;
}

/**********************************************************************************************/
