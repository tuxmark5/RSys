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

void RSubmission :: setCount(int count)
{
  m_count = count;
}

/**********************************************************************************************/

void RSubmission :: setDate0(const QDate& date0)
{
  m_date0 = date0;
}

/**********************************************************************************************/

void RSubmission :: setDate1(const QDate& date1)
{
  m_date1 = date1;
}

/**********************************************************************************************/

void RSubmission :: setMeasure(RMeasure* measure)
{
  m_measure       = measure;
  m_measureName   = measure ? measure->identifier() : QString();
}

/**********************************************************************************************/

void RSubmission :: setMeasureName(const QString& measureName)
{
  m_measureName   = measureName.toUpper();
  m_measure       = m_data->measure(m_measureName);
}

/**********************************************************************************************/

void RSubmission :: setMeasure1Name(const QString& measureName)
{
  m_measureName   = measureName.toUpper();
  m_measure       = m_data->measure(m_measureName);

  if (!m_measure && !m_measureName.isEmpty())
  {
    m_measure = new RMeasure(m_data);
    m_measure->release();
    m_measure->setIdentifier(m_measureName);
    m_data->measures1()->append(m_measure);
  }
}

/**********************************************************************************************/

void RPhantomMeasureDeleter :: f(RMeasure* measure)
{
  measure->data()->measures1()->removeOne(measure);
  delete measure;
}

/**********************************************************************************************/
