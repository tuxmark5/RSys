#include <RSys/Core/RData.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RMeasureAdmTab.hh>
#include <RSys/Interface/RModel2D.hh>

/********************************************* RS *********************************************/
/*                                       RMeasureAdmTab                                       */
/**********************************************************************************************/

Vacuum RMeasureAdmTab :: RMeasureAdmTab(RMainWindow* parent):
  RTab(R_S("Paramos priemonių administravimas"), parent)
{
  RData*    data1   = parent->data();
  RModel2D* model   = makeTable2DTab(parent->measureContainer(), parent->divisionContainer());

  auto dmGetter = [=](int x, int y) -> QVariant
  {
    RDivision*  division  = data1->divisions()->at(y).get();
    RMeasure*   measure   = data1->measures()->at(x).get();
    double      value     = division->measure(measure);

    return value == 0.0 ? QVariant() : value;
  };

  auto dmSetter = [=](int x, int y, const QVariant& var) -> void
  {
    RDivision*  division  = data1->divisions()->at(y).get();
    RMeasure*   measure   = data1->measures()->at(x).get();

    division->setMeasure(measure, var.toDouble());
  };

  model->setGetter(dmGetter);
  model->setSetter(dmSetter);
}

/**********************************************************************************************/

Vacuum RMeasureAdmTab :: ~RMeasureAdmTab()
{
}

/**********************************************************************************************/
