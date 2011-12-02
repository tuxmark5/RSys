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
  m_numRecords(0),
  m_updatesEnabled(true)
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
  for (auto it = m_models.begin(); it != m_models.end(); ++it)
    (*it)->m_results = 0;
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
      if (RUnit* buddy = unit->buddy())
        return buddy->usageAt(x);
      return 0.0;
    };

    case Usage1: return [this, unit](int x) -> QVariant
    {
      return unit->usageAt(x);
    };

    case Usage1Tooltip: return [this, unit](int x) -> QVariant
    {
      return R_S("Intervalas: %1.\nApkrova: %2").
        arg(intervalStr(x)).arg(unit->usageAt(x));
    };

    case DeltaUsage: return [this, unit](int x) -> QVariant
    {
      return fieldDeltaUsage(unit, x);
    };

    case DeltaUsageTooltip: return [this, unit](int x) -> QVariant
    {
      return R_S("Intervalas: %1.\nSkirtumas: %2").
        arg(intervalStr(x)).arg(fieldDeltaUsage(unit, x));
    };

    case DeltaPUsage: return [this, unit](int x) -> QVariant
    {
      if (RUnit* buddy = unit->buddy())
      {
        double usage0 = buddy->usageAt(x);
        double usage1 = unit->usageAt(x);
        return (usage1 - usage0) / usage1 * 100.0; // usage0?
      }
      return QVariant();
    };

    case Identifier: return [=](int) -> QVariant
    {
      return unit->identifier();
    };

    case FullName: return [=](int) -> QVariant
    {
      return unit->fullName();
    };
  }

  return Getter();
}

/**********************************************************************************************/

double RResults :: fieldDeltaUsage(RUnit* unit, int x)
{
  if (RUnit* buddy = unit->buddy())
    return unit->usageAt(x) - buddy->usageAt(x);
  return round(unit->usageAt(x) * 100.0) / 100.0;
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

  return RInterval(QDate(2011, 02, 01), QDate(2011, 03, 01));
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

QString RResults :: intervalStr(int x)
{
  RInterval interval = m_intervalFun(x);
  return QString("nuo %1 iki %2")
   .arg(std::get<0>(interval).toString(Qt::DefaultLocaleShortDate))
   .arg(std::get<1>(interval).addDays(-1).toString(Qt::DefaultLocaleShortDate));
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

void RResults :: resetBegin()
{
  for (auto it = m_models.begin(); it != m_models.end(); ++it)
    emit (*it)->beginResetModel();
}

/**********************************************************************************************/

void RResults :: resetEnd()
{
  for (auto it = m_models.begin(); it != m_models.end(); ++it)
    emit (*it)->endResetModel();
}

/**********************************************************************************************/

void RResults :: setInterval(QDate date0, QDate date1)
{
  m_interval0     = date0;
  m_interval1     = date1;
}

/**********************************************************************************************/

void RResults :: setInterval(RIntervalFun fun, int num)
{
  m_intervalFun   = std::move(fun);
  m_numRecords    = num;

  m_calculator0->update();
  m_calculator0->setIntervalFun(m_intervalFun, m_numRecords);
  m_calculator1->update();
  m_calculator1->setIntervalFun(m_intervalFun, m_numRecords);

  for (auto it = m_models.begin(); it != m_models.end(); ++it)
    emit (*it)->reset();
}

/**********************************************************************************************/

void RResults :: setUpdatesEnabled(bool enabled)
{
  m_updatesEnabled = enabled;
}

/**********************************************************************************************/

void RResults :: unregisterField(RUnit* unit, RResultsModel* model, int key)
{
  m_fields.remove(unit, Field(model, key));
}

/**********************************************************************************************/

void RResults :: update()
{
  m_calculator1->update();
  m_calculator1->setIntervalFun(m_intervalFun, m_numRecords);

  for (auto it = m_models.begin(); it != m_models.end(); ++it)
    emit (*it)->reset();
}

/**********************************************************************************************/

void RResults :: updateDelayed()
{
  R_GUARD(m_updatesEnabled, Vacuum);

  QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
}

/**********************************************************************************************/
