#include <QtGui/QAction>
#include <QtGui/QFileDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QSplitter>
#include <QtGui/QScrollArea>
#include <QtGui/QTableView>
#include <QtGui/QTabWidget>

#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Core/RSystem.hh>

#include <RSys/Interface/RIntervalToolBar.hh>
#include <RSys/Interface/RLoginWidget.hh>
#include <RSys/Interface/RMainMenuBar.hh>
#include <RSys/Interface/RMainToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RPaletteDock.hh>

#include <RSys/Interface/RDivisionTab.hh>
#include <RSys/Interface/RMeasureAdmTab.hh>
#include <RSys/Interface/RMeasureTab.hh>
#include <RSys/Interface/RPlannedTab.hh>
#include <RSys/Interface/RSubmissionTab.hh>
#include <RSys/Interface/RSystemAdmTab.hh>
#include <RSys/Interface/RSystemTab.hh>
#include <RSys/Interface/RUsageTab.hh>

#include <RSys/Logic/RResults.hh>
#include <RSys/Parse/RValidator.hh>
#include <RSys/Util/RContainer.hh>

/********************************************* RS *********************************************/
/*                                        RMainWindow                                         */
/**********************************************************************************************/

Vacuum RMainWindow :: RMainWindow(QWidget* parent):
  QMainWindow(parent)
{
  m_data        = new RData();
  m_results     = new RResults(m_data);
  createContainers();

  createActions();
  connectActions();

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

  createTabs();
  setCentralWidget(m_splitter);

  //setCentralWidget(new RLoginWidget(this));
}

/**********************************************************************************************/

RMainWindow :: ~RMainWindow()
{
  //delete m_results;
}

/**********************************************************************************************/

void RMainWindow :: addLeftTab(RTab* tab, const char* title, const char* toolTip)
{
  int id = m_tabWidgetL->addTab(tab, QString::fromUtf8(title));

  m_tabWidgetL->setTabToolTip(id, QString::fromUtf8(toolTip));
}

/**********************************************************************************************/

void RMainWindow :: addRightTab(RTab* tab, const char* title, const char* toolTip)
{
  int id = m_tabWidgetR->addTab(tab, QString::fromUtf8(title));

  m_tabWidgetR->setTabToolTip(id, QString::fromUtf8(toolTip));
}

/**********************************************************************************************/

