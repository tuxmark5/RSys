#include <QtCore/QSettings>
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
#include <RSys/Core/RGroup.hh>
#include <RSys/Core/RMeasure.hh>
#include <RSys/Core/RSubmission.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Core/RUser.hh>

#include <RSys/Interface/RHelp.hh>
#include <RSys/Interface/RImportForm.hh>
#include <RSys/Interface/RIntervalToolBar.hh>
#include <RSys/Interface/RLogDock.hh>
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

#include <RSys/Logic/RCalculator.hh>
#include <RSys/Logic/RResults.hh>
#include <RSys/Parse/RParser.hh>
#include <RSys/Store/RDatabase.hh>
#include <RSys/Store/RSettings.hh>
#include <RSys/Store/RSqlEntity.hh>
#include <RSys/Util/RContainer.hh>

/**********************************************************************************************/
bool operator < (const QBrush&, const QBrush&) { return true; }
/********************************************* RS *********************************************/
/*                                        RMainWindow                                         */
/**********************************************************************************************/

Vacuum RMainWindow :: RMainWindow(QWidget* parent):
  QMainWindow(parent),
  m_loginWidget(0),
  m_searchForm(0),
  m_splitter(0),
  m_results(0),
  m_importing(false),
  m_loggingIn(false)
{
  m_data0             = new RData();
  m_data1             = new RData();
  m_database          = new RDatabase(m_data1, this);

  createContainers();
  createActions();

  m_logDock           = new RLogDock(this);
  m_paletteDock       = new RPaletteDock(this);
  m_menuBar           = new RMainMenuBar(this);
  m_toolBar           = new RMainToolBar(this);
  m_intervalToolBar   = new RIntervalToolBar(this);
  m_help              = new RHelp(this);

  createConnections();

  setMenuBar(m_menuBar);
  addToolBar(m_toolBar);
  addToolBarBreak();
  addToolBar(m_intervalToolBar);
  addDockWidget(Qt::RightDockWidgetArea, m_paletteDock);
  addDockWidget(Qt::BottomDockWidgetArea, m_logDock);

  connect(m_data1,           SIGNAL(visibilityChanged(RUnit*)), this, SLOT(onVisibilityChanged(RUnit*)));
  connect(m_database,        SIGNAL(message(QString,int,int)), this, SLOT(showMessage(QString,int,int)));
  connect(m_intervalToolBar, SIGNAL(intervalChanged()), this, SLOT(setInterval()));
  connect(m_intervalToolBar, SIGNAL(message(QString,int,int)), this, SLOT(showMessage(QString,int,int)));

  logout(false);
}

/**********************************************************************************************/

Vacuum RMainWindow :: ~RMainWindow()
{
  logout(false);
  /*m_divisionContainer   ->destroy();
  m_groupContainer      ->destroy();
  m_measureContainer    ->destroy();
  m_measure1Container   ->destroy();
  m_submissionContainer ->destroy();
  m_systemContainer     ->destroy();
  delete m_data0;
  delete m_data1;*/
}

/**********************************************************************************************/

void RMainWindow :: addTab(int flag, const char* prop, const char* title, const char* toolTip, TabAlloc alloc)
{
  int         value   = m_database->user()->property(QString::fromUtf8(prop));
  R_GUARD(value > 0, Vacuum);

  RTab*       tab     = alloc();
  QTabWidget* target  = flag & Left ? m_tabWidgetL : m_tabWidgetR;
  int         id      = target->addTab(tab, QString::fromUtf8(title));

  target->setTabToolTip(id, QString::fromUtf8(toolTip));
  if (flag & Editable)
    tab->setEditable(value == 2);
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

  widget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
  layout->insertWidget(0, widget);
}

/**********************************************************************************************/

void RMainWindow :: closeEvent(QCloseEvent* event)
{
  R_GUARD(!m_loginWidget, event->accept());

  if (showSaveDialog(R_S("Išeiti")))
    event->accept();
  else
    event->ignore();
}

/**********************************************************************************************/

