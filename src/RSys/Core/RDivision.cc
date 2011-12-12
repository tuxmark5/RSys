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
  r_cloneMap(m_measureHash, division.m_measureHash);
  r_cloneMap(m_systemHash, division.m_systemHash);
}

/**********************************************************************************************/

Vacuum RDivision :: ~RDivision()
{
  R_NZ(m_data)->purgeDivision(this);
}

/**********************************************************************************************/

void RDivision :: purge()
{
  RUnit::purge();

  for (auto it = m_measureHash.begin(); it != m_measureHash.end(); ++it)
    (*m_data)[onMeasureUnset](this, it.key());
  for (auto it = m_systemHash.begin(); it != m_systemHash.end(); ++it)
    (*m_data)[onSystemUnset](this, it.key());

  m_measureHash.clear();
  m_systemHash.clear();
  R_NZ(m_data)->purgeDivision(this);
}

/**********************************************************************************************/

void RDivision :: remove()
{
  purge();
  m_data->modify();
}

/**********************************************************************************************/

bool RDivision :: setMeasure(RMeasure* measure, double value)
{
  R_DATA_GUARD(measure, false, "Nerasta priemonė.");
  R_DATA_GUARD(value >= 0.0, false, "Apkrova negali būti neigiama.");

  if (value == 0.0)
  {
    auto it = m_measureHash.find(measure);
    if (it != m_measureHash.end())
    {
      (*m_data)[onMeasureUnset](this, measure);
      m_measureHash.erase(it);
    }
  }
  else
  {
    (*m_data)[onMeasureSet](this, measure, value);
    m_measureHash.insert(measure, value);
  }

  m_data->modify();
  return true;
}

/**********************************************************************************************/

void RDivision :: setMeasure1(RMeasure* measure, double value)
{
  R_DATA_GUARD(measure, Vacuum, "Nerasta priemonė.");
  R_DATA_GUARD(value >= 0.0, Vacuum, "Apkrova negali būti neigiama.");

  if (value == 0.0)
  {
    (*m_data)[onMeasureUnset](this, measure);
    m_measureHash1.remove(measure);
  }
  else
  {
    (*m_data)[onMeasureSet](this, measure, value);
    m_measureHash1.insert(measure, value);
  }

  m_data->modify();
}

/**********************************************************************************************/

void RDivision :: setSystem(RSystem* system, double value)
{
  R_GUARD(system, Vacuum);
  R_DATA_GUARD((value == 0) || (value == 1), Vacuum,
    "Šiame lauke galima įvesti tik 0 arba 1");

  if (value == 0)
  {
    auto it = m_systemHash.find(system);
    if (it != m_systemHash.end())
    {
      (*m_data)[onSystemUnset](this, system);
      m_systemHash.erase(it);
    }
  }
  else
  {
    (*m_data)[onSystemSet](this, system, value);
    m_systemHash.insert(system, value);
  }

  m_data->modify();
}

/**********************************************************************************************/
