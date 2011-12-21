#include <QtCore/QSettings>
#include <QtGui/QAction>
#include <QtGui/QGridLayout>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RPaletteDock.hh>
#include <RSys/Interface/RTableView.hh>
#include <RSys/Util/RFunctional.hh>

/********************************************* RS *********************************************/
/*                                        RPaletteDock                                        */
/**********************************************************************************************/

Vacuum RPaletteDock :: RPaletteDock(RMainWindow* parent):
  QDockWidget(QString::fromUtf8("Režimas"), parent),
  m_mainWindow(parent),
  m_mode(false)
{
  QWidget*      widget        = new QWidget(this);
  QGridLayout*  layout        = new QGridLayout(widget);
  QHBoxLayout*  layout1       = new QHBoxLayout();
  QToolButton*  divisionsMode = new QToolButton(widget);
  QToolButton*  measuresMode  = new QToolButton(widget);
  QToolButton*  systemsMode   = new QToolButton(widget);

  QPushButton*  checkAll      = new QPushButton(QIcon(":/icons/check_all.png"), QString(), widget);
  QPushButton*  uncheckAll    = new QPushButton(QIcon(":/icons/check_none.png"), QString(), widget);
  QPushButton*  inverseChecks = new QPushButton(QIcon(":/icons/check_inv.png"), QString(), widget);

  checkAll->setFixedHeight(20);
  uncheckAll->setFixedHeight(20);
  inverseChecks->setFixedHeight(20);

  setMaximumWidth(300);

  divisionsMode->setDefaultAction(parent->m_divisionsStateAction);
  divisionsMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  divisionsMode->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  divisionsMode->setVisible(true);

  measuresMode->setDefaultAction(parent->m_measuresStateAction);
  measuresMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  measuresMode->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  measuresMode->setVisible(true);

  systemsMode->setDefaultAction(parent->m_systemsStateAction);
  systemsMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  systemsMode->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  systemsMode->setVisible(true);

  createContainers(parent);
  m_model   = new RModel1D(m_divisionContainer, widget);
  m_filter  = new RTableView(m_model, widget);
  m_filter->setStretch(true);

  checkAll->setMinimumWidth(20);
  uncheckAll->setMinimumWidth(20);
  inverseChecks->setMinimumWidth(20);

  layout1->addWidget(uncheckAll);
  layout1->addWidget(inverseChecks);
  layout1->addWidget(checkAll);

  layout->addWidget(divisionsMode,  0, 0);
  layout->addWidget(measuresMode,   0, 1);
  layout->addWidget(systemsMode,    0, 2);
  layout->addWidget(m_filter,       1, 0, 1, 3);
  layout->addLayout(layout1,        2, 0, 1, 3);

  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  setMode(false);
  setWidget(widget);

  connect(measuresMode, SIGNAL(toggled(bool)), this, SLOT(setMeasuresMode(bool)));
  connect(systemsMode, SIGNAL(toggled(bool)), this, SLOT(setMode(bool)));
  connect(checkAll, SIGNAL(clicked()), this, SLOT(checkAll()));
  connect(uncheckAll, SIGNAL(clicked()), this, SLOT(uncheckAll()));
  connect(inverseChecks, SIGNAL(clicked()), this, SLOT(inverseChecks()));
}

/**********************************************************************************************/

Vacuum RPaletteDock :: ~RPaletteDock()
{
}

/**********************************************************************************************/

void RPaletteDock :: checkAll()
{
  setChecked(true);
}

/**********************************************************************************************/

