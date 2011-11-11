#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RMeasureAdmTab.hh>
#include <RSys/Interface/RModel2D.hh>

/********************************************* RS *********************************************/
/*                                       RMeasureAdmTab                                       */
/**********************************************************************************************/

Vacuum RMeasureAdmTab :: RMeasureAdmTab(Getter2&& getter, Setter2&& setter, RMainWindow* parent):
  RTab("AAA", parent)
{
  RModel2D* model = makeTable2DTab(parent->measureContainer(), parent->divisionContainer());

  model->setGetter(std::forward<Getter2>(getter));
  model->setSetter(std::forward<Setter2>(setter));
}

/**********************************************************************************************/

Vacuum RMeasureAdmTab :: ~RMeasureAdmTab()
{
}

/**********************************************************************************************/
