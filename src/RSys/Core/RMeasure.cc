#include <RSys/Core/RData.hh>
#include <RSys/Core/RMeasure.hh>

/********************************************* RS *********************************************/
/*                                          RMeasure                                          */
/**********************************************************************************************/

Vacuum RMeasure :: RMeasure(RData* data):
  RUnit(Measure, data)
{
}

/**********************************************************************************************/

Vacuum RMeasure :: RMeasure(RMeasure& measure, RData* data):
  RUnit(measure, data)
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
}

/**********************************************************************************************/