void RMainWindow :: commit()
{
  if (m_database->commit())
  {
    m_results->resetBegin();
    *m_data0    = *m_data1;
    m_data1->setModified(false);
    m_results->calculator0()->update();
    m_results->resetEnd();
    showMessage(R_S("Duomenys išsaugoti."), CommitSuccess, RINFO);
  }
  else
  {
    showMessage(R_S("KLAIDA: Nepavyko išsaugoti duomenų."), CommitFailure, RERROR);
  }
}

/**********************************************************************************************/

#define R_ACTION(icon, name) new QAction(QIcon(icon), QString::fromUtf8(name), this)

void RMainWindow :: createActions()
{
  QActionGroup* stateGroup = new QActionGroup(this);

  m_importAction          = R_ACTION(":/icons/import.png",      "Importuoti");
  m_importAction->setShortcut(QKeySequence("Ctrl+I"));

  m_commitAction          = R_ACTION(":/icons/commit.png",      "Išsaugoti");
  m_commitAction->setShortcut(QKeySequence("Ctrl+S"));

  m_rollbackAction        = R_ACTION(":/icons/rollback.png",    "Atstatyti");

  m_disconnectAction      = R_ACTION(":/icons/disconnect.png",  "Atsijungti");
  m_disconnectAction->setShortcut(QKeySequence("Alt+D"));

  m_exitAction            = R_ACTION(":/icons/exit.png",        "Išeiti");
  m_exitAction->setShortcut(QKeySequence("Ctrl+Shift+X"));

  m_exterpolationAction   = R_ACTION(QString(),                 "Intrapoliuoti rezultatus");
  m_exterpolationAction->setCheckable(true);
  m_exterpolationAction->setChecked(g_settings->value("intrapolation", true).toBool());

  m_searchAction          = R_ACTION(":/icons/find_interval.png", "Mažiausios apkrovos intervalai");
  m_searchAction->setCheckable(true);
  m_searchAction->setShortcut(QKeySequence("Ctrl+F"));

  m_divisionsStateAction  = R_ACTION(":/icons/divisions.png",   "Padaliniai");
  m_divisionsStateAction->setActionGroup(stateGroup);
  m_divisionsStateAction->setCheckable(true);
  m_divisionsStateAction->setChecked(true);
  m_divisionsStateAction->setShortcut(QKeySequence("Alt+P"));

  m_measuresStateAction   = R_ACTION(":/icons/measures.png",   "Priemonės");
  m_measuresStateAction->setCheckable(true);
  m_measuresStateAction->setChecked(false);
  //m_measuresStateAction->setShortcut(QKeySequence("Alt+P"));

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

void RMainWindow :: createConnections()
{
  connect(m_disconnectAction, SIGNAL(triggered()), this, SLOT(logout()));
  connect(m_commitAction, SIGNAL(triggered()), this, SLOT(commit()));
  connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
  connect(m_exterpolationAction, SIGNAL(triggered(bool)), this, SLOT(setIntrapolationEnabled(bool)));
  connect(m_helpAction, SIGNAL(triggered()), m_help, SLOT(launch()));
  connect(m_importAction, SIGNAL(triggered()), this, SLOT(importData()));
  connect(m_rollbackAction, SIGNAL(triggered()), this, SLOT(rollback()));
  connect(m_searchAction, SIGNAL(toggled(bool)), this, SLOT(setShowSearchForm(bool)));
  connect(m_systemsStateAction, SIGNAL(toggled(bool)), this, SLOT(updateUnits()));
}

/**********************************************************************************************/

void RMainWindow :: createConnections1()
{
  (*m_data1)[RData::errorMessage]             << [=](const QString& message)
  { if (!m_importing) showMessage(message); };
  (*m_data1)[RDivision::onMeasureSet]         << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RDivision::onMeasureUnset]       << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RDivision::onSystemSet]          << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RDivision::onSystemUnset]        << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RSubmission::countChange]        << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RSubmission::date0Changed]       << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RSubmission::date1Changed]       << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RSubmission::measureChange]      << std::bind(&RResults::updateDelayed, m_results);
  (*m_data1)[RSubmission::submissionRemoval]  << std::bind(&RResults::updateDelayed, m_results);
  //(*m_data1)[RUnit::viewModeChanged]          << RSettings::updateUnitViewMode;                                               
  (*m_data1)[RUser::onSql]                    << std::bind(&RSqlEntity::exec, m_database->sqlEntity(), _1, _2, _3);
  m_data1->enableIntervalTracking();
}

