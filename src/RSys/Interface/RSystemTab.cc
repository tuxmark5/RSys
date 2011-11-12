#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RSystemTab.hh>

/********************************************* RS *********************************************/
/*                                         RSystemTab                                         */
/**********************************************************************************************/

Vacuum RSystemTab :: RSystemTab(RMainWindow* parent):
  RTab(R_S("Informacinės sistemos"), parent)
{
  makeTable1DTab(parent->systemContainer());
}

/**********************************************************************************************/

Vacuum RSystemTab :: ~RSystemTab()
{
}

/**********************************************************************************************/
