#ifndef RSYS_INTERFACE_RPLANNED_TAB_HH
#define RSYS_INTERFACE_RPLANNED_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                        RPlannedTab                                         */
/**********************************************************************************************/

class RPlannedTab: public RTab
{
  Q_OBJECT

  public:
    _M Vacuum         RPlannedTab(RMainWindow* parent = 0);
    _V Vacuum         ~RPlannedTab();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RPLANNED_TAB_HH */
