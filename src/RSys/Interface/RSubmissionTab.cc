#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RSubmissionTab.hh>

/********************************************* RS *********************************************/
/*                                       RSubmissionTab                                       */
/**********************************************************************************************/

Vacuum RSubmissionTab :: RSubmissionTab(RMainWindow* parent):
  RTab("AAA", parent)
{
  makeTable1DTab(parent->submissionContainer());
}

/**********************************************************************************************/

Vacuum RSubmissionTab :: ~RSubmissionTab()
{
}

/**********************************************************************************************/
