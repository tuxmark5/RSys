#include <QtGui/QAction>
#include <QtGui/QCloseEvent>
#include <QtGui/QFileDialog>
#include <QtGui/QListView>
#include <QtGui/QMessageBox>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QScrollArea>
#include <QtGui/QTableView>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>

#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Core/RUser.hh>

#include <RSys/Interface/RImportForm.hh>
#include <RSys/Interface/RIntervalToolBar.hh>
#include <RSys/Interface/RLoginWidget.hh>
#include <RSys/Interface/RMainMenuBar.hh>
#include <RSys/Interface/RMainToolBar.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RMessage.hh>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RPaletteDock.hh>
#include <RSys/Interface/RSearchForm.hh>

#include <RSys/Interface/RDivisionTab.hh>
#include <RSys/Interface/RMeasureAdmTab.hh>
#include <RSys/Interface/RMeasureTab.hh>
#include <RSys/Interface/RPlannedTab.hh>
#include <RSys/Interface/RSubmissionTab.hh>
#include <RSys/Interface/RSummaryTab.hh>
#include <RSys/Interface/RSystemAdmTab.hh>
#include <RSys/Interface/RSystemTab.hh>
#include <RSys/Interface/RUsageTab.hh>
#include <RSys/Interface/RUserAdmTab.hh>
#include <RSys/Interface/RUserTab.hh>

#include <RSys/Logic/RResults.hh>
#include <RSys/Parse/RValidator.hh>
#include <RSys/Store/RDatabase.hh>
#include <RSys/Store/RSqlEntity.hh>
#include <RSys/Util/RContainer.hh>

/********************************************* RS *********************************************/
/*                                        RMainWindow                                         */
/**********************************************************************************************/

Vacuum RMainWindow :: RMainWindow(QWidget* parent):
  QMainWindow(parent),
  m_loginWidget(0),
  m_searchForm(0)
{
  m_data0             = new RData();
  m_data1             = new RData();
  m_data1->enableIntervalTracking();
  m_results           = new RResults(m_data0, m_data1);
  m_database          = new RDatabase(m_data1, this);
  createContainers();

  createActions();
  connectActions();

  m_menuBar           = new RMainMenuBar(this);
  m_toolBar           = new RMainToolBar(this);
  m_intervalToolBar   = new RIntervalToolBar(this);
  m_paletteDock       = new RPaletteDock(this);

  setMenuBar(m_menuBar);
  addToolBar(m_toolBar);
  addToolBarBreak();
  addToolBar(m_intervalToolBar);
  addDockWidget(Qt::RightDockWidgetArea, m_paletteDock);

  m_widgetL           = new QWidget(this);
  m_widgetR           = new QWidget(this);
  m_layoutL           = new QVBoxLayout(m_widgetL);
  m_layoutR           = new QVBoxLayout(m_widgetR);
  m_tabWidgetL        = new QTabWidget(this);
  m_tabWidgetR        = new QTabWidget(this);

  m_layoutL->setMargin(0);
  m_layoutR->setMargin(0);

  m_layoutL->setSpacing(5);
  m_layoutR->setSpacing(5);

  m_tabWidgetL->setTabPosition(QTabWidget::South);
  m_tabWidgetR->setTabPosition(QTabWidget::South);

  m_splitter          = new QSplitter(this);
  m_layoutL->addWidget(m_tabWidgetL);
  m_layoutR->addWidget(m_tabWidgetR);
  m_splitter->addWidget(m_widgetL);
  m_splitter->addWidget(m_widgetR);

  createTabs();
  updateUnits();

  connect(m_intervalToolBar, SIGNAL(intervalChanged()), this, SLOT(setInterval()));
  connect(m_intervalToolBar, SIGNAL(message(QString,int)), this, SLOT(showMessage(QString,int)));

  logout();
}

/**********************************************************************************************/

Vacuum RMainWindow :: ~RMainWindow()
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

void RMainWindow :: addStatusWidget(QWidget* widget, QObject* owner)
{
  QVBoxLayout* layout = m_widgetL->width() > 0 ? m_layoutL : m_layoutR;

  for (int i = 0; i < layout->count(); i++)
  {
    QWidget* widget = layout->itemAt(i)->widget();

    if (RMessage* message = qobject_cast<RMessage*>(widget))
      if (message->owner() == owner)
        message->onCloseClicked();
  }

  layout->insertWidget(0, widget);
}

