#include <QtGui/QColor>
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
  m_highlightedInterval(-1),
  m_updatesEnabled(true),
  m_updatePending(false)
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

auto RResults :: field(int type, RUnit* unit) -> Getter
{
  switch (type)
  {
    case Background: return [this](int x) -> QVariant
    {
      if (std::get<0>(interval(x)).month() == m_highlightedInterval)
        return QColor(0x00, 0x00, 0x80, 0x40);
      return QVariant();
    };

    case Date: return [this](int x) -> QVariant
    {
      return std::get<0>(this->m_intervalFun(x));
    };

    case Identifier: return [=](int) -> QVariant
    {
      return unit->identifier();
    };

    case FullName: return [=](int) -> QVariant
    {
      return unit->fullName();
    };

    case Usage0 | Hours: return [this, unit](int x) -> QVariant
    {
      if (RUnit* buddy = unit->buddy())
        return buddy->usageAt(x).first;
      return 5.0;
    };

    case Usage0 | Counts: return [this, unit](int x) -> QVariant
    {
      if (RUnit* buddy = unit->buddy())
        return buddy->usageAt(x).second;
      return 0.0;
    };

    case Usage1 | Hours: return [this, unit](int x) -> QVariant
    {
      return unit->usageAt(x).first;
    };

    case Usage1 | Counts: return [this, unit](int x) -> QVariant
    {
      return unit->usageAt(x).second;
    };

    case Usage1 | Hours  | Tooltip:
    case Usage1 | Counts | Tooltip: return [this, unit](int x) -> QVariant
    {
      const RUsage& usage = unit->usageAt(x);
      return R_S("Intervalas: %1.\nApkrova: %2\nSkaičius: %3").
        arg(intervalStr(x)).arg(usage.first).arg(usage.second);
    };

    case UsageD | Hours: return [this, unit](int x) -> QVariant
    {
      return fieldDeltaUsage(unit, x);
    };

    case UsageD | Counts: return [this, unit](int x) -> QVariant
    {
      return fieldDeltaUsageCount(unit, x);
    };

    case UsageD | Counts | Tooltip: break;
    case UsageD | Hours  | Tooltip: return [this, unit](int x) -> QVariant
    {
      return R_S("Intervalas: %1.\nSkirtumas: %2").
        arg(intervalStr(x)).arg(fieldDeltaUsage(unit, x));
    };

    case UsageDP | Hours: return [this, unit](int x) -> QVariant
    {
      if (RUnit* buddy = unit->buddy())
      {
        double usage0 = buddy->usageAt(x).first;
        double usage1 = unit->usageAt(x).first;
        return (usage1 - usage0) / usage1 * 100.0; // usage0?
      }
      return QVariant();
    };

    case UsageDP | Counts | Tooltip: break;
    case UsageDP | Hours  | Tooltip: break;

    default:
    {
      qDebug() << "WARNING: unknown field type" << QString::number(type, 16);
    }
  }

  return Getter();
}

/**********************************************************************************************/

double RResults :: fieldDeltaUsage(RUnit* unit, int x)
{
  if (RUnit* buddy = unit->buddy())
    return unit->usageAt(x).first - buddy->usageAt(x).first;
  return unit->usageAt(x).first;
}

/**********************************************************************************************/

double RResults :: fieldDeltaUsageCount(RUnit* unit, int x)
{
  if (RUnit* buddy = unit->buddy())
    return unit->usageAt(x).second - buddy->usageAt(x).second;
  return unit->usageAt(x).second;
}

/**********************************************************************************************/

RInterval RResults :: findLowUsageInterval(RUnit* unit)
{
  return m_calculator1->findLowUsageInterval(unit, RInterval(m_interval0, m_interval1), m_seasonalLengths);
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

void RResults :: resetData()
{
  for (auto it = m_models.begin(); it != m_models.end(); ++it)
    emit (*it)->updateAllData();
}

/**********************************************************************************************/

void RResults :: resetEnd()
{
  for (auto it = m_models.begin(); it != m_models.end(); ++it)
    emit (*it)->endResetModel();
}

/**********************************************************************************************/

void RResults :: setHighlightedInterval(int x)
{
  R_GUARD(x != m_highlightedInterval, Vacuum);

  m_highlightedInterval = std::get<0>(interval(x)).month();
  resetData();
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

  resetBegin();
  m_calculator0->update();
  m_calculator0->setIntervalFun(m_intervalFun, m_numRecords);
  m_calculator1->update();
  m_calculator1->setIntervalFun(m_intervalFun, m_numRecords);
  resetEnd();
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
  resetData();

  m_updatePending = false;
}

/**********************************************************************************************/

void RResults :: updateDelayed()
{
  R_GUARD(m_updatesEnabled && !m_updatePending, Vacuum);

  m_updatePending = true;
  QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
}

/**********************************************************************************************/
