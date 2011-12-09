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
  }
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

  QDate oldDate0  = m_date0;
  m_date0         = date0;
  (*m_data)[date0Changed](this, oldDate0);
  m_data->modify();

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
  (*m_data)[date1Changed](this, oldDate1);

  m_data->modify();
  return true;
}

/**********************************************************************************************/

void RSubmission :: setMeasure(RMeasure* measure)
{
  (*m_data)[measureChange](this, measure);
  m_measure       = measure;
  m_measureName   = measure ? measure->identifier() : QString();
  m_null          = bool(measure);
  m_data->modify();
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
  m_null          = false;

  m_data->modify();
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
    measure1 = new RMeasure(m_data);
    measure1->setIdentifier(m_measureName);
    m_data->measures1()->append(measure1);
  }

  (*m_data)[measureChange](this, measure1.get());
  m_measure       = measure1;
  m_null          = false;
}

/**********************************************************************************************/

void RPhantomMeasureDeleter :: f(RMeasure* measure)
{
  measure->data()->measures1()->removeOne(measure);
  delete measure;
}

/**********************************************************************************************/
