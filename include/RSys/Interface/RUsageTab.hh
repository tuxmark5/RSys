#ifndef RSYS_INTERFACE_RTAB_HH
#define RSYS_INTERFACE_RTAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                         RUsageTab                                          */
/**********************************************************************************************/

class RUsageTab: public RTab
{
  Q_OBJECT

  private:
    _M QScrollArea*   m_scrollArea;

  public:
    _M Vacuum         RUsageTab(QWidget* parent = 0);
    _V Vacuum         ~RUsageTab();
    _V void           resizeEvent(QResizeEvent* event);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RTAB_HH */
