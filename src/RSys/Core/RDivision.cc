#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>

/********************************************* RS *********************************************/
/*                                         RDivision                                          */
/**********************************************************************************************/

Vacuum RDivision :: RDivision(RData* data):
  RUnit(Division, data)
{
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

void RDivision :: setSystem(RSystem* system, bool value)
{
  if (!value)
    m_systemMap.remove(system);
  else
    m_systemMap.insert(system, value);
}

/**********************************************************************************************/
