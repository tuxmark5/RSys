#include <RSys/Interface/RIntervalToolBar.hh>
#include <RSys/Interface/RLoginWidget.hh>
#include <RSys/Interface/RMainMenuBar.hh>
#include <RSys/Interface/RMainToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RModel1D.hh>
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

QList<RMeasure*> g_measures;

Vacuum RMainWindow :: RMainWindow(QWidget* parent):
  QMainWindow(parent)
{
  m_tabWidgetL  = new QTabWidget(this);
  m_tabWidgetL->setTabPosition(QTabWidget::South);
  m_tabWidgetL->addTab(new QLabel("TEST1"), "LTAB");

  m_tabWidgetR  = new QTabWidget(this);

  createActions();

  setMenuBar(new RMainMenuBar(this));
  addToolBar(new RMainToolBar(this));
  addToolBar(new RIntervalToolBar(this));

  m_sa_results  = new QScrollArea(this);
  m_splitter    = new QSplitter(this);

  setCentralWidget(m_splitter);
  //setCentralWidget(new RLoginWidget(this));


  m_splitter->addWidget(m_tabWidgetL);
  m_splitter->addWidget(m_tabWidgetR);



  //RMeasure* r;
  //g_measures.append(r = new RMeasure());

  auto c = newContainer(&g_measures);
  c->addColumn<QString, &RMeasure::name,       &RMeasure::setName>       ("name");
  c->addColumn<QString, &RMeasure::identifier, &RMeasure::setIdentifier> ("ident");


  QTableView* v = new QTableView();
  v->setModel(new RModel1D(c, this));
  v->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
  //v->horizontalHeader()->set
  v->verticalHeader()->setDefaultSectionSize(20); //setHeight

  m_tabWidgetL->addTab(v, QString::fromUtf8("Priemonės"));

  m_tabWidgetR->setTabPosition(QTabWidget::South);
  m_tabWidgetR->addTab(new QLabel("TEST2"), "RTAB");
  m_tabWidgetR->addTab(new RUsageTab(), "RTAB");
}

/**********************************************************************************************/

RMainWindow :: ~RMainWindow()
{
}

/**********************************************************************************************/

#define R_ACTION(icon, name) new QAction(QIcon(icon), QString::fromUtf8(name), this)

void RMainWindow :: createActions()
{
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
  m_searchAction->setShortcut(QKeySequence("Ctrl+F"));

  m_divisionsStateAction  = R_ACTION(":/icons/divisions.png",   "Padaliniai");
  m_divisionsStateAction->setShortcut(QKeySequence("Alt+P"));

  m_systemsStateAction    = R_ACTION(":/icons/systems.png",     "Sistemos");
  m_systemsStateAction->setShortcut(QKeySequence("Alt+I"));

  m_helpAction            = R_ACTION(":/icons/help.png",        "Pagalba");
  m_helpAction->setShortcut(QKeySequence("F1"));
}

/**********************************************************************************************/