/**********************************************************************************************/

void RMainWindow :: createContainers()
{
  auto submissionColor = [](const RSubmission& s) -> QBrush
  {
    return s.isValid() ? QBrush() : QBrush(QColor(0xFF, 0, 0, 0x40));
  };

  auto cd = newContainer(m_data1->divisions());
  cd->addColumn("Pavadinimas");
  cd->addColumn("Aprašymas");
  cd->addAccessor2<QString>(0, Qt::DisplayRole) >> &RDivision::identifier << &RDivision::setIdentifier;
  cd->addAccessor2<QString>(0, Qt::ToolTipRole) >> &RDivision::fullName;
  cd->addAccessor2<QString>(1, Qt::DisplayRole) >> &RDivision::name       << &RDivision::setName;
  cd->setAlloc([=]() { return new RDivision(m_data1); });

  auto cg = newContainer(m_data1->groups());
  cg->addColumn("Kryptis");
  cg->addAccessor2<QString>(0, Qt::DisplayRole) >> &RGroup::name          << &RGroup::setName;
  cg->setAlloc([=]() { return new RGroup(m_data1); });

  auto cm = newContainer(m_data1->measures());
  cm->addColumn("Pavadinimas");
  cm->addColumn("Aprašymas");
  cm->addColumn("Kryptis");
  cm->addAccessor2<QString>(0, Qt::DisplayRole) >> &RMeasure::identifier << &RMeasure::setIdentifier;
  cm->addAccessor2<QString>(0, Qt::ToolTipRole) >> &RMeasure::fullName;
  cm->addAccessor2<QString>(1, Qt::DisplayRole) >> &RMeasure::name       << &RMeasure::setName;
  cm->addAccessor2<QString>(2, Qt::DisplayRole) >> &RMeasure::groupName  << &RMeasure::setGroupName;
  cm->setAlloc([=]() { return new RMeasure(m_data1); });

  auto cu = newContainer(m_data1->submissions());
  cu->addColumn("Priemonė");
  cu->addColumn("Kiekis");
  cu->addColumn("Pradžia");
  cu->addColumn("Pabaiga");
  cu->addAccessor2<QString>(0, Qt::DisplayRole)
    >> &RSubmission::measureName << &RSubmission::setMeasureNameE;
  cu->addAccessor2<QString>(0, Qt::ToolTipRole)
    >> &RSubmission::measureFullName;
  cu->addAccessor2<int>(1, Qt::DisplayRole)
    >> &RSubmission::count << &RSubmission::setCount;
  cu->addAccessor2<QDate>(2, Qt::DisplayRole)
    >> &RSubmission::date0 << &RSubmission::setDate0E;
  cu->addAccessor2<QDate>(3, Qt::DisplayRole)
    >> &RSubmission::date1 << &RSubmission::setDate1;
  cu->addAccessor2<QBrush>(0xFE, Qt::BackgroundRole)
    >> submissionColor;
  cu->setAlloc([=]() { return new RSubmission(m_data1); });

  auto cu1 = newContainer(m_data1->submissions1(), *cu);
  cu1->addAccessor2<QString>(0, Qt::DisplayRole, true)
    >> &RSubmission::measureName << &RSubmission::setMeasure1NameE;
  cu1->setAlloc([=]() { return new RSubmission(m_data1, true); });

  auto cs = newContainer(m_data1->systems());
  cs->addColumn("Pavadinimas");
  cs->addColumn("Aprašymas");
  cs->addAccessor2<QString>(0, Qt::DisplayRole) >> &RSystem::identifier << &RSystem::setIdentifier;
  cs->addAccessor2<QString>(0, Qt::ToolTipRole) >> &RSystem::fullName;
  cs->addAccessor2<QString>(1, Qt::DisplayRole) >> &RSystem::name       << &RSystem::setName;
  cs->setAlloc([=]() { return new RSystem(m_data1); });

  m_divisionContainer     = cd;
  m_groupContainer        = cg;
  m_measureContainer      = cm;
  m_measure1Container     = newContainer(m_data1->measures1(), *cm);
  m_submissionContainer   = cu;
  m_submission1Container  = cu1;
  m_systemContainer       = cs;
}

