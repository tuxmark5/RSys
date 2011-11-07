#ifndef RSYS_INTERFACE_RMAIN_WINDOW_HH
#define RSYS_INTERFACE_RMAIN_WINDOW_HH

/**********************************************************************************************/
#include <RSys/RSys.hh>
#include <QtGui/QMainWindow>
/********************************************* RS *********************************************/
/*                                        RMainWindow                                         */
/**********************************************************************************************/

class RMainWindow: public QMainWindow
{
  Q_OBJECT

  public:
    _F class          RMainMenuBar;
    _F class          RMainToolBar;
    _F class          RPaletteDock;

  private:
    _M QSplitter*     m_splitter;
    _M QTabWidget*    m_tabWidgetL;
    _M QTabWidget*    m_tabWidgetR;

    _M QAction*       m_openAction;
    _M QAction*       m_saveAction;
    _M QAction*       m_importAction;
    _M QAction*       m_disconnectAction;
    _M QAction*       m_exitAction;
    _M QAction*       m_searchAction;
    _M QAction*       m_divisionsStateAction;
    _M QAction*       m_systemsStateAction;
    _M QAction*       m_helpAction;

    _M RData*         m_data;

  public:
    _M Vacuum         RMainWindow(QWidget* parent = 0);
    _V Vacuum         ~RMainWindow();
    _M void           createActions();
    _M void           createTabs();

  private:
    _M void           addLeftTab(RTab* tab, const char* title, const char* toolTip);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMAIN_WINDOW_HH */
