#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Util/RAlgorithm.hh>

/********************************************* RS *********************************************/
/*                                           RData                                            */
/**********************************************************************************************/

Vacuum RData :: RData():
  m_purgeEnabled(true)
{
}

/**********************************************************************************************/

void RData :: clear()
{
  m_divisions.deleteAll();      // deps: measures, systems
  m_submissions.clear();        // deps: measures
  m_submissions1.clear();       // deps: measures

  m_measures.deleteAll();       // deps: -
  m_measures1.deleteAll();      // deps: -
  m_systems.deleteAll();        // deps: -
}

/**********************************************************************************************/

RDivision* RData :: division(const QString& identifier) const
{
  if (RUnit* unit = m_unitHash[RUnit::Division].value(identifier))
    return static_cast<RDivision*>(unit);
  return 0;
}

/**********************************************************************************************/

RMeasure* RData :: measure(const QString& identifier) const
{
  if (RUnit* unit = m_unitHash[RUnit::Measure].value(identifier))
    return static_cast<RMeasure*>(unit);
  return 0;
}

/**********************************************************************************************/

void RData :: operator = (RData& data)
{
  m_purgeEnabled = false;
  clear();
  m_purgeEnabled = true;

  m_measures.clone(data.m_measures, this);
  m_measures1.clone(data.m_measures1, this);
  m_systems.clone(data.m_systems, this);

  m_submissions.clone(data.m_submissions, this);
  m_submissions1.clone(data.m_submissions1, this);
  m_divisions.clone(data.m_divisions, this);

  r_cloneMap(m_unitHash[0], data.m_unitHash[0]);
  r_cloneMap(m_unitHash[1], data.m_unitHash[1]);
  r_cloneMap(m_unitHash[2], data.m_unitHash[2]);
}

/**********************************************************************************************/

void RData :: purgeDivision(RDivision* division)
{
  R_GUARD(m_purgeEnabled, Vacuum);

  for (auto it = m_measures.begin(); it != m_measures.end(); ++it)
    (*it)->m_divisionUsage.remove(division);
}

/**********************************************************************************************/

void RData :: purgeMeasure(RMeasure* measure)
{
  R_GUARD(m_purgeEnabled, Vacuum);

  for (auto it = m_divisions.begin(); it != m_divisions.end(); ++it)
    (*it)->m_measureMap.remove(measure);
}

/**********************************************************************************************/

void RData :: purgeSystem(RSystem* system)
{
  R_GUARD(m_purgeEnabled, Vacuum);

  for (auto it = m_divisions.begin(); it != m_divisions.end(); ++it)
    (*it)->m_systemMap.remove(system);
  for (auto it = m_measures.begin(); it != m_measures.end(); ++it)
    (*it)->m_systemUsage.remove(system);
}

/**********************************************************************************************/

RSystem* RData :: system(const QString& identifier) const
{
  if (RUnit* unit = m_unitHash[RUnit::System].value(identifier))
    return static_cast<RSystem*>(unit);
  return 0;
}

/**********************************************************************************************/
