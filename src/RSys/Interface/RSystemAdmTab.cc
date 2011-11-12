#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RSystemAdmTab.hh>
#include <RSys/Interface/RModel2D.hh>

/********************************************* RS *********************************************/
/*                                       RSystemAdmTab                                        */
/**********************************************************************************************/

Vacuum RSystemAdmTab :: RSystemAdmTab(Getter2&& getter, Setter2&& setter, RMainWindow* parent):
  RTab(R_S("Informacinių sistemų paskirstymas padaliniuose"), parent)
{
  RModel2D* model = makeTable2DTab(parent->systemContainer(), parent->divisionContainer());

  model->setGetter(std::forward<Getter2>(getter));
  model->setSetter(std::forward<Setter2>(setter));
}

/**********************************************************************************************/

Vacuum RSystemAdmTab :: ~RSystemAdmTab()
{
}

/**********************************************************************************************/
