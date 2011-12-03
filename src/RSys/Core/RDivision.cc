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

bool RDivision :: setMeasure(RMeasure* measure, double value)
{
  R_DATA_GUARD(measure, false, "Nerasta priemonė.");
  R_DATA_GUARD(value >= 0.0, false, "Apkrova negali būti neigiama.");

  if (value == 0.0)
  {
    (*m_data)[onMeasureUnset](this, measure);
    m_measureMap.remove(measure);
  }
  else
  {
    (*m_data)[onMeasureSet](this, measure, value);
    m_measureMap.insert(measure, value);
  }
  return true;
}

/**********************************************************************************************/

void RDivision :: setMeasure1(RMeasure* measure, double value)
{
  R_GUARD(measure, Vacuum);

  if (value <= 0.0)
  {
    (*m_data)[onMeasureUnset](this, measure);
    m_measureMap1.remove(measure);
  }
  else
  {
    (*m_data)[onMeasureSet](this, measure, value);
    m_measureMap1.insert(measure, value);
  }
}

/**********************************************************************************************/

void RDivision :: setSystem(RSystem* system, double value)
{
  R_GUARD(system, Vacuum);

  if (!value)
  {
    (*m_data)[onSystemUnset](this, system);
    m_systemMap.remove(system);
  }
  else
  {
    (*m_data)[onSystemSet](this, system, value);
    m_systemMap.insert(system, value);
  }
}

/**********************************************************************************************/
