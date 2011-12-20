#include <RSys/Core/RData.hh>
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

bool RGroup :: setName(const QString& name)
{
  // FIXME Nėra patikrinimo ar vardas unikalus.
  QString name1 = name.trimmed();
  R_DATA_GUARD(!name1.isEmpty(), false, "Krypties pavadinimas negali būti tuščia eilutė.");
  m_name = name1;
  return true;
}

/**********************************************************************************************/