/**********************************************************************************************/

void RMainWindow :: createInterface()
{
  QScrollArea* scrollAreaL = new QScrollArea();
  QScrollArea* scrollAreaR = new QScrollArea();

  m_splitter          = new QSplitter();
  m_widgetL           = new QWidget(m_splitter);
  m_widgetR           = new QWidget(m_splitter);
  m_layoutL           = new QVBoxLayout(m_widgetL);
  m_layoutR           = new QVBoxLayout(m_widgetR);
  m_tabWidgetL        = new QTabWidget();
  m_tabWidgetR        = new QTabWidget();

  m_layoutL->setMargin(0);
  m_layoutL->setSizeConstraint(QLayout::SetMinAndMaxSize);
  m_layoutL->setSpacing(5);
  m_layoutR->setMargin(0);
  m_layoutR->setSizeConstraint(QLayout::SetMinAndMaxSize);
  m_layoutR->setSpacing(5);

  m_widgetL->setMinimumHeight(200);
  m_widgetL->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
  m_widgetR->setMinimumHeight(200);
  m_widgetR->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

  m_tabWidgetL->setTabPosition(QTabWidget::South);
  m_tabWidgetR->setTabPosition(QTabWidget::South);

  m_layoutL->addWidget(m_tabWidgetL);
  m_layoutR->addWidget(m_tabWidgetR);

  scrollAreaL->setFrameStyle(0);
  scrollAreaL->setWidgetResizable(true);
  scrollAreaL->setWidget(m_widgetL);
  scrollAreaR->setFrameStyle(0);
  scrollAreaR->setWidgetResizable(true);
  scrollAreaR->setWidget(m_widgetR);

  m_splitter->addWidget(scrollAreaL); // m_widgetL
  m_splitter->addWidget(scrollAreaR); // m_widgetR

  createTabs();
  updateUnits();
}

/**********************************************************************************************/

void RMainWindow :: createTabs()
{
  RUser* user = m_database->user();

  addTab(Left | Editable, "mea", "Priemonės", "Paramos priemonės", [=]()
  { return new RMeasureTab(this); });

  addTab(Left | Editable, "div", "Padaliniai", "Padaliniai", [=]()
  { return new RDivisionTab(this); });

  addTab(Left | Editable, "sys", "IS", "Informacinės sistemos", [=]()
  { return new RSystemTab(this); });

  addTab(Left | Editable, "meaA", "Priemonių adm.", "Paramos priemonių administravimas", [=]()
  { return new RMeasureAdmTab(this); });

  addTab(Left | Editable, "sysA", "IS adm.", "Informacinių sistemų pasiskirstymas", [=]()
  { return new RSystemAdmTab(this); });

  addTab(Left | Editable, "sub", "Istoriniai duom.", "Istoriniai duomenys", [=]()
  { return new RSubmissionTab(this); });

  if (true)
    addLeftTab(new RPlannedTab(this), "Planuojami kiekiai", "Planuojami paramos priemonių kiekiai");

  addTab(Right, "res", "Apkrovos ir prognozės", "Individualios padalinių/sistemų apkrovos ir prognozės", [=]()
  { return new RUsageTab(this); });

  addTab(Right, "sum", "Apžvalga", "Apžvalga", [=]()
  { return new RSummaryTab(this); });

  if (user->adminAcc())
  {
    RUserTab* userTab;
    addLeftTab(userTab = new RUserTab(this), "Naudotojai", "Sistemos naudotojai");
    addRightTab(new RUserAdmTab(userTab, this), "Naud. adm.", "Sistemos naudotojų administravimas");
  }
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
    m_searchForm->getSeasonalLengths(m_results->seasonalLengths());
    m_intervalToolBar->applyInterval();
    emit searchModeChanged(true);
  }
  else
  {
    showMessage(R_S("Pirma pasirinkite teisingą paieškos intervalą."), ValidIntervalRequired, RWARNING);
  }
}

/**********************************************************************************************/

