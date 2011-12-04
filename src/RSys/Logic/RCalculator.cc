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
  m_numIntervals(0)
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
    updateMeasures(it->get(), (*it)->m_measureHash);
    updateMeasures(it->get(), (*it)->m_measureHash1);
  }
  updateUsages(m_data->submissions());
  updateUsages(m_data->submissions1());
  updateUsages((RUnitPtrList*) m_data->divisions());
  updateUsages((RUnitPtrList*) m_data->systems());

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

void RCalculator :: updateUsages(RSubmissionPtrList* submissions)
{
  for (auto it = submissions->begin(); it != submissions->end(); it++)
  {
    if ((*it)->measure() != NULL)
    {
      updateUsageChanges((RUnitHash*) &(*it)->measure()->m_divisionUsage, it->get());
      updateUsageChanges((RUnitHash*) &(*it)->measure()->m_systemUsage, it->get());
    }
  }
}

/**********************************************************************************************/

void RCalculator :: updateUsageChanges(RUnitHash* units, RSubmission* submission)
{
  for (auto it = units->begin(); it != units->end(); it++)
  {
    double usage = submission->count() * it.value()
                   / (submission->date0().daysTo(submission->date1()) + 1);
    it.key()->m_usageChangeMap[submission->date0()] += usage;
    it.key()->m_usageChangeMap[submission->date1().addDays(1)] -= usage;
  }
}

/**********************************************************************************************/

void RCalculator :: updateUsages(RUnitPtrList* units)
{
  for (auto unitIt = units->begin(); unitIt != units->end(); unitIt++)
  {
    double usage = 0;
    for (auto usageIt = (*unitIt)->m_usageChangeMap.begin();
              usageIt != (*unitIt)->m_usageChangeMap.end(); usageIt++)
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
  calculateIntervals();
}

/**********************************************************************************************/

void RCalculator :: calculateIntervals()
{
  if (m_numIntervals > 0)
  {
    calculateIntervals((RUnitPtrList*) m_data->divisions());
    calculateIntervals((RUnitPtrList*) m_data->systems());
  }
}

/**********************************************************************************************/

void RCalculator :: calculateIntervals(RUnitPtrList* units)
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
  if (it == usageMap.end()) {
    return 0;
  }
  if (it == usageMap.begin())
  {
    curUsage = 0;
  } else {
    it--;
    curUsage = it.value();
    // tolygus variantas: be tolesnių 2 eilučių
    usage = -polynomialExterpolation(it, usageMap.begin(), usageMap.end(), curDate);
    curDate = it.key();
    it++;
  }
  while (it != usageMap.end() && it.key() < TO(interval))
  {
    usage += curDate.daysTo(it.key()) * curUsage;
    curUsage = it.value();
    curDate = it.key();
    it++;
  }
  // tolygus variantas: usage += curDate.daysTo(TO(interval)) * curUsage;
  if (it != usageMap.begin())
  {
    usage += polynomialExterpolation(--it, usageMap.begin(), usageMap.end(), TO(interval));
  } else {
    return 0;
  }
  return usage;
}

/**********************************************************************************************/

double RCalculator :: polynomialExterpolation(QDate prevDate, double prevUsage,
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
  if (solveSystemOfLinearEquations(matrix, coefficients))
  {
    double answer = 0;
    for (int i = 0; i < 3; i++)
    {
      answer += coefficients[i] / (3 - i) * (pow(prevDate.daysTo(date), 3 - i)
                                            - pow(prevDate.daysTo(startDate), 3 - i));
    }
    return answer;
  } else { // jei neišsprendžiame (gali nutikti, pavyzdžiui, jei neturime
           // ankstesnių duomenų), laikome tolygiu
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

double RCalculator :: polynomialExterpolation(RUsageMap :: iterator it,
                                              RUsageMap :: iterator begin,
                                              RUsageMap :: iterator end,
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
  return polynomialExterpolation(prevDate, prevUsage, startDate, mainUsage,
                                 endDate, nextUsage, nextDate, date);
}
