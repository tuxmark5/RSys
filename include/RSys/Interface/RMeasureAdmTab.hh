#ifndef RSYS_INTERFACE_RMEASURE_ADM_TAB_HH
#define RSYS_INTERFACE_RMEASURE_ADM_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                       RMeasureAdmTab                                       */
/**********************************************************************************************/

class RMeasureAdmTab: public RTab
{
  Q_OBJECT

  public:
    _M Vacuum         RMeasureAdmTab(RMainWindow* parent = 0);
    _V Vacuum         ~RMeasureAdmTab();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMEASURE_ADM_TAB_HH */
