#include <QtGui/QGridLayout>
#include <QtGui/QToolButton>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RModel1D.hh>
#include <RSys/Interface/RPaletteDock.hh>
#include <RSys/Interface/RTableView.hh>

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
  auto cd = newContainer(main->data()->divisions());
  cd->addColumn<bool,     FN(&RDivision::visible),    FN(&RDivision::setVisible)>     ("Rodyti");
  cd->addColumn<QString,  FN(&RDivision::identifier), FN(&RDivision::setIdentifier)>  ("Padalinys");

  auto cs = newContainer(main->data()->systems());
  cs->addColumn<bool,     FN(&RSystem::visible),      FN(&RSystem::setVisible)>       ("Rodyti");
  cs->addColumn<QString,  FN(&RSystem::identifier),   FN(&RSystem::setIdentifier)>    ("Sistema");

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
