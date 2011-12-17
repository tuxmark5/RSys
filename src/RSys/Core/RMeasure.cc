#include <RSys/Core/RData.hh>
#include <RSys/Core/RGroup.hh>
#include <RSys/Core/RMeasure.hh>

/********************************************* RS *********************************************/
/*                                          RMeasure                                          */
/**********************************************************************************************/

Vacuum RMeasure :: RMeasure(RData* data, bool planned):
  RUnit(Measure, data),
  m_planned(planned)
{
}

/**********************************************************************************************/

Vacuum RMeasure :: RMeasure(RMeasure& measure, RData* data):
  RUnit(measure, data),
  m_group(measure.m_group ? measure.m_group->buddy() : 0),
  m_planned(measure.m_planned)
{
}

/**********************************************************************************************/

Vacuum RMeasure :: ~RMeasure()
{
  R_NZ(m_data)->purgeMeasure(this);
  setGroup(0);
}

/**********************************************************************************************/

RID RMeasure :: groupId() const
{
  return m_group ? m_group->id() : -1;
}

/**********************************************************************************************/

QString RMeasure :: groupName() const
{
  return m_group ? m_group->name() : QString();
}

/**********************************************************************************************/

RInterval RMeasure :: lastInterval()
{
  R_GUARD(!m_usageMap.empty(), RInterval());

  auto  it    = m_usageMap.end();
  QDate to    = (--it).key().addDays(-1);
  QDate from  = (--it).key();
  return RInterval(from, to);
}

/**********************************************************************************************/

void RMeasure :: purge()
{
  RUnit::purge();
  R_NZ(m_data)->purgeMeasure(this);
  setGroup(0);
}

/**********************************************************************************************/

void RMeasure :: remove()
{
  (*m_data)[measureRemoval](this);
  purge();
  m_data->modify();
}

/**********************************************************************************************/

void RMeasure :: setGroup(RGroup* group)
{
  R_GUARD(m_group != group, Vacuum);

  if (m_group && (m_group->numRefs() <= 3)) // this, list, entity?
    m_data->groups()->removeOne(m_group);
  m_group = group;
}

/**********************************************************************************************/

void RMeasure :: setGroupId(RID group)
{
  setGroup(m_data->group(group));
}

/**********************************************************************************************/

void RMeasure :: setGroupName(const QString& group)
{
  setGroup(m_data->group(group));
}

/**********************************************************************************************/
