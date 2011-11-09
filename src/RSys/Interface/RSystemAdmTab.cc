#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RSystemAdmTab.hh>

/********************************************* RS *********************************************/
/*                                       RSystemAdmTab                                        */
/**********************************************************************************************/

Vacuum RSystemAdmTab :: RSystemAdmTab(RMainWindow* parent):
  RTab("AAA", parent)
{
  makeTable2DTab(parent->systemContainer(), parent->divisionContainer());
}

/**********************************************************************************************/

Vacuum RSystemAdmTab :: ~RSystemAdmTab()
{
}

/**********************************************************************************************/