/**********************************************************************************************/

void RMainWindow :: closeEvent(QCloseEvent* event)
{
  int button = QMessageBox::question(this, R_S("Išeiti"), R_S("Ar tikrai norite išeiti?"),
    QMessageBox::Ok | QMessageBox::Cancel);

  switch (button)
  {
    case QMessageBox::Ok:
      event->accept();
      return;

    case QMessageBox::Cancel:
      event->ignore();
      return;
  }
}

/**********************************************************************************************/

void RMainWindow :: commit()
{
  if (m_database->commit())
  {
    *m_data0 = *m_data1;
    showMessage(R_S("Duomenys išsaugoti."));
  }
  else
  {
    showMessage(R_S("KLAIDA: Nepavyko išsaugoti duomenų."));
  }
}

/**********************************************************************************************/

void RMainWindow :: connectActions()
{
  QAction::connect(m_disconnectAction, SIGNAL(triggered()), this, SLOT(logout()));
  QAction::connect(m_commitAction, SIGNAL(triggered()), this, SLOT(commit()));
  QAction::connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
  QAction::connect(m_importAction, SIGNAL(triggered()), this, SLOT(importData()));
  QAction::connect(m_rollbackAction, SIGNAL(triggered()), this, SLOT(rollback()));
  QAction::connect(m_searchAction, SIGNAL(toggled(bool)), this, SLOT(setShowSearchForm(bool)));
  QAction::connect(m_systemsStateAction, SIGNAL(toggled(bool)), this, SLOT(updateUnits()));

  (*m_data1)[RSubmission::measureChange]  << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RSubmission::countChange]    << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RSubmission::date0Change]    << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RSubmission::date1Change]    << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RDivision::onMeasureSet]     << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RDivision::onMeasureUnset]   << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RDivision::onSystemSet]      << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RDivision::onSystemUnset]    << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RUser::onSql]                << std::bind(&RSqlEntity::exec, m_database->sqlEntity(), _1);
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

  m_commitAction          = R_ACTION(":/icons/commit.png",      "COMMIT");

  m_rollbackAction        = R_ACTION(":/icons/rollback.png",    "ROLLBACK");

  m_disconnectAction      = R_ACTION(":/icons/disconnect.png",  "Atsijungti");
  m_disconnectAction->setShortcut(QKeySequence("Alt+D"));

  m_exitAction            = R_ACTION(":/icons/exit.png",        "Išeiti");
  m_exitAction->setShortcut(QKeySequence("Ctrl+Shift+X"));

  m_searchAction          = R_ACTION(":/icons/find_interval.png", "Mažiausiai apkrauti intervalai");
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

  /*m_showMainToolbarAction = R_ACTION("Pagrindinė įrankių juosta");
  m_showIntervalToolbarAction = R_ACTION("Intervalo juosta");
  m_showPaletteAction*/
}

/**********************************************************************************************/

