#include <RSys/Logic/RCalculator.hh>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Core/RSubmission.hh>
#include <QVector>
#include <QDate>

#define FROM(x) std::get<0>(x)
#define TO(x)   std::get<1>(x)

/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

Vacuum RCalculator :: RCalculator(RData* data):
  m_data(data)
{
}

/**********************************************************************************************/

Vacuum RCalculator :: ~RCalculator()
{
}

/**********************************************************************************************/

void RCalculator :: update()
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

void RCalculator :: updateMeasures(RDivision* division, RMeasureMap& measures)
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

void RCalculator :: updateUsages(RSubmissionList* submissions)
{
  for (auto it = submissions->begin(); it != submissions->end(); it++)
  {
    updateUsageChanges((RUnitMap*) &(*it)->measure()->m_divisionUsage, *it);
    updateUsageChanges((RUnitMap*) &(*it)->measure()->m_systemUsage, *it);
  }
}

/**********************************************************************************************/

void RCalculator :: updateUsageChanges(RUnitMap* units, RSubmission* submission)
{
  for (auto it = units->begin(); it != units->end(); it++)
  {
    double usage = submission->count() * it.value();
    it.key()->m_usageChangeMap[submission->date0()] += usage;
    it.key()->m_usageChangeMap[submission->date1().addDays(1)] -= usage;
  }
}

/**********************************************************************************************/

void RCalculator :: updateUsages(RUnitList* units)
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

/**********************************************************************************************/

void RCalculator :: setIntervalFun(IntervalFun intervalFun, int numIntervals)
{
  m_intervalFun = intervalFun;
  m_numIntervals = numIntervals;
  calculateIntervals((RUnitList*) m_data->divisions());
  calculateIntervals((RUnitList*) m_data->systems());
}

/**********************************************************************************************/

void RCalculator :: calculateIntervals(RUnitList* units)
{
  QVector<RInterval> intervals;
  for (int i = 0; i < m_numIntervals; i++)
  {
    intervals.push_back(m_intervalFun(i));
  }
  for (auto unitIt = units->begin(); unitIt != units->end(); unitIt++)
  {
    (*unitIt)->m_usage.resize(m_numIntervals);
    for (int i = 0; i < m_numIntervals; i++)
    {
      (*unitIt)->m_usage[i] = calculateUsage(intervals[i], (*unitIt)->m_usageMap);
    }
  }
}

/**********************************************************************************************/

double RCalculator :: calculateUsage(RInterval interval, RUsageMap& usageMap)
{
  double usage = 0, curUsage;
  QDate curDate = FROM(interval);
  RUsageMap :: iterator it = usageMap.upperBound(curDate);
  if (it == usageMap.begin())
  {
    curUsage = 0;
  } else {
    it--;
    curUsage = it.value();
    it++;
  }
  while (it != usageMap.end() && it.key() < TO(interval))
  {
    usage += curDate.daysTo(it.key()) * curUsage;
    curUsage = it.value();
    curDate = it.key();
    it++;
  }
  usage += curDate.daysTo(TO(interval)) * curUsage;
  return usage;
}
