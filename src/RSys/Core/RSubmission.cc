#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>

/********************************************* RS *********************************************/
/*                                        RSubmission                                         */
/**********************************************************************************************/

Vacuum RSubmission :: RSubmission(RData* data):
  RElement(data)
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
  m_measure     = measure;
  m_measureName = measure ? measure->identifier() : QString();
}

/**********************************************************************************************/

void RSubmission :: setMeasureName(const QString& measureName)
{
  m_measureName = measureName;
  // TODO: lookup measure
}

/**********************************************************************************************/