void RPaletteDock :: createContainers(RMainWindow* main)
{
  auto getBool = [](bool x) -> int  { return x ? 2 : 0; };
  auto setBool = [](int x)  -> bool { return x != 0; };

  auto cd = newContainer(main->data()->divisions());
  cd->addColumn("Padalinys");
  cd->addAccessor2<int>    (0, Qt::CheckStateRole)
    >> f(getBool) * f(&RDivision::isVisible)
    << f(&RDivision::setVisible) * f(setBool);
  cd->addAccessor2<QString>(0, Qt::DisplayRole)   >> &RDivision::fullName;
  cd->addAccessor2<QString>(0, Qt::ToolTipRole)   >> &RDivision::fullName;

  auto cm = newContainer(main->data()->measures());
  cm->addColumn("Priemonė");
  cm->addAccessor2<int>    (0, Qt::CheckStateRole)
    >> f(getBool) * f(&RMeasure::isVisible)
    << f(&RMeasure::setVisible) * f(setBool);
  cm->addAccessor2<QString>(0, Qt::DisplayRole)   >> &RMeasure::fullName;
  cm->addAccessor2<QString>(0, Qt::ToolTipRole)   >> &RMeasure::fullName;

  auto cs = newContainer(main->data()->systems());
  cs->addColumn("Sistema");
  cs->addAccessor2<int>     (0, Qt::CheckStateRole)
    >> f(getBool) * f(&RSystem::isVisible)
    << f(&RSystem::setVisible) * f(setBool);
  cs->addAccessor2<QString> (0, Qt::DisplayRole)  >> &RSystem::fullName;
  cs->addAccessor2<QString> (0, Qt::ToolTipRole)  >> &RSystem::fullName;

  m_divisionContainer = cd;
  m_measureContainer  = cm;
  m_systemContainer   = cs;
}

/**********************************************************************************************/

void RPaletteDock :: inverseChecks()
{
  UnitList units = selectedUnits();

  for (auto it = units.begin(); it != units.end(); ++it)
    (*it)->setVisibleRaw((*it)->isVisible() ^ true);

  m_mainWindow->updateUnits();
  m_model->notifyAllRowsChanged();
}

/**********************************************************************************************/

QString RPaletteDock :: modeName() const
{
  return m_mode ? "Padaliniai" : QString::fromUtf8("Informacinės sistemos");
}

/**********************************************************************************************/

auto RPaletteDock :: selectedUnits() const -> UnitList
{
  QItemSelectionModel*  smodel    = m_filter->selectionModel();
  QModelIndexList       selection = smodel->selectedRows();
  RUnitPtrList*         units0    = selectedUnitList();
  UnitList              units;

  if (selection.size() < 2)
  {
    for (auto it = units0->begin(); it != units0->end(); ++it)
      units.append(it->get());
  }
  else
  {
    for (auto it = selection.begin(); it != selection.end(); ++it)
      units.append(units0->at(it->row()).get());
  }

  return units;
}

/**********************************************************************************************/

RUnitPtrList* RPaletteDock :: selectedUnitList() const
{
  if (m_mainWindow->m_measuresStateAction->isChecked())
    return m_mainWindow->data()->measures()->cast<RUnitPtr>();
  return m_mainWindow->currentUnits();
}

/**********************************************************************************************/

void RPaletteDock :: setChecked(bool checked)
{
  UnitList units = selectedUnits();

  for (auto it = units.begin(); it != units.end(); ++it)
    (*it)->setVisibleRaw(checked);

  m_mainWindow->updateUnits();
  m_model->notifyAllRowsChanged();
}

/**********************************************************************************************/

void RPaletteDock :: setMeasuresMode(bool mode)
{
  m_mainWindow->m_divisionsStateAction->setEnabled(!mode);
  m_mainWindow->m_systemsStateAction->setEnabled(!mode);

  if (mode)
    m_model->setContainer(m_measureContainer);
  else
    m_model->setContainer(!m_mode ? m_divisionContainer : m_systemContainer);
}

/**********************************************************************************************/

void RPaletteDock :: setMode(bool mode)
{
  m_mode = mode;
  m_model->setContainer(!mode ? m_divisionContainer : m_systemContainer);
}

/**********************************************************************************************/

void RPaletteDock :: uncheckAll()
{
  setChecked(false);
}

/**********************************************************************************************/
