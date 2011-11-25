#include <RSys/Core/RData.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RSystemAdmTab.hh>
#include <RSys/Interface/RModel2D.hh>

/********************************************* RS *********************************************/
/*                                       RSystemAdmTab                                        */
/**********************************************************************************************/

Vacuum RSystemAdmTab :: RSystemAdmTab(RMainWindow* parent):
  RTab(R_S("Informacinių sistemų paskirstymas padaliniuose"), parent)
{
  RData*    data1   = parent->data();
  RModel2D* model   = makeTable2DTab(parent->systemContainer(), parent->divisionContainer());

  auto dsGetter = [=](int x, int y) -> QVariant
  {
    RDivision*  division  = data1->divisions()->at(y).get();
    RSystem*    system    = data1->systems()->at(x).get();
    int         value     = division->system(system);

    return value == 1 ? 1 : QVariant();
  };

  auto dsSetter = [=](int x, int y, const QVariant& var) -> void
  {
    RDivision*  division  = data1->divisions()->at(y).get();
    RSystem*    system    = data1->systems()->at(x).get();

    division->setSystem(system, var.toInt());
  };

  model->setGetter(dsGetter);
  model->setSetter(dsSetter);
}

/**********************************************************************************************/

Vacuum RSystemAdmTab :: ~RSystemAdmTab()
{
}

/**********************************************************************************************/