void RMainWindow :: createContainers()
{
  auto cd = newContainer(m_data1->divisions());
  cd->addColumn("Pavadinimas");
  cd->addColumn("Aprašymas");
  cd->addAccessor2<QString>(0, Qt::DisplayRole) >> &RDivision::identifier << &RDivision::setIdentifier;
  cd->addAccessor2<QString>(0, Qt::ToolTipRole) >> &RDivision::fullName;
  cd->addAccessor2<QString>(1, Qt::DisplayRole) >> &RDivision::name       << &RDivision::setName;
  cd->setAlloc([=]() { return new RDivision(m_data1); });

  auto cm = newContainer(m_data1->measures());
  cm->addColumn("Pavadinimas");
  cm->addColumn("Aprašymas");
  cm->addAccessor2<QString>(0, Qt::DisplayRole) >> &RMeasure::identifier << &RMeasure::setIdentifier;
  cm->addAccessor2<QString>(0, Qt::ToolTipRole) >> &RMeasure::fullName;
  cm->addAccessor2<QString>(1, Qt::DisplayRole) >> &RMeasure::name       << &RMeasure::setName;
  cm->setAlloc([=]() { return new RMeasure(m_data1); });

  auto cu = newContainer(m_data1->submissions());
  cu->addColumn("Priemonė");
  cu->addColumn("Kiekis");
  cu->addColumn("Pradžia");
  cu->addColumn("Pabaiga");
  cu->addAccessor2<QString>(0, Qt::DisplayRole)
    >> &RSubmission::measureName << &RSubmission::setMeasureName;
  cu->addAccessor2<QString>(0, Qt::ToolTipRole)
    >> &RSubmission::measureFullName;
  cu->addAccessor2<int>(1, Qt::DisplayRole)
    >> &RSubmission::count << &RSubmission::setCount;
  cu->addAccessor2<QDate>(2, Qt::DisplayRole)
    >> &RSubmission::date0 << &RSubmission::setDate0;
  cu->addAccessor2<QDate>(3, Qt::DisplayRole)
    >> &RSubmission::date1 << &RSubmission::setDate1;
  cu->setAlloc([=]() { return new RSubmission(m_data1); });

  auto cu1 = newContainer(m_data1->submissions1(), *cu);
  cu1->addAccessor2<QString>(0, Qt::DisplayRole, true)
    >> &RSubmission::measureName << &RSubmission::setMeasure1Name;

  auto cs = newContainer(m_data1->systems());
  cs->addColumn("Pavadinimas");
  cs->addColumn("Aprašymas");
  cs->addAccessor2<QString>(0, Qt::DisplayRole) >> &RSystem::identifier << &RSystem::setIdentifier;
  cs->addAccessor2<QString>(0, Qt::ToolTipRole) >> &RSystem::fullName;
  cs->addAccessor2<QString>(1, Qt::DisplayRole) >> &RSystem::name       << &RSystem::setName;
  cs->setAlloc([=]() { return new RSystem(m_data1); });

  m_divisionContainer     = cd;
  m_measureContainer      = cm;
  m_measure1Container     = newContainer(m_data1->measures1(), *cm);
  m_submissionContainer   = cu;
  m_submission1Container  = cu1;
  m_systemContainer       = cs;
}

/**********************************************************************************************/

void RMainWindow :: createTabs()
{
  addLeftTab(new RMeasureTab(this),     "Priemonės", "Paramos priemonės");
  addLeftTab(new RDivisionTab(this),    "Padaliniai", "Padaliniai");
  addLeftTab(new RSystemTab(this),      "IS", "Informacinės sistemos");
  addLeftTab(new RMeasureAdmTab(this),  "Priemonių adm.", "Paramos priemonių administravimas");
  addLeftTab(new RSystemAdmTab(this),   "IS adm.", "Informacinių sistemų pasiskirstymas");
  addLeftTab(new RSubmissionTab(this),  "Istoriniai duom.", "Istoriniai duomenys");
  addLeftTab(new RPlannedTab(this),     "Planuojami kiekiai", "Planuojami paramos priemonių kiekiai");  

  addRightTab(new RUsageTab(this),      "Apkrovos ir prognozės", "Individualios padalinių/sistemų apkrovos ir prognozės");
  addRightTab(new RSummaryTab(this),    "Apžvalga", "Apžvalga");

  addLeftTab(new RUserTab(this),        "Naudotojai", "Sistemos naudotojai");
  addRightTab(new RUserAdmTab(this),    "Naud. adm.", "Sistemos naudototojų administravimas");
}

/**********************************************************************************************/

RUnitPtrList* RMainWindow :: currentUnits() const
{
  if (m_systemsStateAction->isChecked())
    return m_data1->systems()->cast<RUnitPtr>();
  else
    return m_data1->divisions()->cast<RUnitPtr>();
}

/**********************************************************************************************/

void RMainWindow :: findIntervalNow()
{
  R_GUARD(m_searchForm, Vacuum);

  if (m_intervalToolBar->isIntervalValid())
  {
    m_intervalToolBar->applyInterval();
    m_searchForm->getSeasonalLengths(m_results->seasonalLengths());
    emit searchModeChanged(true);
  }
  else
  {
    showMessage(R_S("Pirma pasirinkite validų paieškos intervalą"));
  }
}

/**********************************************************************************************/

