#include <RSys/Core/RData.hh>

#include <RSys/Interface/RIntervalToolBar.hh>
#include <RSys/Interface/RLoginWidget.hh>
#include <RSys/Interface/RMainMenuBar.hh>
#include <RSys/Interface/RMainToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RPaletteDock.hh>

#include <RSys/Interface/RDivisionTab.hh>
#include <RSys/Interface/RMeasureTab.hh>
#include <RSys/Interface/RSystemTab.hh>
#include <RSys/Interface/RUsageTab.hh>


#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QSplitter>
#include <QtGui/QScrollArea>
#include <QtGui/QTableView>
#include <QtGui/QTabWidget>
#include <QtGui/QAction>

#include <RSys/Core/RMeasure.hh>
#include <RSys/Util/RContainer.hh>

/********************************************* RS *********************************************/
/*                                        RMainWindow                                         */
/**********************************************************************************************/

Vacuum RMainWindow :: RMainWindow(QWidget* parent):
  QMainWindow(parent)
{
  createActions();

  addToolBar(new RMainToolBar(this));
  addToolBar(new RIntervalToolBar(this));
  addDockWidget(Qt::RightDockWidgetArea, new RPaletteDock(this));
  setMenuBar(new RMainMenuBar(this));

  m_tabWidgetL  = new QTabWidget(this);
  m_tabWidgetL->setTabPosition(QTabWidget::South);

  m_tabWidgetR  = new QTabWidget(this);
  m_tabWidgetR->setTabPosition(QTabWidget::South);

  m_splitter    = new QSplitter(this);
  m_splitter->addWidget(m_tabWidgetL);
  m_splitter->addWidget(m_tabWidgetR);

  m_data        = new RData();

  createTabs();

  setCentralWidget(m_splitter);

  //setCentralWidget(new RLoginWidget(this));
}

/**********************************************************************************************/

RMainWindow :: ~RMainWindow()
{
}

/**********************************************************************************************/

void RMainWindow :: addLeftTab(RTab* tab, const char* title, const char* toolTip)
{
  int id = m_tabWidgetL->addTab(tab, QString::fromUtf8(title));

  m_tabWidgetL->setTabToolTip(id, QString::fromUtf8(toolTip));
}

/**********************************************************************************************/

#define R_ACTION(icon, name) new QAction(QIcon(icon), QString::fromUtf8(name), this)

void RMainWindow :: createActions()
{
  QActionGroup* stateGroup = new QActionGroup(this);

  m_openAction            = R_ACTION(":/icons/open.png",        "Atverti");
  m_openAction->setShortcut(QKeySequence("Ctrl+O"));

  m_saveAction            = R_ACTION(":/icons/save.png",        "Išsaugoti");
  m_saveAction->setShortcut(QKeySequence("Ctrl+S"));

  m_importAction          = R_ACTION(":/icons/import.png",      "Importuoti");
  m_importAction->setShortcut(QKeySequence("Ctrl+I"));

  m_disconnectAction      = R_ACTION(":/icons/disconnect.png",  "Atsijungti");
  m_disconnectAction->setShortcut(QKeySequence("Alt+D"));

  m_exitAction            = R_ACTION(":/icons/exit.png",        "Išeiti");
  m_exitAction->setShortcut(QKeySequence("Ctrl+Shift+X"));

  m_searchAction          = R_ACTION(":/icons/search.png",      "Ieškoti intervalo");
  m_searchAction->setCheckable(true);
  m_searchAction->setShortcut(QKeySequence("Ctrl+F"));

  m_divisionsStateAction  = R_ACTION(":/icons/divisions.png",   "Padaliniai");
  m_divisionsStateAction->setActionGroup(stateGroup);
  m_divisionsStateAction->setCheckable(true);
  m_divisionsStateAction->setChecked(true);
  m_divisionsStateAction->setShortcut(QKeySequence("Alt+P"));

  m_systemsStateAction    = R_ACTION(":/icons/systems.png",     "Sistemos");
  m_systemsStateAction->setActionGroup(stateGroup);
  m_systemsStateAction->setCheckable(true);
  m_systemsStateAction->setShortcut(QKeySequence("Alt+I"));

  m_helpAction            = R_ACTION(":/icons/help.png",        "Pagalba");
  m_helpAction->setShortcut(QKeySequence("F1"));
}

/**********************************************************************************************/

void RMainWindow :: createTabs()
{
  addLeftTab(new RMeasureTab(m_data->measures(), this),  "Priemonės", "Priemonės TOOL");
  addLeftTab(new RDivisionTab(m_data->divisions(), this), "Padaliniai", "Padaliniai TOOL");
  addLeftTab(new RSystemTab(m_data->systems(), this),   "IS", "IS TOOL");

  // 2d
  m_tabWidgetL->addTab(new QLabel("NOT IMPLEMENTED"), QString::fromUtf8("Priemonių adm."));
  m_tabWidgetL->addTab(new QLabel("NOT IMPLEMENTED"), QString::fromUtf8("IS adm."));

  m_tabWidgetL->addTab(new QLabel("NOT IMPLEMENTED"), QString::fromUtf8("Istoriniai duom."));
  m_tabWidgetL->addTab(new QLabel("NOT IMPLEMENTED"), QString::fromUtf8("Planuojami kiekiai"));

  m_tabWidgetR->addTab(new RUsageTab(), QString::fromUtf8("Apkrovos ir prognozės"));
  m_tabWidgetR->addTab(new QLabel("TEST2"), QString::fromUtf8("Apžvalga"));

  // WIP
  /*auto c = newContainer(&g_measures);
  c->addColumn<QString, &RMeasure::name,       &RMeasure::setName>       ("name");
  c->addColumn<QString, &RMeasure::identifier, &RMeasure::setIdentifier> ("ident");

  QTableView* v = new QTableView();
  v->setModel(new RModel1D(c, this));
  v->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
  //v->horizontalHeader()->set
  v->verticalHeader()->setDefaultSectionSize(20); //setHeight

  m_tabWidgetL->addTab(v, QString::fromUtf8("Priemonės"));*/

}

/**********************************************************************************************/
