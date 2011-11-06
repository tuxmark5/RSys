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
    _F class        RMainMenuBar;
    _F class        RMainToolBar;

  private:
    _M QSplitter*     m_splitter;
    _M QTabWidget*    m_tabWidgetL;
    _M QTabWidget*    m_tabWidgetR;
    _M QScrollArea*   m_sa_results;

    _M QAction*       m_openAction;
    _M QAction*       m_saveAction;
    _M QAction*       m_importAction;
    _M QAction*       m_disconnectAction;
    _M QAction*       m_exitAction;
    _M QAction*       m_searchAction;
    _M QAction*       m_divisionsStateAction;
    _M QAction*       m_systemsStateAction;
    _M QAction*       m_helpAction;

  public:
    _M Vacuum         RMainWindow(QWidget* parent = 0);
    _V Vacuum         ~RMainWindow();
    _M void           createActions();
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMAIN_WINDOW_HH */
