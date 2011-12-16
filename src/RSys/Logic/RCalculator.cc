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

#define FROM(x)       std::get<0>(x)
#define TO(x)         std::get<1>(x)
#define IS_LEAP(x)    (x).daysInYear() == 366
#define MAGIC         2.718281828

/**********************************************************************************************/

/**
 * Informacija apie priemonės apkrovų įrašus jų teisingumo patikrinimui.
 */
struct MeasureInfo
{
  QMap<QDate, RSubmissionPtr> m_usefulSubmissions; // smulkiausi korektiški įrašai
                                                   // pagal intervalo pradžią
  QMap<QDate, QDate>          m_invalidIntervals; // kur yra susikertančių intervalų
  QVector<RSubmissionPtr>     m_splitSubmissions; // kurie buvo patikslinti
};

/********************************************* RS *********************************************/
/*                                        RCalculator                                         */
/**********************************************************************************************/

Vacuum RCalculator :: RCalculator(RData* data):
  m_data(data),
  m_validMeasures(data->measures(), data->measures1()),
  m_validSubmissions(data->submissions(), data->submissions1()),
  m_validDivisions(data->divisions()),
  m_numIntervals(0),
  m_intrapolationEnabled(true)
{
}

/**********************************************************************************************/

Vacuum RCalculator :: ~RCalculator()
{
}

/**********************************************************************************************/

void RCalculator :: update()
{
  for (auto measure : *(m_data->measures()))
  {
    measure->m_unitUsage.clear();
    measure->m_usageMap.clear();
  }
  for (auto division : m_validDivisions)
  {
    updateMeasures(division, division->m_measureHash);
    updateMeasures(division, division->m_measureHash1);
  }

  QHash<RMeasure*, MeasureInfo> measureInfos;
  for (auto submission : m_validSubmissions)
  {
    QDate from = submission->date0();
    QDate to   = submission->date1().addDays(1);
    MeasureInfo& info = measuresInfos[submission->measure()];

    { // patikriname, ar nesikerta su anksčiau susikirtusiais
      auto it = info.m_invalidIntervals.lower_bound(to);
      if (it != info.m_invalidIntervals.begin() && (--it).value() > from)
      {
        submission->setValid(false);
        if (from >= it.key())
        {
          if (to > it.value()) it.value() = to;
        } else {
          if (to < it.value()) to = it.value();
          do
          {
            if (it != info.m_invalidIntervals.begin())
            {
              info.m_invalidIntervals.erase(it--);
            } else {
              break;
            }
          } while (it.key() > from);
          if (it.key() == from)
          {
            it.value() = to;
          } else if (it.key() > from) {
            info.m_invalidIntervals.erase(it);
            info.m_invalidIntervals.insert(from, to);
          } else if (it.key() < from) {
            if (it.value() >= from)
            {
              it.value() = to;
            } else {
              info.m_invalidIntervals.insert(from, to);
            }
          }
        }
        continue;
      }
    }

    { // patikrina, ar nesikerta su naudojamais
      auto it = info.m_usefulSubmissions.lower_bound(to);
      if (it != info.m_usefulSubmissions.begin())
      {
        if ((--it).value()->date1() > from)
        {
          submission->setValid(false);
          if (it.value()->date1() > to) to = it.value()->date1();
          do
          {
            it.value()->setValid(false);
            if (it.value() != info.m_usefulSubmissions.begin())
            {
              if (it.key() < from) from = it.key();
              info.m_usefulSubmissions.erase(it--);
            } else {
              break;
            }
          } while (it.value()->date1() > from);
          if (it.value()->date1() > from)
          {
            if (it.key() < from) from = it.key();
            info.m_usefulSubmissions.erase(it--);
          }
          info.m_invalidIntervals.insert(from, to);
          continue;
        }
      }
    }

    { // patikrina, ar yra tikslinantis intervalas
      auto it = info.m_usefulSubmissions.lower_bound(from);
      if (it != info.m_usefulSubmissions.end() && it.value()->date1() < to)
      { // buvo nedidesnis intervalas
        info.m_splitSubmissions.push_back(submission);
        continue;
      } else {
        if (it != info.m_usefulSubmissions.begin()
            && (it == info.m_usefulSubmissions.end() || it.key() != from))
        {
            --it;
        }
        if (it != info.m_usefulSubmissions.end() && it.key() <= from
            && it.value()->date1() >= to)
        { // buvo didesnis intervalas
          info.m_splitSubmissions.push_back(it->value());
          if (it.key() == from)
          {
            it.value() = submission;
            continue;
          } else {
            info.m_usefulSubmissions.erase(it);
          }
        }
      }
    }

    info.m_usefulSubmissions.insert(from, submission);
  }

  for (info.m_usefulSubmissions)
    double usage = (double)submission->count() / from.daysTo(to);
    submission->measure()->m_usageMap.insert(from, usage);
    if (intervalMap.find(to) == intervalMap.end())
    {
      submission->measure()->m_usageMap.insert(to, 0);
    }

  calculateIntervals();
}

