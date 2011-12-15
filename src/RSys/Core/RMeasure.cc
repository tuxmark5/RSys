#include <RSys/Core/RData.hh>
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
  m_planned(measure.m_planned)
{
}

/**********************************************************************************************/

Vacuum RMeasure :: ~RMeasure()
{
  R_NZ(m_data)->purgeMeasure(this);
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

void RMeasure :: remove()
{
  (*m_data)[measureRemoval](this);

  RUnit::purge();

  R_NZ(m_data)->purgeMeasure(this);

  m_data->modify();
}

/**********************************************************************************************/
