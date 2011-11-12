#include <RSys/Interface/RResultsModel.hh>
#include <RSys/Logic/RResults.hh>

/********************************************* RS *********************************************/
/*                                          RResults                                          */
/**********************************************************************************************/

Vacuum RResults :: RResults(RData* data):
  m_data(data)
{
}

/**********************************************************************************************/

Vacuum RResults :: ~RResults()
{
}

/**********************************************************************************************/
#include <math.h>
void RResults :: addUsage0Field(RResultsModel* model, RUnit* unit)
{
  int id = model->addField([](int x) -> QVariant
  {
    return "Ind";
  });

  model->addGetter(id, Qt::DisplayRole, [](int x) -> QVariant
  {
    return 2.0 * x + sin(x);
  });
}

/**********************************************************************************************/

void RResults :: addUsage1Field(RResultsModel* model, RUnit* unit)
{
  int id = model->addField([](int x) -> QVariant
  {
    return "Ind2";
  });

  model->addGetter(id, Qt::DisplayRole, [](int x) -> QVariant
  {
    return 40.0 - (2.0 * x + sin(x));
  });
}

/**********************************************************************************************/

void RResults :: addDeltaUsageField(RResultsModel* model, RUnit* unit)
{

}

/**********************************************************************************************/

void RResults :: addDeltaPUsageField(RResultsModel* model, RUnit* unit)
{

}

/**********************************************************************************************/
