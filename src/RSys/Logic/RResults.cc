#include <RSys/Interface/RResultsModel.hh>
#include <RSys/Logic/RResults.hh>
#include <math.h>

/********************************************* RS *********************************************/
/*                                          RResults                                          */
/**********************************************************************************************/

Vacuum RResults :: RResults(RData* data, QObject* parent):
  QObject(parent),
  m_data(data),
  m_numRecords(0)
{
  m_seasonalLengths[0] = 0;
  m_seasonalLengths[1] = 0;
  m_seasonalLengths[2] = 0;
  m_seasonalLengths[3] = 0;
}

/**********************************************************************************************/

Vacuum RResults :: ~RResults()
{
}

/**********************************************************************************************/

auto RResults :: field(ResultType type, RUnit* unit) -> Getter
{
  switch (type)
  {
    case Date: return [this](int x) -> QVariant
    {
      return std::get<0>(this->m_intervalFun(x));
    };

    case Usage0: return [this](int x) -> QVariant
    {
      return (this->m_interval0.year() - 1995) + 2.0 * x + sin(x);
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

RInterval RResults :: findLowUsageInterval(RUnit* unit)
{
  // HARDCODED STUFF FOR TESTING
  if (m_interval0 == QDate(2012, 01, 01) && m_interval1 == QDate(2012, 06, 01))
  {
    if (m_seasonalLengths[0] > 0)
    {
      uint  mod   = qHash(unit->identifier()) % 20;
      QDate base  = QDate(2012, 02, 01).addDays(mod);

      return RInterval(base, base.addDays(m_seasonalLengths[0]));
    }
  }

  return RInterval();
}

/**********************************************************************************************/

auto RResults :: intervalFun() -> IntervalFun
{
  return [m_interval0](int x) -> Interval
  {
    return Interval(m_interval0.addMonths(x), m_interval0.addMonths(x + 1));
  };
}

/**********************************************************************************************/

void RResults :: registerField(RUnit* unit, RResultsModel* model, int key)
{
  m_fields.insertMulti(unit, Field(model, key));
}

/**********************************************************************************************/

void RResults :: setInterval(QDate date0, QDate date1)
{
  m_interval0     = date0;
  m_interval1     = date1;
  m_intervalFun   = intervalFun();
  m_numRecords    = date0.daysTo(date1) / 30; // temporary HACK

  for (auto it = m_models.begin(); it != m_models.end(); ++it)
    emit (*it)->reset();
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
