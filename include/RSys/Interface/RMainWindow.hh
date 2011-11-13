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
    _F class                RMainMenuBar;
    _F class                RMainToolBar;
    _F class                RPaletteDock;

  private:
    _M RLoginWidget*        m_loginWidget;

    _M RMainMenuBar*        m_menuBar;
    _M RMainToolBar*        m_toolBar;
    _M RIntervalToolBar*    m_intervalToolBar;
    _M RPaletteDock*        m_paletteDock;
    _M RSearchForm*         m_searchForm;

    _M QSplitter*           m_splitter;
    _M QWidget*             m_widgetL;
    _M QVBoxLayout*         m_layoutL;
    _M QTabWidget*          m_tabWidgetL;
    _M QTabWidget*          m_tabWidgetR;

    _M QAction*             m_openAction;
    _M QAction*             m_saveAction;
    _M QAction*             m_importAction;
    _M QAction*             m_disconnectAction;
    _M QAction*             m_exitAction;
    _M QAction*             m_searchAction;
    _M QAction*             m_divisionsStateAction;
    _M QAction*             m_systemsStateAction;
    _M QAction*             m_helpAction;

    _M RData*               m_data;
    _M RResults*            m_results;

    _M RContainer*          m_divisionContainer;
    _M RContainer*          m_measureContainer;
    _M RContainer*          m_measure1Container;
    _M RContainer*          m_submissionContainer;
    _M RContainer*          m_submission1Container;
    _M RContainer*          m_systemContainer;

  public:
    _M Vacuum               RMainWindow(QWidget* parent = 0);
    _V Vacuum               ~RMainWindow();
    _M void                 addStatusWidget(QWidget* widget);
    _M void                 connectActions();
    _M void                 createActions();
    _M void                 createContainers();
    _M void                 createTabs();
    _M RData*               data() const { return m_data; }
    _M RContainer*          divisionContainer() const { return m_divisionContainer; }
    _M RContainer*          measureContainer() const { return m_measureContainer; }
    _M RContainer*          measure1Container() const { return m_measure1Container; }
    _M RResults*            results() const { return m_results; }
    _M RContainer*          submissionContainer() const { return m_submissionContainer; }
    _M RContainer*          submission1Container() const { return m_submission1Container; }
    _M RContainer*          systemContainer() const { return m_systemContainer; }
    _M QAction*             systemsStateAction() const { return m_systemsStateAction; }

  public slots:
    _M void                 importData();
    _M void                 login();
    _M void                 logout();
    _M void                 onSearchFormDestroyed();
    _M void                 onUnitModeChanged(bool systems);
    _M void                 setInterfaceEnabled(bool enabled);
    _M void                 setShowSearchForm(bool show);
    _M void                 showMessage(const QString& message, int timeout = 5000);

  signals:
    _M void                 unitsChanged(RUnitList* units);

  private:
    _M void                 addLeftTab(RTab* tab, const char* title, const char* toolTip);
    _M void                 addRightTab(RTab* tab, const char* title, const char* toolTip);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMAIN_WINDOW_HH */
