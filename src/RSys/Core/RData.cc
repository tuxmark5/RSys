#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSystem.hh>

/********************************************* RS *********************************************/
/*                                           RData                                            */
/**********************************************************************************************/

Vacuum RData :: RData()
{
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

RSystem* RData :: system(const QString& identifier) const
{
  if (RUnit* unit = m_unitHash[RUnit::System].value(identifier))
    return static_cast<RSystem*>(unit);
  return 0;
}

/**********************************************************************************************/