void RMainWindow :: importData()
{
  QString fileName = QFileDialog::getOpenFileName
      (this, QString::fromUtf8("Importuoti"), QString(),
       QString("Microsoft Excel bylos (*.xls)"));

  if (!fileName.isNull())
  {
    RValidator      parser;
    RImportForm*    importForm;

    m_results->setUpdatesEnabled(false);
    parser.validate(fileName, m_data1);
    m_results->setUpdatesEnabled(true);
    m_data1->calculateIntervals();

    importForm = new RImportForm();
    addStatusWidget(new RStatusWidget(importForm));

    showMessage(QString::fromUtf8("Duomenys sėkmingai (o gal ir ne) importuoti\n"
                                  "Vytautai, man čia reikia, kad tavo kodas išspjautų tik vieną žinutę\n"
                                  "Tam padaryk kokį naują signalą, o visas perteklines žinutes į logą galim\n"
                                  "kraut"), 15000);
    m_intervalToolBar->applyInterval();
  }
}

/**********************************************************************************************/

void RMainWindow :: login()
{
  R_GUARD(m_loginWidget, Vacuum);

  m_data1->withBlock([this]
  {
    m_database->select();
  });
  m_data1->calculateIntervals();

  setInterfaceEnabled(true);
  m_loginWidget   = 0; // deleted by QMainWindow::setCentralWidget
  *m_data0        = *m_data1;
  m_intervalToolBar->applyInterval();
}

/**********************************************************************************************/

void RMainWindow :: logout()
{
  R_GUARD(!m_loginWidget, Vacuum);

  m_data0->clear();
  m_data1->clear();
  m_loginWidget = new RLoginWidget(m_database);
  connect(m_loginWidget, SIGNAL(loggedIn()), this, SLOT(login()));
  setInterfaceEnabled(false);
  setCentralWidget(m_loginWidget);
}

/**********************************************************************************************/

void RMainWindow :: onSearchFormDestroyed()
{
  m_searchAction->setChecked(false);
  m_searchForm = 0;
}

/**********************************************************************************************/

void RMainWindow :: rollback()
{
  if (m_database->rollback())
  {
    *m_data1 = *m_data0;
    m_intervalToolBar->applyInterval();
    showMessage(R_S("Duomenys atstatyti."));
  }
}

/**********************************************************************************************/

void RMainWindow :: setInterfaceEnabled(bool enabled)
{
  if (enabled)
    setCentralWidget(m_splitter);

  m_menuBar->setEnabled(enabled);
  m_toolBar->setEnabled(enabled);
  m_intervalToolBar->setEnabled(enabled);
  m_paletteDock->setEnabled(enabled);
  m_paletteDock->setVisible(enabled);
  m_splitter->setVisible(enabled);

  if (!enabled)
    m_splitter->setParent(0);
}

/**********************************************************************************************/

void RMainWindow :: setInterval()
{
  if (m_searchForm)
    emit searchModeChanged();
}

/**********************************************************************************************/

void RMainWindow :: setShowSearchForm(bool show)
{
  if (!m_searchForm && show)
  {
    RStatusWidget* statusWidget;

    m_searchForm = new RSearchForm(this);

    addStatusWidget(statusWidget = new RStatusWidget(m_searchForm));
    // handle untoggle
    connect(m_searchAction, SIGNAL(toggled(bool)), statusWidget, SLOT(onCloseClicked()));
    // handle RStatusWidget's "X" button
    connect(m_searchForm, SIGNAL(destroyed()), this, SLOT(onSearchFormDestroyed()));
    connect(m_searchForm, SIGNAL(findIntervalPressed()), this, SLOT(findIntervalNow()));
  }
  else
  {
    m_searchAction->setChecked(false);
    m_searchForm = 0;
  }

  emit searchModeChanged(show);
}

/**********************************************************************************************/

void RMainWindow :: showMessage(const QString& message, int timeout)
{
  if (timeout == -1)
  {
    timeout = 5000 + message.size() * 40;
  }

  RMessage* widget = new RMessage(message, timeout);

  widget->setOwner(sender());
  addStatusWidget(widget, sender());
}

/**********************************************************************************************/

void RMainWindow :: updateUnits()
{
  emit unitsChanged(currentUnits());
}

/**********************************************************************************************/
