#include <RSys/Core/RUnit.hh>
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
auto RResults :: field(ResultType type, RUnit* unit) -> Getter
{
  switch (type)
  {
    case Usage0: return [](int x) -> QVariant
    {
      return 2.0 * x + sin(x);
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

void RResults :: registerField(RUnit* unit, RResultsModel* model, int key)
{
  m_fields.insertMulti(unit, Field(model, key));
}

/**********************************************************************************************/

void RResults :: unregisterField(RUnit* unit, RResultsModel* model, int key)
{
  m_fields.remove(unit, Field(model, key));
}

/**********************************************************************************************/
