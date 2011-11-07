#include <QtGui/QGridLayout>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RPaletteDock.hh>
#include <QtGui/QLabel>
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

  m_filter = new QTableView(widget);
  layout->addWidget(m_filter, 1, 0, 1, 2);

  setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  setWidget(widget);
}

/**********************************************************************************************/

Vacuum RPaletteDock :: ~RPaletteDock()
{
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
}

/**********************************************************************************************/
