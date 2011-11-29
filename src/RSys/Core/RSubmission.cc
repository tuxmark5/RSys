#include <RSys/Core/RData.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>

/********************************************* RS *********************************************/
/*                                        RSubmission                                         */
/**********************************************************************************************/

Vacuum RSubmission :: RSubmission(RData* data):
  RElement(data),
  m_measure(0),
  m_count(0)
{
}

/**********************************************************************************************/

Vacuum RSubmission :: RSubmission(RSubmission& other, RData* data):
  RElement(other, data),
  m_measure(other.m_measure ? other.m_measure->buddy() : 0),
  m_measureName(other.m_measureName),
  m_date0(other.m_date0),
  m_date1(other.m_date1),
  m_count(other.m_count)
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

void RSubmission :: setCount(int count)
{
  (*m_data)[countChange](this, count);
  m_count = count;
}

/**********************************************************************************************/

void RSubmission :: setDate0(const QDate& date0)
{
  (*m_data)[date0Change](this, date0);
  m_date0 = date0;
}

/**********************************************************************************************/

void RSubmission :: setDate1(const QDate& date1)
{
  (*m_data)[date1Change](this, date1);
  m_date1 = date1;
}

/**********************************************************************************************/

void RSubmission :: setMeasure(RMeasure* measure)
{
  (*m_data)[measureChange](this, measure);
  m_measure       = measure;
  m_measureName   = measure ? measure->identifier() : QString();
}

/**********************************************************************************************/

void RSubmission :: setMeasureId(RID id)
{
  if (RMeasure* measure = m_data->measure(id))
    setMeasure(measure);
}

/**********************************************************************************************/

void RSubmission :: setMeasureName(const QString& measureName)
{
  RMeasurePtr measure1;

  m_measureName   = measureName.toUpper();
  measure1        = m_data->measure(m_measureName);
  (*m_data)[measureChange](this, measure1.get());
  m_measure       = measure1;
}

/**********************************************************************************************/

void RSubmission :: setMeasure1Name(const QString& measureName)
{
  RMeasurePtr measure1;

  m_measureName   = measureName.toUpper();
  measure1        = m_data->measure(m_measureName);

  if (!measure1 && !m_measureName.isEmpty())
  {
    measure1 = new RMeasure(m_data);
    measure1->release();
    measure1->setIdentifier(m_measureName);
    m_data->measures1()->append(measure1);
  }

  (*m_data)[measureChange](this, measure1.get());
  m_measure       = measure1;
}

/**********************************************************************************************/

void RPhantomMeasureDeleter :: f(RMeasure* measure)
{
  measure->data()->measures1()->removeOne(measure);
  delete measure;
}

/**********************************************************************************************/
