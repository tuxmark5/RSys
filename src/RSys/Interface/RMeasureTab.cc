#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RMeasureTab.hh>

/********************************************* RS *********************************************/
/*                                        RMeasureTab                                         */
/**********************************************************************************************/

Vacuum RMeasureTab :: RMeasureTab(RMainWindow* parent):
  RTab("AAA", parent)
{
  makeTable1DTab(parent->measureContainer());
}

/**********************************************************************************************/

Vacuum RMeasureTab :: ~RMeasureTab()
{
}

/**********************************************************************************************/
