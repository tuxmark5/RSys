#ifndef RSYS_INTERFACE_RMAIN_WINDOW_HH
#define RSYS_INTERFACE_RMAIN_WINDOW_HH

/**********************************************************************************************/
#include <QtCore/QDate>
#include <QtGui/QMainWindow>
#include <RSys/RSys.hh>
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
    _M QWidget*             m_widgetR;
    _M QVBoxLayout*         m_layoutL;
    _M QVBoxLayout*         m_layoutR;
    _M QTabWidget*          m_tabWidgetL;
    _M QTabWidget*          m_tabWidgetR;

    _M QMenu*               m_viewMenu;
    _M QAction*             m_openAction;
    _M QAction*             m_saveAction;
    _M QAction*             m_importAction;
    _M QAction*             m_commitAction;
    _M QAction*             m_rollbackAction;
    _M QAction*             m_disconnectAction;
    _M QAction*             m_exitAction;
    _M QAction*             m_searchAction;
    _M QAction*             m_divisionsStateAction;
    _M QAction*             m_systemsStateAction;
    _M QAction*             m_helpAction;

    _M QAction*             m_showMainToolbarAction;
    _M QAction*             m_showIntervalToolbarAction;
    _M QAction*             m_showPaletteAction;

    _M RDatabase*           m_database;
    _M RData*               m_data0;
    _M RData*               m_data1;
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
    _M void                 addStatusWidget(QWidget* widget, QObject* owner = 0);
    _M void                 connectActions();
    _M RUnitPtrList*        currentUnits() const;
    _M void                 createActions();
    _M void                 createContainers();
    _M void                 createTabs();
    _M RData*               data() const { return m_data1; }
    _M RContainer*          divisionContainer() const { return m_divisionContainer; }
    _M RContainer*          measureContainer() const { return m_measureContainer; }
    _M RContainer*          measure1Container() const { return m_measure1Container; }
    _M RMainMenuBar*        menuBar() const { return m_menuBar; }
    _M RResults*            results() const { return m_results; }
    _M QAction*             searchIntervalAction() const { return m_searchAction; }
    _M RContainer*          submissionContainer() const { return m_submissionContainer; }
    _M RContainer*          submission1Container() const { return m_submission1Container; }
    _M RContainer*          systemContainer() const { return m_systemContainer; }
    _M QAction*             systemsStateAction() const { return m_systemsStateAction; }

  public slots:
    _M void                 commit();
    _M void                 importData();
    _M void                 login();
    _M void                 logout();
    _M void                 onSearchFormDestroyed();
    _M void                 rollback();
    _M void                 setInterfaceEnabled(bool enabled);
    _M void                 setInterval();
    _M void                 setShowSearchForm(bool show);
    _M void                 showMessage(const QString& message, int timeout = 5000);
    _M void                 updateUnits();

  protected:
    _V void                 closeEvent(QCloseEvent* event);

  private:
    _M void                 addLeftTab(RTab* tab, const char* title, const char* toolTip);
    _M void                 addRightTab(RTab* tab, const char* title, const char* toolTip);

  private slots:
    _M void                 findIntervalNow();

  signals:
    _M void                 searchModeChanged(bool search = true);
    _M void                 unitsChanged(RUnitPtrList* units);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RMAIN_WINDOW_HH */
