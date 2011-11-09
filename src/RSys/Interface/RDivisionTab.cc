#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RDivisionTab.hh>

/********************************************* RS *********************************************/
/*                                        RDivisionTab                                        */
/**********************************************************************************************/

Vacuum RDivisionTab :: RDivisionTab(RMainWindow* parent):
  RTab("AAA", parent)
{
  makeTable1DTab(parent->divisionContainer());
}

/**********************************************************************************************/

Vacuum RDivisionTab :: ~RDivisionTab()
{
}

/**********************************************************************************************/