void RMainWindow :: importData()
{
  QString       fileName    = QFileDialog::getOpenFileName
      (this, QString::fromUtf8("Importuoti"),
       g_settings->value("importDir", ".").toString(),
       QString("Microsoft Excel bylos (*.xls)"));
  R_GUARD(!fileName.isNull(), Vacuum);

  RParser*      parser      = new RParser();
  RImportForm*  importForm;

  g_settings->setValue("importDir", fileName);

  connect(parser, SIGNAL(report(QString,int,int)), this,
    SLOT(showMessage(QString,int,int)));
  connect(parser, SIGNAL(log(QString,int,int)), m_logDock,
    SLOT(addMessage(QString,int,int)));

  if (parser->open(fileName))
  {
    importForm = new RImportForm(parser, m_data1);
    importForm->setImportModes(parser->guessesList());

    (*importForm)[RImportForm::importBegin] << [&]()
    {
      m_results->setUpdatesEnabled(false);
      m_importing = true;
    };

    (*importForm)[RImportForm::importEnd] << [&]()
    {
      m_importing = false;
      m_results->setUpdatesEnabled(true);
      m_data1->calculateIntervals();
      m_results->updateResults();
    };

    addStatusWidget(new RStatusWidget(importForm));
  }
  else
  {
    showMessage(R_S("Nepavyko atidaryti failo importavimui."), ImportBeginFailure, RERROR);
    delete parser;
  }
}

/**********************************************************************************************/

void RMainWindow :: loginBegin()
{
  m_loggingIn     = true;
  m_results       = new RResults(m_data0, m_data1);
}

/**********************************************************************************************/

void RMainWindow :: loginEnd(bool success)
{
  if (success)
  {
    RUser* user = m_database->user();

    RSettings::loadUnitSettings(m_data1);
    setInterfaceEnabled(true);

    // permissions
    m_importAction->setEnabled(user->property("imp"));
    m_divisionsStateAction->setEnabled(user->divisionModeAcc());
    m_systemsStateAction->setEnabled(user->systemModeAcc());

    /**/ if (!m_divisionsStateAction->isEnabled())
      m_systemsStateAction->setChecked(true);
    else if (!m_systemsStateAction->isEnabled())
      m_divisionsStateAction->setChecked(true);

    m_loginWidget   = 0; // deleted by QMainWindow::setCentralWidget
    m_data1->calculateIntervals();
    m_data1->setModified(false);
    *m_data0        = *m_data1;
    m_results->updateResults(true, true);
    m_intervalToolBar->applyInterval();

    if (m_data1->interval0().daysTo(m_data1->interval1()) < 365)
      showMessage(R_S("<b>Prognozės gali būti netikslios dėl mažo duomenų kiekio</b>"));
  }
  else
  {
    // disconnect signals to destroyed REntities
    m_data1->disconnectAll();

    m_data0->clear();
    m_data1->clear();
    delete m_results;
    m_results = 0;
  }

  m_loggingIn = false;
}

/**********************************************************************************************/

void RMainWindow :: logout(bool interactive)
{
  R_GUARD(!m_loginWidget, Vacuum);

  if (interactive && !showSaveDialog(R_S("Atsijungti")))
    return;

  RSettings::saveUnitSettings(m_data1);
  m_data1->disconnectAll();
  m_database->logout();

  m_loginWidget = new RLoginWidget(m_database);
  connect(m_loginWidget, SIGNAL(loginBegin()), this, SLOT(loginBegin()));
  connect(m_loginWidget, SIGNAL(loginEnd(bool)), this, SLOT(loginEnd(bool)));
  setInterfaceEnabled(false);
  setCentralWidget(m_loginWidget);

  m_data0->clear();
  m_data1->clear();
  delete m_results;
  m_results = 0;
}

/**********************************************************************************************/

void RMainWindow :: onSearchFormDestroyed()
{
  m_searchAction->setChecked(false);
  m_searchForm = 0;
}

/**********************************************************************************************/

void RMainWindow :: onVisibilityChanged(RUnit* unit)
{
  Q_UNUSED(unit);
  if (m_paletteDock->isMeasureModeActive())
    m_results->updateInterval();
}

/**********************************************************************************************/

