#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RMeasureAdmTab.hh>

/********************************************* RS *********************************************/
/*                                       RMeasureAdmTab                                       */
/**********************************************************************************************/

Vacuum RMeasureAdmTab :: RMeasureAdmTab(RMainWindow* parent):
  RTab("AAA", parent)
{
  makeTable2DTab(parent->measureContainer(), parent->divisionContainer());
}

/**********************************************************************************************/

Vacuum RMeasureAdmTab :: ~RMeasureAdmTab()
{
}

/**********************************************************************************************/
