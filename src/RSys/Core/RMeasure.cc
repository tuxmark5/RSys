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

void RMeasure :: remove()
{
  (*m_data)[measureRemoval](this);

  RUnit::purge();

  R_NZ(m_data)->purgeMeasure(this);

  m_data->modify();
}

/**********************************************************************************************/
