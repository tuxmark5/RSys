#ifndef RSYS_INTERFACE_RSUBMISSION_TAB_HH
#define RSYS_INTERFACE_RSUBMISSION_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                       RSubmissionTab                                       */
/**********************************************************************************************/

class RSubmissionTab: public RTab
{
  Q_OBJECT

  public:
    _M Vacuum         RSubmissionTab(RMainWindow* parent = 0);
    _V Vacuum         ~RSubmissionTab();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSUBMISSION_TAB_HH */
