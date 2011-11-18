#include <RSys/Interface/RResultsModel.hh>
#include <RSys/Logic/RResults.hh>

/********************************************* RS *********************************************/
/*                                          RResults                                          */
/**********************************************************************************************/

Vacuum RResults :: RResults(RData* data):
  m_data(data)
{
}

/**********************************************************************************************/

Vacuum RResults :: ~RResults()
{
}

/**********************************************************************************************/
#include <math.h>
auto RResults :: field(ResultType type, RUnit* unit) -> Getter
{
  switch (type)
  {
    case Usage0: return [](int x) -> QVariant
    {
      return 2.0 * x + sin(x);
    };

    case Usage1: return [](int x) -> QVariant
    {
      return 40.0 - (2.0 * x + sin(x));
    };

    case Identifier: return [=](int) -> QVariant
    {
      return unit->identifier();
    };
  }

  return Getter();
}

/**********************************************************************************************/

void RResults :: registerField(RUnit* unit, RResultsModel* model, int key)
{
  m_fields.insertMulti(unit, Field(model, key));
}

/**********************************************************************************************/

void RResults :: unregisterField(RUnit* unit, RResultsModel* model, int key)
{
  m_fields.remove(unit, Field(model, key));
}

/**********************************************************************************************/

void RResults :: update()
{
  for (auto it = m_data->systems()->begin(); it != m_data->systems()->end(); it++)
  {
    (*it)->m_usageMap.clear();
    (*it)->m_usageChangeMap.clear();
  }
  for (auto it = m_data->measures()->begin(); it != m_data->measures()->end(); it++)
  {
    (*it)->m_systemUsage.clear();
    (*it)->m_divisionUsage.clear();
  }
  for (auto it = m_data->divisions()->begin(); it != m_data->divisions()->end(); it++)
  {
    (*it)->m_usageMap.clear();
    (*it)->m_usageChangeMap.clear();
    updateMeasures(*it, (*it)->m_measureMap);
    updateMeasures(*it, (*it)->m_measureMap1);
  }
  updateUsages(m_data->submissions());
  updateUsages(m_data->submissions1());
  updateUsages((RUnitList*)m_data->divisions());
  updateUsages((RUnitList*)m_data->systems());
}

/**********************************************************************************************/

void RResults :: updateMeasures(RDivision* division, RMeasureMap& measures)
{
  for (auto divIt = measures.begin(); divIt != measures.end(); divIt++)
  {
    divIt.key()->m_divisionUsage.insert(division, divIt.value());
    for (auto sysIt = division->m_systemMap.begin(); sysIt != division->m_systemMap.end(); sysIt++)
    {
      divIt.key()->m_systemUsage[sysIt.key()] += sysIt.value() * divIt.value();
    }
  }
}

/**********************************************************************************************/

void RResults :: updateUsages(RSubmissionList* submissions)
{
  for (auto it = submissions->begin(); it != submissions->end(); it++)
  {
    updateUsageChanges((RUnitMap*) &(*it)->measure()->m_divisionUsage, *it);
    updateUsageChanges((RUnitMap*) &(*it)->measure()->m_systemUsage, *it);
  }
}

/**********************************************************************************************/

void RResults :: updateUsageChanges(RUnitMap* units, RSubmission* submission)
{
  for (auto it = units->begin(); it != units->end(); it++)
  {
    double usage = submission->count() * it.value();
    it.key()->m_usageChangeMap[submission->date0()] += usage;
    it.key()->m_usageChangeMap[submission->date1().addDays(1)] -= usage;
  }
}

void RResults :: updateUsages(RUnitList* units)
{
  for (auto unitIt = units->begin(); unitIt != units->end(); unitIt++)
  {
    double usage = 0;
    for (auto usageIt = (*unitIt)->m_usageChangeMap.begin();
              usageIt != (*unitIt)->m_usageChangeMap.begin(); usageIt++)
    {
      usage += usageIt.value();
      (*unitIt)->m_usageMap.insert(usageIt.key(), usage);
    }
  }
}
