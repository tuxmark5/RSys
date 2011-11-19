#include <RSys/Core/RUnit.hh>
#include <RSys/Interface/RResultsModel.hh>
#include <RSys/Logic/RCalculator.hh>
#include <RSys/Logic/RResults.hh>
#include <math.h>

/********************************************* RS *********************************************/
/*                                          RResults                                          */
/**********************************************************************************************/

Vacuum RResults :: RResults(RData* data0, RData* data1, QObject* parent):
  QObject(parent),
  m_data0(data0),
  m_data1(data1),
  m_numRecords(0)
{
  m_calculator0 = new RCalculator(m_data0);
  m_calculator1 = new RCalculator(m_data1);

  m_seasonalLengths[0] = 0;
  m_seasonalLengths[1] = 0;
  m_seasonalLengths[2] = 0;
  m_seasonalLengths[3] = 0;
}

/**********************************************************************************************/

Vacuum RResults :: ~RResults()
{
  delete m_calculator0;
  delete m_calculator1;
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

    case Usage0: return [this, unit](int x) -> QVariant
    {
      return (this->m_interval0.year() - 1995) + 2.0 * x + sin(x);
    };

    case Usage1: return [this, unit](int x) -> QVariant
    {
      return x < unit->usage().size() ? unit->usage().at(x) : 0.0;
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

void RResults :: reset()
{
}

/**********************************************************************************************/
#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
void RResults :: setInterval(QDate date0, QDate date1)
{
  m_interval0     = date0;
  m_interval1     = date1;
  m_intervalFun   = intervalFun();
  m_numRecords    = date0.daysTo(date1) / 30; // temporary HACK

  for (auto it = m_models.begin(); it != m_models.end(); ++it)
    emit (*it)->reset();

  m_calculator1->update();
  m_calculator1->setIntervalFun(m_intervalFun, m_numRecords);

  /*auto d = m_data1->divisions();
  for (auto it = d->begin(); it != d->end(); ++it)
  {
    qDebug() << (*it)->identifier() << "X" << (*it)->usage().size();

    auto usage = (*it)->usage();

    for (auto it1 = usage.begin(); it1 != usage.end(); ++it1)
      qDebug() << *it1;
  }*/
}

/**********************************************************************************************/

void RResults :: unregisterField(RUnit* unit, RResultsModel* model, int key)
{
  m_fields.remove(unit, Field(model, key));
}

/**********************************************************************************************/
