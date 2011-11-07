#ifndef RSYS_INTERFACE_RMEASURE_TAB_HH
#define RSYS_INTERFACE_RMEASURE_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                        RMeasureTab                                         */
/**********************************************************************************************/

class RMeasureTab: public RTab
{
  Q_OBJECT

  public:
    _M Vacuum         RMeasureTab(RMeasureList* measures, RMainWindow* parent = 0);
    _V Vacuum         ~RMeasureTab();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMEASURE_TAB_HH */
