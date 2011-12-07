#include <RSys/Logic/RCalculator.hh>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Core/RSubmission.hh>
#include <QVector>
#include <QDate>
#include <cmath>
#include <algorithm>

#define FROM(x) std::get<0>(x)
#define TO(x)   std::get<1>(x)

/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

Vacuum RCalculator :: RCalculator(RData* data):
  m_data(data),
  m_numIntervals(0),
  m_extrapolationEnabled(true)
{
}

/**********************************************************************************************/

Vacuum RCalculator :: ~RCalculator()
{
}

/**********************************************************************************************/

void RCalculator :: update()
{
  /* TODO: Galbūt prireiks mažiausiai apkrauto intervalo paieškai:
  for (auto it = m_data->systems()->begin(); it != m_data->systems()->end(); it++)
  {
    (*it)->m_usageHrsMap.clear();
    (*it)->m_usageHrsChangeMap.clear();
    (*it)->m_usageCntMap.clear();
    (*it)->m_usageCntChangeMap.clear();
  }
  */
  for (auto it = m_data->measures()->begin(); it != m_data->measures()->end(); it++)
  {
    (*it)->m_systemUsage.clear();
    (*it)->m_divisionUsage.clear();
    (*it)->m_usageCntMap.clear();
    (*it)->m_usageCntChangeMap.clear();
  }
  for (auto it = m_data->divisions()->begin(); it != m_data->divisions()->end(); it++)
  {
    /* TODO: Galbūt prireiks mažiausiai apkrauto intervalo paieškai:
    (*it)->m_usageHrsMap.clear();
    (*it)->m_usageHrsChangeMap.clear();
    (*it)->m_usageCntMap.clear();
    (*it)->m_usageCntChangeMap.clear();
    */
    updateMeasures(it->get(), (*it)->m_measureHash);
    updateMeasures(it->get(), (*it)->m_measureHash1);
  }
  updateUsageChanges(m_data->submissions());
  updateUsageChanges(m_data->submissions1());
  // TODO: Galbūt prireiks mažiausiai apkrauto intervalo paieškai:
  // updateUsages((RUnitPtrList*) m_data->divisions());
  // updateUsages((RUnitPtrList*) m_data->systems());
  updateUsages((RUnitPtrList*) m_data->measures());

  calculateIntervals();
}

/**********************************************************************************************/

void RCalculator :: updateMeasures(RDivision* division, RMeasureHash& measures)
{
  for (auto measIt = measures.begin(); measIt != measures.end(); measIt++)
  {
    measIt.key()->m_divisionUsage.insert(division, measIt.value());
    for (auto sysIt = division->m_systemHash.begin(); sysIt != division->m_systemHash.end(); sysIt++)
    {
      measIt.key()->m_systemUsage[sysIt.key()] += sysIt.value() * measIt.value();
    }
  }
}

/**********************************************************************************************/

void RCalculator :: updateUsageChanges(RSubmissionPtrList* submissions)
{
  for (auto it = submissions->begin(); it != submissions->end(); it++)
  {
    if ((*it)->measure() != NULL)
    {
      // TODO: Galbūt prireiks mažiausiai apkrauto intervalo paieškai:
      // updateUsageChanges((UnitHash*) &(*it)->measure()->m_divisionUsage, it->get());
      // updateUsageChanges((UnitHash*) &(*it)->measure()->m_systemUsage, it->get());
      double usage = (double)(*it)->count()
                     / ((*it)->date0().daysTo((*it)->date1()) + 1);
      (*it)->measure()->m_usageCntChangeMap[(*it)->date0()] += usage;
      (*it)->measure()->m_usageCntChangeMap[(*it)->date1().addDays(1)] -= usage;
    }
  }
}

/**********************************************************************************************/

/* TODO: Galbūt prireiks mažiausiai apkrauto intervalo paieškai:
void RCalculator :: updateUsageChanges(UnitHash* units, RSubmission* submission)
{
  for (auto it = units->begin(); it != units->end(); it++)
  {
    double usage = (double)submission->count()
                   / (submission->date0().daysTo(submission->date1()) + 1);
    it.key()->m_usageCntChangeMap[submission->date0()] += usage;
    it.key()->m_usageCntChangeMap[submission->date1().addDays(1)] -= usage;
    usage *= it.value();
    it.key()->m_usageHrsChangeMap[submission->date0()] += usage;
    it.key()->m_usageHrsChangeMap[submission->date1().addDays(1)] -= usage;
  }
}
*/

/**********************************************************************************************/

