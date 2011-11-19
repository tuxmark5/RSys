#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Core/RSystem.hh>

/********************************************* RS *********************************************/
/*                                           RData                                            */
/**********************************************************************************************/

Vacuum RData :: RData()
{
}

/**********************************************************************************************/

void RData :: clear()
{
  m_divisions.deleteAll();      // deps: measures, systems
  m_submissions.deleteAll();    // deps: measures
  m_submissions1.deleteAll();   // deps: measures

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
  clear();

  m_measures.clone(data.m_measures, this);
  m_measures1.clone(data.m_measures1, this);
  m_systems.clone(data.m_systems, this);

  m_submissions.clone(data.m_submissions, this);
  m_submissions1.clone(data.m_submissions1, this);
  m_divisions.clone(data.m_divisions, this);

  for (int i = 0; i < 3; i++)
  {
    RUnitMultiHash& dst = m_unitHash[i];
    RUnitMultiHash& src = data.m_unitHash[i];

    dst.clear();
    for (auto it = src.begin(); it != src.end(); ++it)
      dst.insert(it.key(), it.value()->buddy());
  }
}

/**********************************************************************************************/

RSystem* RData :: system(const QString& identifier) const
{
  if (RUnit* unit = m_unitHash[RUnit::System].value(identifier))
    return static_cast<RSystem*>(unit);
  return 0;
}

/**********************************************************************************************/
