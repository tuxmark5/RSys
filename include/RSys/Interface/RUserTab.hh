#ifndef RSYS_INTERFACE_RUSER_TAB_HH
#define RSYS_INTERFACE_RUSER_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                          RUserTab                                          */
/**********************************************************************************************/

class RUserTab: public RTab
{
  Q_OBJECT

  private:
    _M RMainWindow*   m_mainWindow;
    _M RContainerPtr  m_userContainer;

  public:
    _M Vacuum         RUserTab(RMainWindow* parent = 0);
    _V Vacuum         ~RUserTab();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RUSER_TAB_HH */