void RCalculator :: updateUsages(RUnitPtrList* units)
{
  for (auto it = units->begin(); it != units->end(); it++)
  {
    // TODO: Galbūt prireiks mažiausiai apkrauto intervalo paieškai:
    // updateUsages((*it)->m_usageHrsMap, (*it)->m_usageHrsChangeMap);
    updateUsages((*it)->m_usageCntMap, (*it)->m_usageCntChangeMap);
  }
}

/**********************************************************************************************/

void RCalculator :: updateUsages(UsageMap& usageMap, UsageMap& usageChangeMap)
{
  double usage = 0;
  for (auto it = usageChangeMap.begin(); it != usageChangeMap.end(); it++)
  {
    usage += it.value();
    usageMap.insert(it.key(), usage);
  }
}

/**********************************************************************************************/

void RCalculator :: setIntervalFun(IntervalFun intervalFun, int numIntervals)
{
  m_intervalFun = intervalFun;
  m_numIntervals = numIntervals;
  calculateIntervals();
}

/**********************************************************************************************/

void RCalculator :: calculateIntervals()
{
  if (m_numIntervals > 0)
  {
    zeroUsages((RUnitPtrList*)m_data->systems());
    zeroUsages((RUnitPtrList*)m_data->divisions());
    QVector<RInterval> intervals;
    for (int i = 0; i < m_numIntervals; i++)
    {
      intervals.push_back(m_intervalFun(i));
    }
    for (auto it = m_data->measures()->begin(); it != m_data->measures()->end(); it++)
    {
      (*it)->m_usage.clear();
      (*it)->m_usage.reserve(m_numIntervals);
      for (int i = 0; i < m_numIntervals; i++)
      {
        (*it)->m_usage.push_back(qMakePair(0.0, calculateUsage(intervals[i], (*it)->m_usageCntMap)));
      }
      calculateIntervals((UnitHash*)&(*it)->m_divisionUsage, (*it)->m_usage);
      calculateIntervals((UnitHash*)&(*it)->m_systemUsage, (*it)->m_usage);
    }
  }
}

/**********************************************************************************************/

void RCalculator :: zeroUsages(RUnitPtrList* units)
{
  for (auto it = units->begin(); it != units->end(); it++)
  {
    (*it)->m_usage.clear();
    (*it)->m_usage.resize(m_numIntervals);
  }
}

/**********************************************************************************************/

void RCalculator :: calculateIntervals(UnitHash* units, UsageVector& usage)
{
  for (auto it = units->begin(); it != units->end(); it++)
  {
    for (int i = 0; i < m_numIntervals; i++)
    {
      it.key()->m_usage[i].first += usage[i].second * it.value();
      it.key()->m_usage[i].second += usage[i].second;
    }
  }
}

/**********************************************************************************************/

double RCalculator :: calculateUsage(RInterval interval, UsageMap& usageMap)
{
  double usage = 0, curUsage;
  QDate curDate = FROM(interval);
  UsageMap :: iterator it = usageMap.upperBound(curDate);
  if (it == usageMap.end()) {
    return 0;
  }
  if (it == usageMap.begin())
  {
    curUsage = 0;
  } else {
    it--;
    curUsage = it.value();
    if (m_extrapolationEnabled)
    {
      usage = -polynomialExtrapolation(it, usageMap.begin(), usageMap.end(), curDate);
      curDate = it.key();
    }
    it++;
  }
  while (it != usageMap.end() && it.key() < TO(interval))
  {
    usage += curDate.daysTo(it.key()) * curUsage;
    curUsage = it.value();
    curDate = it.key();
    it++;
  }
  if (it != usageMap.begin())
  {
    if (m_extrapolationEnabled)
    {
      usage += polynomialExtrapolation(--it, usageMap.begin(), usageMap.end(), TO(interval));
    } else {
      usage += curDate.daysTo(TO(interval)) * curUsage;
    }
  } else {
    return 0;
  }
  if (usage < MIN_USAGE) return 0; // galbūt netinkama vieta
  return usage;
}

/**********************************************************************************************/

