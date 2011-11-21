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
  QDockWidget(QString::fromUtf8("Rėžimas"), parent),
  m_mainWindow(parent)
{
  QWidget*      widget        = new QWidget(this);
  QGridLayout*  layout        = new QGridLayout(widget);
  QHBoxLayout*  layout1       = new QHBoxLayout();
  QToolButton*  divisionsMode = new QToolButton(widget);
  QToolButton*  systemsMode   = new QToolButton(widget);

  QPushButton*  checkAll      = new QPushButton(R_S("\u2611"), widget);
  QPushButton*  uncheckAll    = new QPushButton(R_S("\u2610"), widget);
  QPushButton*  inverseChecks = new QPushButton(R_S("\u25EA"), widget);

  setMaximumWidth(300);

  divisionsMode->setDefaultAction(parent->m_divisionsStateAction);
  divisionsMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  divisionsMode->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  divisionsMode->setVisible(true);

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
  layout->addWidget(systemsMode,    0, 1);
  layout->addWidget(m_filter,       1, 0, 1, 2);
  layout->addLayout(layout1,        2, 0, 1, 2);

  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  setMode(false);
  setWidget(widget);

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
    >> f(getBool) * f(&RDivision::visible)
    << f(&RDivision::setVisible) * f(setBool);
  cd->addAccessor2<QString>(0, Qt::DisplayRole)
    >> &RDivision::identifier
    << &RDivision::setIdentifier;

  auto cs = newContainer(main->data()->systems());
  cs->addColumn("Sistema");
  cs->addAccessor2<int>     (0, Qt::CheckStateRole)
    >> f(getBool) * f(&RSystem::visible)
    << f(&RSystem::setVisible) * f(setBool);
  cs->addAccessor2<QString> (0, Qt::DisplayRole)
    >> &RSystem::identifier
    << &RSystem::setIdentifier;

  m_divisionContainer = cd;
  m_systemContainer   = cs;
}

/**********************************************************************************************/

void RPaletteDock :: inverseChecks()
{
  UnitList units = selectedUnits();

  for (auto it = units.begin(); it != units.end(); ++it)
    (*it)->setVisibleRaw((*it)->visible() ^ true);

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
  RUnitPtrList*         units0    = m_mainWindow->currentUnits();
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

void RPaletteDock :: setChecked(bool checked)
{
  UnitList units = selectedUnits();

  for (auto it = units.begin(); it != units.end(); ++it)
    (*it)->setVisibleRaw(checked);

  m_mainWindow->updateUnits();
  m_model->notifyAllRowsChanged();
}

/**********************************************************************************************/

void RPaletteDock :: setMode(bool mode)
{
  R_GUARD(mode != m_mode, Vacuum);

  m_mode = mode;
  m_model->setContainer(!mode ? m_divisionContainer : m_systemContainer);
}

/**********************************************************************************************/

void RPaletteDock :: uncheckAll()
{
  setChecked(false);
}

/**********************************************************************************************/
