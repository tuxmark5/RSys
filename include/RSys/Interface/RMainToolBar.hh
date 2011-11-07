#ifndef RSYS_INTERFACE_RMAIN_TOOL_BAR_HH
#define RSYS_INTERFACE_RMAIN_TOOL_BAR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QToolBar>
/********************************************* RS *********************************************/
/*                                        RMainToolBar                                        */
/**********************************************************************************************/

class RMainToolBar: public QToolBar
{
  Q_OBJECT

  public:
    _M Vacuum       RMainToolBar(RMainWindow* parent = 0);
    _V Vacuum       ~RMainToolBar();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMAIN_TOOL_BAR_HH */
