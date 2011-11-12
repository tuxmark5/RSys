#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RSubmissionTab.hh>

/********************************************* RS *********************************************/
/*                                       RSubmissionTab                                       */
/**********************************************************************************************/

Vacuum RSubmissionTab :: RSubmissionTab(RMainWindow* parent):
  RTab(R_S("Istoriniai paramos priemonių paraiškų duomenys"), parent)
{
  makeTable1DTab(parent->submissionContainer());
}

/**********************************************************************************************/

Vacuum RSubmissionTab :: ~RSubmissionTab()
{
}

/**********************************************************************************************/