void RMainWindow :: rollback()
{
  int button = QMessageBox::question(this, R_S("Atstatyti"), R_S("Ar tikrai norite atstatyti pakeitimus?"),
    QMessageBox::Yes, QMessageBox::No);
  R_GUARD(button == QMessageBox::Yes, Vacuum);

  if (m_database->rollback())
  {
    emit unitsChanged(0);
    *m_data1    = *m_data0;
    m_data1->setModified(false);
    m_results->updateResults(true, true);
    m_intervalToolBar->applyInterval();
    emit unitsChanged(currentUnits());

    showMessage(R_S("Duomenys atstatyti."), RollbackSuccess, RINFO);
  }
  else
  {
    showMessage(R_S("Duomenų atstatyti nepavyko."), RollbackFailure, RERROR);
  }
}

/**********************************************************************************************/

void RMainWindow :: setIntrapolationEnabled(bool enabled)
{
  m_results->calculator0()->setIntrapolationEnabled(enabled);
  m_results->calculator1()->setIntrapolationEnabled(enabled);

  R_GUARD(!m_loggingIn, Vacuum);
  g_settings->setValue("intrapolation", enabled);
  m_intervalToolBar->applyInterval();
}

/**********************************************************************************************/

void RMainWindow :: setInterfaceEnabled(bool enabled)
{
  if (enabled)
  {
    createInterface();
    createConnections1();
    setCentralWidget(m_splitter);
    setIntrapolationEnabled(m_exterpolationAction->isChecked());
  }
  else if (m_splitter)
  {
    delete m_splitter;
    m_splitter = 0;
  }

  m_measuresStateAction   ->setChecked(false);
  m_commitAction          ->setEnabled(enabled);
  m_disconnectAction      ->setEnabled(enabled);
  m_divisionsStateAction  ->setEnabled(enabled);
  m_exterpolationAction   ->setEnabled(enabled);
  m_importAction          ->setEnabled(enabled);
  m_rollbackAction        ->setEnabled(enabled);
  m_searchAction          ->setEnabled(enabled);
  m_systemsStateAction    ->setEnabled(enabled);

  m_intervalToolBar->setEnabled(enabled);
  m_paletteDock->setEnabled(enabled);
  m_paletteDock->setVisible(enabled);
  m_logDock->setVisible(false);
}

/**********************************************************************************************/

void RMainWindow :: setInterval()
{
  //if (m_searchForm)
  //  emit searchModeChanged();
}

/**********************************************************************************************/

void RMainWindow :: setShowSearchForm(bool show)
{
  if (!m_searchForm && show)
  {
    RStatusWidget* statusWidget;

    m_searchForm = new RSearchForm(m_results, this);

    addStatusWidget(statusWidget = new RStatusWidget(m_searchForm));
    // handle untoggle
    connect(m_searchAction, SIGNAL(toggled(bool)), statusWidget, SLOT(onCloseClicked()));
    // handle RStatusWidget's "X" button
    connect(m_searchForm, SIGNAL(destroyed()), this, SLOT(onSearchFormDestroyed()));
    connect(m_searchForm, SIGNAL(findIntervalPressed()), this, SLOT(findIntervalNow()));
    // messages
    connect(m_searchForm, SIGNAL(message(QString,int,int)), this, SLOT(showMessage(QString,int,int)));
  }
  else
  {
    m_searchAction->setChecked(false);
    m_searchForm = 0;

    emit searchModeChanged(false);
  }
}

/**********************************************************************************************/

void RMainWindow :: showMessage(const QString& message, int id, int type)
{
  int timeout = 5000 + message.size() * 40;

  RMessage* widget = new RMessage(message, timeout);

  widget->setOwner(sender());
  addStatusWidget(widget, sender());

  if (id != -1)
  {
    m_logDock->addMessage(message, id, type);
  }
}

/**********************************************************************************************/

bool RMainWindow :: showSaveDialog(const QString& title)
{
  R_GUARD(m_data1->isModified(), true);

  int button = QMessageBox::question(this, title, R_S("Ar norite išsaugoti pakeitimus?"),
    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

  switch (button)
  {
    case QMessageBox::Save:
      commit();
      return true;

    case QMessageBox::Discard:
      return true;
  }

  return false;
}

/**********************************************************************************************/

void RMainWindow :: updateUnits()
{
  if (m_paletteDock->isMeasureModeActive())
    m_results->updateInterval();
  else
    emit unitsChanged(currentUnits());
}

/**********************************************************************************************/
