#ifndef RSYS_INTERFACE_RMAIN_MENU_BAR_HH
#define RSYS_INTERFACE_RMAIN_MENU_BAR_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QMenuBar>
/********************************************* RS *********************************************/
/*                                        RMainMenuBar                                        */
/**********************************************************************************************/

class RMainMenuBar: public QMenuBar
{
  Q_OBJECT

  public:
    _M QMenu*       m_viewMenu;

  public:
    _M Vacuum       RMainMenuBar(RMainWindow* parent = 0);
    _V Vacuum       ~RMainMenuBar();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMAIN_MENU_BAR_HH */
