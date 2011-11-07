#ifndef RSYS_INTERFACE_RSYSTEM_TAB_HH
#define RSYS_INTERFACE_RSYSTEM_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                         RSystemTab                                         */
/**********************************************************************************************/

class RSystemTab: public RTab
{
  Q_OBJECT

  public:
    _M Vacuum         RSystemTab(RSystemList* systems, RMainWindow* parent = 0);
    _V Vacuum         ~RSystemTab();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RSYSTEM_TAB_HH */
