#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Util/RAlgorithm.hh>

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
  r_cloneMap(m_measureMap, division.m_measureMap);
  r_cloneMap(m_systemMap, division.m_systemMap);
}

/**********************************************************************************************/

Vacuum RDivision :: ~RDivision()
{
  m_data->purgeDivision(this);
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

void RDivision :: setSystem(RSystem* system, double value)
{
  if (!value)
    m_systemMap.remove(system);
  else
    m_systemMap.insert(system, value);
}

/**********************************************************************************************/
