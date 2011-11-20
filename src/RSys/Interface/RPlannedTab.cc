#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RModel2D.hh>
#include <RSys/Interface/RPlannedTab.hh>

/********************************************* RS *********************************************/
/*                                        RPlannedTab                                         */
/**********************************************************************************************/

Vacuum RPlannedTab :: RPlannedTab(RMainWindow* parent):
  RTab(R_S("Planuojami paramos priemonių kiekiai"), parent)
{
  RData*    data = parent->data();
  RModel2D* model;

  auto getter = [=](int x, int y) -> QVariant
  {
    RDivision*  division  = data->divisions()->at(y).get();
    RMeasure*   measure   = data->measures1()->at(x);
    double      value     = division->measure1(measure);

    return value == 0.0 ? QVariant() : value;
  };

  auto setter = [=](int x, int y, const QVariant& var) -> void
  {
    RDivision*  division  = data->divisions()->at(y).get();
    RMeasure*   measure   = data->measures1()->at(x);

    division->setMeasure1(measure, var.toDouble());
  };

  /*****/ makeTable1DTab(parent->submission1Container());
  model = makeTable2DTab(parent->measure1Container(), parent->divisionContainer());

  model->setGetter(getter);
  model->setSetter(setter);
}

/**********************************************************************************************/

Vacuum RPlannedTab :: ~RPlannedTab()
{
}

/**********************************************************************************************/