void RMainWindow :: connectActions()
{
  QAction::connect(m_importAction, SIGNAL(triggered()), this, SLOT(importData()));
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

void RMainWindow :: createContainers()
{
  auto cd = newContainer(m_data->divisions());
  cd->addColumn("Pavadinimas");
  cd->addColumn("Aprašymas");
  cd->addAccessor2<QString>(0, Qt::DisplayRole) >> &RDivision::identifier << &RDivision::setIdentifier;
  cd->addAccessor2<QString>(1, Qt::DisplayRole) >> &RDivision::name       << &RDivision::setName;
  cd->setAlloc([=]() { return new RDivision(m_data); });

  auto cm = newContainer(m_data->measures());
  cm->addColumn("Pavadinimas");
  cm->addColumn("Aprašymas");
  cm->addAccessor2<QString>(0, Qt::DisplayRole) >> &RMeasure::identifier << &RMeasure::setIdentifier;
  cm->addAccessor2<QString>(1, Qt::DisplayRole) >> &RMeasure::name       << &RMeasure::setName;
  cm->setAlloc([=]() { return new RMeasure(m_data); });

  auto cu = newContainer(m_data->submissions());
  cu->addColumn("Priemonė");
  cu->addColumn("Kiekis");
  cu->addColumn("Pradžia");
  cu->addColumn("Pabaiga");
  cu->addAccessor2<QString>(0, Qt::DisplayRole)
    >> &RSubmission::measureName << &RSubmission::setMeasureName;
  cu->addAccessor2<int>(1, Qt::DisplayRole)
    >> &RSubmission::count << &RSubmission::setCount;
  cu->addAccessor2<QDate>(2, Qt::DisplayRole)
    >> &RSubmission::date0 << &RSubmission::setDate0;
  cu->addAccessor2<QDate>(3, Qt::DisplayRole)
    >> &RSubmission::date1 << &RSubmission::setDate1;
  cu->setAlloc([=]() { return new RSubmission(m_data); });

  auto cu1 = newContainer(m_data->submissions1(), *cu);
  cu->addAccessor2<QString>(0, Qt::DisplayRole)
    << &RSubmission::setMeasure1Name;

  auto cs = newContainer(m_data->systems());
  cs->addColumn("Pavadinimas");
  cs->addColumn("Aprašymas");
  cs->addAccessor2<QString>(0, Qt::DisplayRole) >> &RSystem::identifier << &RSystem::setIdentifier;
  cs->addAccessor2<QString>(1, Qt::DisplayRole) >> &RSystem::name       << &RSystem::setName;
  cs->setAlloc([=]() { return new RSystem(m_data); });

  m_divisionContainer     = cd;
  m_measureContainer      = cm;
  m_measure1Container     = newContainer(m_data->measures1(), *cm);
  m_submissionContainer   = cu;
  m_submission1Container  = cu1;
  m_systemContainer       = cs;
}

/**********************************************************************************************/

void RMainWindow :: createTabs()
{
  auto dmGetter = [=](int x, int y) -> QVariant
  {
    RDivision*  division  = m_data->divisions()->at(y);
    RMeasure*   measure   = m_data->measures()->at(x);
    double      value     = division->m_measureMap.value(measure, 0);

    return value == 0.0 ? QVariant() : value;
  };

  auto dmSetter = [=](int x, int y, const QVariant& var) -> void
  {
    RDivision*  division  = m_data->divisions()->at(y);
    RMeasure*   measure   = m_data->measures()->at(x);

    division->setMeasure(measure, var.toDouble());
  };

  auto dsGetter = [=](int x, int y) -> QVariant
  {
    RDivision*  division  = m_data->divisions()->at(y);
    RSystem*    system    = m_data->systems()->at(x);
    int         value     = division->m_systemMap.value(system, 0);

    return value == 1 ? 1 : QVariant();
  };

  auto dsSetter = [=](int x, int y, const QVariant& var) -> void
  {
    RDivision*  division  = m_data->divisions()->at(y);
    RSystem*    system    = m_data->systems()->at(x);

    division->setSystem(system, var.toInt());
  };

  RMeasureAdmTab*   dmTab = new RMeasureAdmTab(dmGetter, dmSetter, this);
  RSystemAdmTab*    dsTab = new RSystemAdmTab(dsGetter, dsSetter, this);

  addLeftTab(new RMeasureTab(this),     "Priemonės", "Priemonės TOOL");
  addLeftTab(new RDivisionTab(this),    "Padaliniai", "Padaliniai TOOL");
  addLeftTab(new RSystemTab(this),      "IS", "IS TOOL");
  addLeftTab(dmTab,                     "Priemonių adm.", "Priemonės TOOL");
  addLeftTab(dsTab,                     "IS adm.", "IS TOOL");
  addLeftTab(new RSubmissionTab(this),  "Istoriniai duom.", "IS TOOL");
  addLeftTab(new RPlannedTab(this),     "Planuojami kiekiai", "IS TOOL");

  addRightTab(new RUsageTab(this),      "Apkrovos ir prognozės", "ZEL");
  m_tabWidgetR->addTab(new QLabel("TEST2"), QString::fromUtf8("Apžvalga"));
}

/**********************************************************************************************/

void RMainWindow :: importData()
{
  QString fileName = QFileDialog::getOpenFileName
      (this, QString::fromUtf8("Importuoti"), QString(),
       QString("Microsoft Excel bylos (*.xls)"));

  if (!fileName.isNull())
  {
    RValidator    parser;

    parser.validate(fileName, m_data);
  }
}

/**********************************************************************************************/
