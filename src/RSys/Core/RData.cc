#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Core/RUser.hh>
#include <RSys/Util/RAlgorithm.hh>

/********************************************* RS *********************************************/
/*                                           RData                                            */
/**********************************************************************************************/

Vacuum RData :: RData():
  m_purgeEnabled(true)
{
}

/**********************************************************************************************/

Vacuum RData :: ~RData()
{
  m_purgeEnabled = false;
}

/**********************************************************************************************/

void RData :: calculateIntervals()
{
  m_interval0 = QDate();
  m_interval1 = QDate();
  calculateIntervals(submissions());
  calculateIntervals(submissions1());
}

/**********************************************************************************************/

void RData :: calculateIntervals(RSubmissionPtrList* submissions)
{
  for (auto it = submissions->begin(); it != submissions->end(); ++it)
  {
    if (((*it)->date0() < m_interval0) || m_interval0.isNull()) m_interval0 = (*it)->date0();
    if (((*it)->date1() > m_interval1) || m_interval1.isNull()) m_interval1 = (*it)->date1();
  }

  emit globalIntervalChanged();
}

/**********************************************************************************************/

void RData :: clear()
{
  m_divisions.clear();          // deps: measures, systems
  m_submissions.clear();        // deps: measures
  m_submissions1.clear();       // deps: measures

  m_measures.clear();           // deps: -
  m_measures1.deleteAll();      // deps: -
  m_systems.clear();            // deps: -
  m_users.clear();

  m_unitHash[RUnit::Division].clear();
  m_unitHash[RUnit::Measure].clear();
  m_unitHash[RUnit::System].clear();
}

/**********************************************************************************************/

RDivision* RData :: division(RID id) const
{
  for (auto it = m_divisions.begin(); it != m_divisions.end(); ++it)
    if ((*it)->id() == id)
      return it->get();
  return 0;
}

/**********************************************************************************************/

RDivision* RData :: division(const QString& identifier) const
{
  if (RUnit* unit = m_unitHash[RUnit::Division].value(identifier))
    return static_cast<RDivision*>(unit);
  return 0;
}

/**********************************************************************************************/

void RData :: enableIntervalTracking()
{
  (*this)[RSubmission::date0Changed]      << std::bind(&RData::onDate0Change, this, _1, _2);
  (*this)[RSubmission::date1Changed]      << std::bind(&RData::onDate1Change, this, _1, _2);
  (*this)[RSubmission::submissionRemoval] << std::bind(&RData::onSubmissionRemoval, this, _1);
}

/**********************************************************************************************/

RMeasure* RData :: measure(RID id) const
{
  for (auto it = m_measures.begin(); it != m_measures.end(); ++it)
    if ((*it)->id() == id)
      return it->get();
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

void RData :: onDate0Change(RSubmission* submission, QDate oldDate0)
{
  R_GUARD(submission->date0().isValid(), Vacuum);
  R_GUARD(!submission->isPlanned(), Vacuum);

  /**/ if (submission->date0() < m_interval0)
  {
    m_interval0 = submission->date0();
    emit globalIntervalChanged();
  }
  else if (oldDate0 == m_interval0)
    calculateIntervals();
  validateSubmissions1();
}

/**********************************************************************************************/

void RData :: onDate1Change(RSubmission* submission, QDate oldDate1)
{
  R_GUARD(submission->date1().isValid(), Vacuum);
  R_GUARD(!submission->isPlanned(), Vacuum);

  /**/ if (submission->date1() > m_interval1)
  {
    m_interval1 = submission->date1();
    emit globalIntervalChanged();
  }
  else if (oldDate1 == m_interval1)
    calculateIntervals();
  validateSubmissions1();
}

/**********************************************************************************************/

void RData :: onSubmissionRemoval(RSubmission* submission)
{
  R_GUARD(!submission->isPlanned(), Vacuum);

  bool left   = m_interval0.isValid() && (m_interval0 == submission->date0());
  bool right  = m_interval1.isValid() && (m_interval1 == submission->date1());

  if (left || right)
    calculateIntervals();
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
  m_users.clone(data.m_users, this);

  m_submissions.clone(data.m_submissions, this);
  m_submissions1.clone(data.m_submissions1, this);
  m_divisions.clone(data.m_divisions, this);

  r_cloneMap(m_unitHash[0], data.m_unitHash[0]);
  r_cloneMap(m_unitHash[1], data.m_unitHash[1]);
  r_cloneMap(m_unitHash[2], data.m_unitHash[2]);

  m_interval0 = data.m_interval0;
  m_interval1 = data.m_interval1;
}

/**********************************************************************************************/

void RData :: purgeDivision(RDivision* division)
{
  R_GUARD(m_purgeEnabled, Vacuum);

  for (auto it = m_measures.begin(); it != m_measures.end(); ++it)
    (*it)->m_unitUsage.remove(division);
}

/**********************************************************************************************/

void RData :: purgeMeasure(RMeasure* measure)
{
  R_GUARD(m_purgeEnabled, Vacuum);

  if (!measure->isPlanned())
  {
    for (auto it = m_divisions.begin(); it != m_divisions.end(); ++it)
      (*it)->setMeasure(measure, 0);
  }
  else
  {
    for (auto it = m_divisions.begin(); it != m_divisions.end(); ++it)
      (*it)->setMeasure1(measure, 0);
  }

  m_submissions.removeIf([=](RSubmission* s) -> bool
  {
    return s->measure() == measure;
  });
}

/**********************************************************************************************/

void RData :: purgeSystem(RSystem* system)
{
  R_GUARD(m_purgeEnabled, Vacuum);

  for (auto it = m_divisions.begin(); it != m_divisions.end(); ++it)
    (*it)->setSystem(system, 0);
  for (auto it = m_measures.begin(); it != m_measures.end(); ++it)
    (*it)->m_unitUsage.remove(system);
}

/**********************************************************************************************/

void RData :: setModified(bool modified)
{
  m_modified = modified;
}

/**********************************************************************************************/

RSystem* RData :: system(RID id) const
{
  for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
    if ((*it)->id() == id)
      return it->get();
  return 0;
}

/**********************************************************************************************/

RSystem* RData :: system(const QString& identifier) const
{
  if (RUnit* unit = m_unitHash[RUnit::System].value(identifier))
    return static_cast<RSystem*>(unit);
  return 0;
}

/**********************************************************************************************/

RUser* RData :: user(RID id) const
{
  for (auto it = m_users.begin(); it != m_users.end(); ++it)
    if ((*it)->id() == id)
      return it->get();
  return 0;
}

/**********************************************************************************************/

RUser* RData :: user(const QString& userName) const
{
  for (auto it = m_users.begin(); it != m_users.end(); ++it)
    if ((*it)->userName() == userName)
      return it->get();
  return 0;
}

/**********************************************************************************************/

void RData :: validateSubmissions1()
{
  for (auto& x: m_submissions1)
    x->validate();
}

/**********************************************************************************************/
