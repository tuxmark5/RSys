#include <QtGui/QGridLayout>
#include <QtGui/QToolButton>
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
  QDockWidget(QString::fromUtf8("Rėžimas"), parent)
{
  QWidget*      widget        = new QWidget(this);
  QGridLayout*  layout        = new QGridLayout(widget);
  QToolButton*  divisionsMode = new QToolButton(widget);
  QToolButton*  systemsMode   = new QToolButton(widget);

  layout->addWidget(divisionsMode, 0, 0);
  divisionsMode->setDefaultAction(parent->m_divisionsStateAction);
  divisionsMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  divisionsMode->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  divisionsMode->setVisible(true);

  layout->addWidget(systemsMode, 0, 1);
  systemsMode->setDefaultAction(parent->m_systemsStateAction);
  systemsMode->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  systemsMode->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  systemsMode->setVisible(true);

  QToolButton::connect(systemsMode, SIGNAL(toggled(bool)), this, SLOT(setMode(bool)));

  createContainers(parent);
  m_model   = new RModel1D(m_divisionContainer, widget);
  m_filter  = new RTableView(m_model, widget);
  m_filter->setStretch(true);
  layout->addWidget(m_filter, 1, 0, 1, 2);

  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  setWidget(widget);
}

/**********************************************************************************************/

Vacuum RPaletteDock :: ~RPaletteDock()
{
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

QString RPaletteDock :: modeName() const
{
  return m_mode ? "Padaliniai" : QString::fromUtf8("Informacinės sistemos");
}

/**********************************************************************************************/

void RPaletteDock :: setMode(bool mode)
{
  R_GUARD(mode != m_mode, Vacuum);

  m_mode = mode;
  m_model->setContainer(!mode ? m_divisionContainer : m_systemContainer);
}

/**********************************************************************************************/
