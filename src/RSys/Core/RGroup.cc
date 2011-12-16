#include <RSys/Core/RGroup.hh>

/********************************************* RS *********************************************/
/*                                           RGroup                                           */
/**********************************************************************************************/

Vacuum RGroup :: RGroup(RData* data):
  RElement(data)
{

}

/**********************************************************************************************/

Vacuum RGroup :: RGroup(RGroup& group, RData* data):
  RElement(group, data),
  m_name(group.m_name)
{
}

/**********************************************************************************************/

Vacuum RGroup :: ~RGroup()
{
}

/**********************************************************************************************/

void RGroup :: setName(const QString& name)
{
  qDebug() << "SN" << name;
  m_name = name;
}

/**********************************************************************************************/
