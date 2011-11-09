#ifndef RSYS_INTERFACE_RDIVISION_TAB_HH
#define RSYS_INTERFACE_RDIVISION_TAB_HH

/**********************************************************************************************/
#include <RSys/Interface/RTab.hh>
/********************************************* RS *********************************************/
/*                                        RDivisionTab                                        */
/**********************************************************************************************/

class RDivisionTab: public RTab
{
  Q_OBJECT

  public:
    _M Vacuum         RDivisionTab(RMainWindow* parent = 0);
    _V Vacuum         ~RDivisionTab();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RDIVISION_TAB_HH */
