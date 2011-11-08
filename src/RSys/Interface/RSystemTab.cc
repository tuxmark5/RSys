#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RSystemTab.hh>

/********************************************* RS *********************************************/
/*                                         RSystemTab                                         */
/**********************************************************************************************/

Vacuum RSystemTab :: RSystemTab(RMainWindow* parent):
  RTab("AAA", parent)
{
  makeTable1DTab(parent->systemContainer());
}

/**********************************************************************************************/

Vacuum RSystemTab :: ~RSystemTab()
{
}

/**********************************************************************************************/
