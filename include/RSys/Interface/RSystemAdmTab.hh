#ifndef RSYS_INTERFACE_RSYSTEM_ADM_TAB_HH
#define RSYS_INTERFACE_RSYSTEM_ADM_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                       RSystemAdmTab                                        */
/**********************************************************************************************/

class RSystemAdmTab: public RTab
{
  Q_OBJECT

  public:
    _M Vacuum         RSystemAdmTab(RMainWindow* parent = 0);
    _V Vacuum         ~RSystemAdmTab();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSYSTEM_ADM_TAB_HH */
