#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RDivisionTab.hh>

/********************************************* RS *********************************************/
/*                                        RDivisionTab                                        */
/**********************************************************************************************/

Vacuum RDivisionTab :: RDivisionTab(RMainWindow* parent):
  RTab(R_S("Padaliniai"), parent)
{
  makeTable1DTab(parent->divisionContainer());
}

/**********************************************************************************************/

Vacuum RDivisionTab :: ~RDivisionTab()
{
}

/**********************************************************************************************/