double RCalculator :: polynomialExtrapolation(QDate prevDate, double prevUsage,
                                              QDate startDate, double mainUsage,
                                              QDate endDate, double nextUsage,
                                              QDate nextDate, QDate date)
{
  double matrix[3][4];
  double coefficients[3]; // antro laipsnio polinomo koeficientai
                          // (koeficientas prie laipsnio i yra indeksu 2 - i)
  // susikuriame matricą, kurią išsprendę gausime ieškomos funkcijos koeficientus
  // prevDate laikysime abscisės pradžia

  for (int i = 1; i <= 3; i++)
  {
    matrix[0][3 - i] = pow(prevDate.daysTo(startDate), i) / i;
    matrix[1][3 - i] = (pow(prevDate.daysTo(endDate), i)
                       - pow(prevDate.daysTo(startDate), i)) / i;
    matrix[2][3 - i] = (pow(prevDate.daysTo(nextDate), i)
                       - pow(prevDate.daysTo(endDate), i)) / i;
  }
  // lygybių sprendiniai (norimos atitinkamų integralų reikšmės)
  matrix[0][3] = prevDate.daysTo(startDate) * prevUsage;
  matrix[1][3] = startDate.daysTo(endDate) * mainUsage;
  matrix[2][3] = endDate.daysTo(nextDate) * nextUsage;
  if (solveSystemOfLinearEquations(matrix, coefficients)
      && nonNegativeInInterval(coefficients, prevDate.daysTo(startDate),
                         prevDate.daysTo(endDate)))
  {
    double answer = 0;
    for (int i = 0; i < 3; i++)
    {
      answer += coefficients[i] / (3 - i) * (pow(prevDate.daysTo(date), 3 - i)
                                            - pow(prevDate.daysTo(startDate), 3 - i));
    }
    return answer;
  } else { // jei neišsprendžiame (gali nutikti, pavyzdžiui, jei neturime
   // ankstesnių duomenų) arba galime gauti neigiamas apkrovas, laikome tolygiu
    return startDate.daysTo(date) * mainUsage;
  }
}

/**********************************************************************************************/

bool RCalculator :: solveSystemOfLinearEquations(double matrix[3][4],
                                                 double solution[3])
{ // Gauso metodas
  const int numRows = 3;
  const int numCols = 4;
  // žemiau pateiktas algoritmas teisingas, tik kai numRows + 1 == numCols
  bool uniqueSolution = true;
  for (int i = 0; i < numRows; i++)
  {
    int maxi = i;
    for (int j = i + 1; j < numRows; j++)
    {
      if (abs(matrix[maxi][i]) < abs(matrix[j][i]))
      {
        maxi = j;
      }
    }
    if (matrix[maxi][i] != 0)
    {
      for (int j = 0; j < numCols && i != maxi; j++) // sukeičiame matricas maxi, i
      {
        std::swap(matrix[maxi][j], matrix[i][j]);
      }
      for (int j = numCols - 1; j >= i; j--) // pasidarome matrix[i][i] == 1
      {
        matrix[i][j] /= matrix[i][i];
      }
      for (int j = i + 1; j < numRows; j++)
      { // tolesnėse eilutėse i-ajame stulpelyje pasidarome 0
        for (int k = numCols - 1; k >= i; k--)
        {
          matrix[j][k] -= matrix[i][k] * matrix[j][i];
        }
      }
    } else {
      uniqueSolution = false;
    }
  }
  // formuoja sprendinį
  for (int i = numRows - 1; i >= 0; i--)
  {
    solution[i] = matrix[i][numCols - 1];
    for (int j = i + 1; j < numCols - 1; j++)
    {
      solution[i] -= solution[j] * matrix[i][j];
    }
  }
  return uniqueSolution;
}

/**********************************************************************************************/

double RCalculator :: polynomialExtrapolation(UsageMap :: iterator it,
                                              UsageMap :: iterator begin,
                                              UsageMap :: iterator end,
                                              QDate date)
{
  QDate prevDate, startDate, endDate, nextDate;
  double prevUsage, mainUsage, nextUsage;
  if (it == begin)
  {
    prevDate = it.key();
    prevUsage = 0;
  }
  else
  {
    it--;
    prevDate = it.key();
    prevUsage = it.value();
    it++;
  }
  startDate = it.key();
  mainUsage = it.value();
  it++;
  if (it == end)
  {
    return 0;
  }
  endDate = it.key();
  nextUsage = it.value();
  it++;
  if (it == end)
  {
    nextDate = endDate;
  } else {
    nextDate = it.key();
  }
  return polynomialExtrapolation(prevDate, prevUsage, startDate, mainUsage,
                                 endDate, nextUsage, nextDate, date);
}

/**********************************************************************************************/

bool RCalculator :: nonNegativeInInterval(double coefficients[3], int from, int to)
{
  double discriminant = coefficients[1] * coefficients[1]
                        - 4 * coefficients[0] * coefficients[2];
  if (discriminant <= 0)
  {
    return coefficients[0] > 0;
  }
  double roots[] = {(-coefficients[1] - sqrt(discriminant)) / (2 * coefficients[0]),
                    (-coefficients[1] + sqrt(discriminant)) / (2 * coefficients[0])};
  if (roots[0] > roots[1]) std::swap(roots[0], roots[1]);
  return roots[0] >= to || roots[1] <= from;
}

/**********************************************************************************************/

 void RCalculator :: setExtrapolationEnabled(bool enabled)
 {
   m_extrapolationEnabled = enabled;
 }
