#include <RSys/Core/RData.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>

/********************************************* RS *********************************************/
/*                                        RSubmission                                         */
/**********************************************************************************************/

Vacuum RSubmission :: RSubmission(RData* data, bool planned):
  RElement(data),
  m_measure(0),
  m_count(0),
  m_planned(planned)
{
  m_valid = false;
}

/**********************************************************************************************/

Vacuum RSubmission :: RSubmission(RSubmission& other, RData* data):
  RElement(other, data),
  m_measure(other.m_measure ? other.m_measure->buddy() : 0),
  m_measureName(other.m_measureName),
  m_date0(other.m_date0),
  m_date1(other.m_date1),
  m_count(other.m_count),
  m_planned(other.m_planned)
{
}

/**********************************************************************************************/

Vacuum RSubmission :: ~RSubmission()
{
}

/**********************************************************************************************/

QString RSubmission :: measureFullName() const
{
  if (m_measure)
    return m_measure->fullName();
  return R_S("(Nežinoma paramos priemonė)");
}

/**********************************************************************************************/

RID RSubmission :: measureId() const
{
  R_GUARD(m_measure, 0);
  return m_measure->id();
}

/**********************************************************************************************/

void RSubmission :: remove()
{
  (*m_data)[submissionRemoval](this);
  m_data->modify();

  if (m_planned && m_measure && m_measure->numRefs() == 2)
  {
    m_data->measures1()->removeOne(m_measure);
    m_measure = 0;
  }

  m_valid = false;
}

/**********************************************************************************************/

bool RSubmission :: setCount(int count)
{
  R_DATA_GUARD(count >= 0, false, "Kiekis negali būti neigiamas skaičius.");

  (*m_data)[countChange](this, count);
  m_count = count;

  m_data->modify();
  return true;
}

/**********************************************************************************************/

bool RSubmission :: setDate0(const QDate& date0)
{
  R_DATA_GUARD(date0.isValid(), false, "Neteisinga data.");
  R_DATA_GUARD(m_date1.isValid() ? (date0 < m_date1) : true, false,
               "Klaidingas kairysis intervalo galas.");
  R_DATA_GUARD(isPlanned() ? date0 > m_data->interval1() : true, false,
               "Planuojamos paraiškos intervalas kertasi su istoriniais duomenimis.<br>"
               "Intervalas gali prasidėti nuo: <b>%1</b>",
               .arg(R_DATE_TO_S(m_data->interval1().addDays(1))));

  QDate oldDate0  = m_date0;
  m_date0         = date0;
  validate();
  (*m_data)[date0Changed](this, oldDate0);
  m_data->modify();

  return true;
}

/**********************************************************************************************/

bool RSubmission :: setDate0E(const QDate& date0)
{
  R_GUARD(setDate0(date0),  false);
  R_GUARD(m_date1.isNull(), true);

  setDate1(m_date0.addMonths(1).addDays(-1));
  return true;
}

/**********************************************************************************************/

bool RSubmission :: setDate1(const QDate& date1)
{
  R_DATA_GUARD(date1.isValid(), false, "Neteisinga data.");
  R_DATA_GUARD(m_date0.isValid() ? (m_date0 < date1) : true, false,
               "Klaidingas dešinysis intervalo galas.");

  QDate oldDate1  = m_date1;
  m_date1         = date1;
  validate();
  (*m_data)[date1Changed](this, oldDate1);

  m_data->modify();
  return true;
}

/**********************************************************************************************/

void RSubmission :: setDefaultInteval()
{
  R_GUARD(m_measure, Vacuum);
  R_GUARD(m_date0.isNull() || m_date1.isNull(), Vacuum);

  RInterval lastInterval  = m_measure->lastInterval();
  QDate     date0         = std::get<0>(lastInterval);
  QDate     date1         = std::get<1>(lastInterval);
  QDate     newDate0;
  QDate     newDate1;

  if (date0.isValid() && date1.isValid())
  {
    int length = date0.daysTo(date1);

    switch (length)
    {
      case 29:
      case 30:
      case 31:
        newDate0 = date0.addMonths(1);
        newDate1 = newDate0.addMonths(1).addDays(-1);
        break;

      default:
        newDate0 = date1.addDays(1);
        newDate1 = newDate0.addDays(length);
        break;
    }
  }
  else
  {
    newDate0 = m_data->interval1().addDays(1);
    newDate1 = newDate0.addMonths(1).addDays(-1);
  }

  if (m_date0.isNull()) setDate0(newDate0);
  if (m_date1.isNull()) setDate1(newDate1);
}

/**********************************************************************************************/

void RSubmission :: setMeasure(RMeasure* measure)
{
  (*m_data)[measureChange](this, measure);
  m_measure       = measure;
  m_measureName   = measure ? measure->identifier() : QString();
  m_data->modify();
  validate();
}

/**********************************************************************************************/

void RSubmission :: setMeasureId(RID id)
{
  if (RMeasure* measure = m_data->measure(id))
    setMeasure(measure);
}

/**********************************************************************************************/

bool RSubmission :: setMeasureName(const QString& measureName)
{
  QString       measureName1  = measureName.trimmed().toUpper();
  RMeasurePtr   measure1      = m_data->measure(measureName1);
  R_DATA_GUARD(measure1, false, "Nežinoma paramos priemonė <b>%1</b>", .arg(measureName1));

  m_measureName   = measureName1;
  (*m_data)[measureChange](this, measure1.get());
  m_measure       = measure1;
  validate();

  m_data->modify();
  setDefaultInteval();

  return true;
}

/**********************************************************************************************/

void RSubmission :: setMeasure1NameE(const QString& measureName)
{
  RMeasurePtr measure1;

  m_measureName   = measureName.toUpper();
  measure1        = m_data->measure(m_measureName);

  if (!measure1 && !m_measureName.isEmpty())
  {
    measure1 = new RMeasure(m_data, true);
    measure1->setIdentifier(m_measureName);
    m_data->measures1()->append(measure1);
  }

  (*m_data)[measureChange](this, measure1.get());
  m_measure       = measure1;
  validate();
  setDefaultInteval();
}

/**********************************************************************************************/

void RSubmission :: validate()
{
  bool valid = true;

  valid &= m_date0.isValid();
  valid &= m_date1.isValid();
  valid &= bool(m_measure);

  setValid(valid);
}

/**********************************************************************************************/

void RPhantomMeasureDeleter :: f(RMeasure* measure)
{
  measure->data()->measures1()->removeOne(measure);
  delete measure;
}

/**********************************************************************************************/