/**********************************************************************************************/

void RCalculator :: updateMeasures(RDivisionPtr& division, RMeasureHash& measures)
{
  for (auto measIt = measures.begin(); measIt != measures.end(); measIt++)
  {
    measIt.key()->m_unitUsage.insert(division, measIt.value());
    for (auto sysIt = division->m_systemHash.begin(); sysIt != division->m_systemHash.end(); sysIt++)
    {
      measIt.key()->m_unitUsage[sysIt.key()] += sysIt.value() * measIt.value();
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
    zeroUsages((RUnitPtrList*)m_data->systems());
    zeroUsages((RUnitPtrList*)m_data->divisions());
    QVector<RInterval> intervals;
    for (int i = 0; i < m_numIntervals; i++)
    {
      intervals.push_back(m_intervalFun(i));
    }
    for (auto measure : m_validMeasures)
    {
      measure->m_usage.clear();
      if (measure->m_usageMap.empty())
      {
        measure->m_usage.resize(m_numIntervals);
        continue;
      }
      QDate predictFrom = (--measure->m_usageMap.end()).key();
      if (m_data->interval1().isValid() && m_data->interval1().daysTo(predictFrom) <= 0)
      {
        predictFrom = m_data->interval1().addDays(1);
      }
      measure->m_usage.reserve(m_numIntervals);
      for (int i = 0; i < m_numIntervals; i++)
      {
        double usage;
        if (TO(intervals[i]).daysTo(predictFrom) >= 0)
        { // intervalas istorijoje
          usage = calculateUsage(intervals[i], measure->m_usageMap);
        } else if (FROM(intervals[i]).daysTo(predictFrom) <= 0)
        { // prognozė
          usage = predictUsage(intervals[i], measure->m_usageMap);
        } else { // ir istorija, ir prognozė
          RInterval interval = intervals[i];
          TO(interval) = predictFrom;
          usage = calculateUsage(interval, measure->m_usageMap);
          FROM(interval) = predictFrom;
          TO(interval) = TO(intervals[i]);
          usage += predictUsage(interval, measure->m_usageMap);
        }
        measure->m_usage.push_back(qMakePair(0.0, usage));
      }
      calculateIntervals(measure->m_unitUsage, measure->m_usage);
    }
  }
}

/**********************************************************************************************/

void RCalculator :: zeroUsages(RUnitPtrList* units)
{
  for (auto unit : *units)
  {
    unit->m_usage.clear();
    unit->m_usage.resize(m_numIntervals);
  }
}

/**********************************************************************************************/

void RCalculator :: calculateIntervals(UnitHash& units, UsageVector& usage)
{
  for (auto it = units.begin(); it != units.end(); it++)
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
    if (m_intrapolationEnabled)
    {
      usage = -polynomialIntrapolation(it, usageMap.begin(), usageMap.end(), curDate);
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
    if (m_intrapolationEnabled)
    {
      usage += polynomialIntrapolation(--it, usageMap.begin(), usageMap.end(), TO(interval));
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

double RCalculator :: predictUsage(RInterval interval, UsageMap& usageMap)
{
  if (usageMap.empty()) return 0;
  QDate newestData = (--usageMap.end()).key().addDays(-1);
  if (m_data->interval1().isValid() && m_data->interval1() > newestData)
  {
    newestData = m_data->interval1();
  }
  bool feb29 = FROM(interval).month() == 2 && FROM(interval).month() == 29;
  int distance = 0;
  if (FROM(interval).month() > newestData.month()
      || (FROM(interval).month() == newestData.month()
                        && FROM(interval).day() > newestData.day()
                        && (feb29 == false || IS_LEAP(newestData))))
  {
    distance = -1;
  }
  if (feb29)
  {
    FROM(interval).addDays(-1);
    TO(interval).addDays(-1);
  }
  int yearsToFuture = FROM(interval).year() - (newestData.year() + distance);
  distance = FROM(interval).daysTo(QDate(newestData.year() + distance,
                                         FROM(interval).month(), FROM(interval).day()));
  double usage[3];
  int pastYears; // kelių metų duomenis turime
  for (pastYears = 0; pastYears < 2; pastYears++)
  {
    FROM(interval) = FROM(interval).addDays(distance);
    TO(interval) = TO(interval).addDays(distance);
    if (feb29 && IS_LEAP(FROM(interval)))
    {
      FROM(interval) = FROM(interval).addDays(1);
      TO(interval) = TO(interval).addDays(1);
    }
    if (usageMap.begin().key().daysTo(TO(interval)) <= 0)
      break;
    if (TO(interval).daysTo(newestData) >= -1)
    {
      usage[pastYears] = calculateUsage(interval, usageMap);
    } else {
      RInterval interval0 = interval;
      RInterval interval1 = interval;
      TO(interval0) = newestData.addDays(1);
      FROM(interval1) = TO(interval0);
      usage[pastYears] = calculateUsage(interval0, usageMap) + predictUsage(interval1, usageMap);
    }
    distance = FROM(interval).daysTo(FROM(interval).addYears(-1));
  }
  switch (pastYears)
  {
    case 0:
      return 0;
    case 1:
      return usage[0];
    case 2:
      return std::max(0.0, usage[0] + (usage[0] - usage[1]) * yearsToFuture);
  }
  return -1; // neturėtų įvykti
}

/**********************************************************************************************/

double RCalculator :: polynomialIntrapolation(QDate prevDate, double prevUsage,
                                              QDate startDate, double mainUsage,
                                              QDate endDate, double nextUsage,
                                              QDate nextDate, QDate date)
{
  double coefficients[3]; // antro laipsnio polinomo koeficientai
                          // (koeficientas prie laipsnio i yra indeksu 2 - i)
  if (getPolynom(prevDate.daysTo(startDate), prevDate.daysTo(startDate) * prevUsage,
                 prevDate.daysTo(endDate), startDate.daysTo(endDate) * mainUsage,
                 prevDate.daysTo(nextDate), endDate.daysTo(nextDate) * nextUsage,
                 coefficients)
      && nonNegativeInInterval(coefficients, prevDate.daysTo(startDate),
                               prevDate.daysTo(endDate)))
  {
    return integrate(coefficients, prevDate.daysTo(startDate), prevDate.daysTo(date));
  } else { // jei neišsprendžiame (gali nutikti, pavyzdžiui, jei neturime
   // ankstesnių duomenų) arba galime gauti neigiamas apkrovas, laikome tolygiu
    return startDate.daysTo(date) * mainUsage;
  }
}

/**********************************************************************************************/

bool RCalculator :: getPolynom(int segment1, double segment1Integral,
                               int segment2, double segment2Integral,
                               int segment3, double segment3Integral,
                               double coefficients[3])
{
  double matrix[3][4];
  // (rezultate koeficientas prie laipsnio i yra indeksu 2 - i)
  // susikuriame matricą, kurią išsprendę gausime ieškomos funkcijos koeficientus
  // prevDate laikysime abscisės pradžia

  for (int i = 1; i <= 3; i++)
  {
    matrix[0][3 - i] = pow(segment1, i) / i;
    matrix[1][3 - i] = (pow(segment2, i)
                       - pow(segment1, i)) / i;
    matrix[2][3 - i] = (pow(segment3, i)
                       - pow(segment2, i)) / i;
  }
  // lygybių sprendiniai (norimos atitinkamų integralų reikšmės)
  matrix[0][3] = segment1Integral;
  matrix[1][3] = segment2Integral;
  matrix[2][3] = segment3Integral;
  return solveSystemOfLinearEquations(matrix, coefficients);
}

/**********************************************************************************************/

double RCalculator :: integrate(double coefficients[3], int from, int to)
{
  double answer = 0;
  for (int i = 0; i < 3; i++)
  {
    answer += coefficients[i] / (3 - i) * (pow(to, 3 - i) - pow(from, 3 - i));
  }
  return answer;
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

double RCalculator :: polynomialIntrapolation(UsageMap :: iterator it,
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
  return polynomialIntrapolation(prevDate, prevUsage, startDate, mainUsage,
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

RInterval RCalculator :: findLowUsageInterval(RUnitPtr unit, RInterval interval,
                                             int daysBySeasons[4])
{
  RInterval result;
  int fractionsBySeasons[4]; // kokią dalį reikiamo ilgio sudaro viena diena
  int fractionsNeeded = 1;
  for (int i = 0; i < 4; i++)
  {
    if (daysBySeasons[i] > 0)
    {
      fractionsNeeded *= daysBySeasons[i];
    }
  }
  if (fractionsNeeded <= 0) return result;
  for (int i = 0; i < 4; i++)
  {
    if (daysBySeasons[i] > 0)
    {
      fractionsBySeasons[i] = fractionsNeeded / daysBySeasons[i];
    }
  }

  QHash<RMeasurePtr, double> measures;
  for (auto measure : m_validMeasures)
  {
    double measureUsage = measure->m_unitUsage.value(unit, 0);
    if (measureUsage > 0)
    {
      measures.insert(measure, measureUsage);
    }
  }

  int intervalLength = FROM(interval).daysTo(TO(interval)) + 1;
  QVector<double> usage;
  QVector<int> fraction;
  usage.reserve(intervalLength);
  fraction.reserve(intervalLength);
  QDate day = FROM(interval);
  for (int i = 0; i < intervalLength; i++)
  {
    double curUsage = 0;
    for (auto it = measures.begin(); it != measures.end(); it++)
    {
      curUsage += it.value() * daysUsage(day, it.key()->m_usageMap);
    }
    usage.push_back(curUsage);
    fraction.push_back(fractionsBySeasons[seasonOf(day)]);
    day = day.addDays(1);
  }

  double currentUsage = 0;
  double lowestUsage = MAGIC;
  int currentFractions = 0;
  for (int from = 0, to = 0; to < intervalLength; to++)
  {
    if (fraction[to] == 0) // netinkamas sezonas
    {
      while (to < intervalLength && fraction[to] == 0) to++;
      from = to;
      currentUsage = 0;
      currentFractions = 0;
      if (to >= intervalLength) break;
    }
    currentFractions += fraction[to];
    currentUsage += usage[to];
    while (currentFractions - fraction[from] >= fractionsNeeded)
    { // čia visada from < intervalLength, nes užtikrinam fractionsNeeded > 0
      currentUsage -= usage[from];
      currentFractions -= fraction[from];
      from++;
    }
    if (currentFractions >= fractionsNeeded
        && (FROM(result).isNull() || currentUsage < lowestUsage))
    {
      lowestUsage = currentUsage;
      result = RInterval(FROM(interval).addDays(from), FROM(interval).addDays(to));
    }
  }
  return result;
}

/**********************************************************************************************/

int RCalculator :: seasonOf(QDate date)
{
  return date.month() % 12 / 3; // elegantiška, ar ne? :D
}

/**********************************************************************************************/

double RCalculator :: daysUsage(QDate day, UsageMap& usageMap)
{
  RInterval interval = RInterval(day, day.addDays(1));
  if (day <= m_data->interval1())
  {
    return calculateUsage(interval, usageMap);
  } else {
    return predictUsage(interval, usageMap);
  }
}

/**********************************************************************************************/

 void RCalculator :: setIntrapolationEnabled(bool enabled)
 {
   m_intrapolationEnabled = enabled;
 }
