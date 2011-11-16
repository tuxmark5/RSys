#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSystem.hh>

/********************************************* RS *********************************************/
/*                                         RDivision                                          */
/**********************************************************************************************/

Vacuum RDivision :: RDivision(RData* data):
  RUnit(Division, data)
{
}

/**********************************************************************************************/

Vacuum RDivision :: RDivision(RDivision& division, RData* data):
  RUnit(division, data)
{
  for (auto it = division.m_measureMap.begin(); it != division.m_measureMap.end(); ++it)
    m_measureMap.insert(it.key()->buddy(), it.value());
  for (auto it = division.m_systemMap.begin(); it != division.m_systemMap.end(); ++it)
    m_systemMap.insert(it.key()->buddy(), it.value());
}

/**********************************************************************************************/

Vacuum RDivision :: ~RDivision()
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
