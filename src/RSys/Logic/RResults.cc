#include <RSys/Core/RUnit.hh>
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
