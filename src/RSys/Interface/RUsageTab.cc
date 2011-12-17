#include <QtGui/QAction>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Interface/RMainMenuBar.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RUsageTab.hh>
#include <RSys/Interface/RUsageWidget.hh>
#include <RSys/Logic/RResults.hh>

/********************************************* RS *********************************************/
/*                                         RUsageTab                                          */
/**********************************************************************************************/

Vacuum RUsageTab :: RUsageTab(RMainWindow* parent):
  RTab(R_S("Individualios apkrovos ir prognozės"), parent),
  m_mainWindow(parent),
  m_scrollArea(new QScrollArea(this)),
  m_results(parent->results()),
  m_units(0),
  m_defaultMode(RUsageWidget::Usage1 | RUsageWidget::Hours | RUsageWidget::Bar)
{
  QMenu* menu = RUsageWidget::createModeMenu(this, SLOT(setMode()), m_defaultMode);

  menu->setTitle(R_S("Pateikti visus rezultatus"));
  parent->menuBar()->m_viewMenu->addSeparator()->setParent(this);
  parent->menuBar()->m_viewMenu->addMenu(menu)->setParent(this);

  connect(parent->data(), SIGNAL(elementChanged(RElement*,int)),
    this, SLOT(updateElement(RElement*,int)));
  connect(parent->data(), SIGNAL(visibilityChanged(RUnit*)),
    this, SLOT(updateElementVisibility(RUnit*)));
  connect(parent, SIGNAL(unitsChanged(RUnitPtrList*)),
    this, SLOT(setUnits(RUnitPtrList*)));
  connect(m_mainWindow, SIGNAL(searchModeChanged(bool)),
    this, SLOT(setIntervalSearchEnabled(bool)));

  m_innerLayout = new QVBoxLayout();
  m_innerLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);

  m_innerWidget = new QWidget();
  m_innerWidget->setLayout(m_innerLayout);

  m_scrollArea->setWidget(m_innerWidget);
  layout()->addWidget(m_scrollArea);
}

/**********************************************************************************************/

Vacuum RUsageTab :: ~RUsageTab()
{
  if (m_units)
    m_units->removeObserver(this);
}

/**********************************************************************************************/

void RUsageTab :: clearUnits()
{
  R_GUARD(m_units, Vacuum);

  int count = m_innerLayout->count();

  m_innerWidget->setVisible(false);
  remove0(0, count);
  m_innerWidget->setVisible(true);
}

/**********************************************************************************************/

RUsageWidget* RUsageTab :: createWidget(RUnit* unit)
{
  int           mode    = unit->viewMode() != -1 ? unit->viewMode() : m_defaultMode;
  RUsageWidget* widget  = new RUsageWidget(mode, unit, m_results);

  return widget;
}

/**********************************************************************************************/

void RUsageTab :: insert1(int i0, int i1)
{
  for (; i0 < i1; i0++)
  {
    RUnit*        unit    = m_units->at(i0);
    RUsageWidget* widget  = createWidget(unit);

    m_innerLayout->insertWidget(i0, widget);
  }
}

/**********************************************************************************************/

void RUsageTab :: populateUnits()
{
  R_GUARD(m_units, Vacuum);

  m_innerWidget->setVisible(false);

  for (auto it = m_units->begin(); it != m_units->end(); ++it)
  {
    RUsageWidget* widget = createWidget(*it);

    m_innerLayout->addWidget(widget);
    widget->setVisible((*it)->isVisible());
  }

  m_innerWidget->setVisible(true);
  m_innerLayout->update();
}

/**********************************************************************************************/

bool RUsageTab :: remove0(int i0, int i1)
{
  for (int i = i1 - 1; i >= i0; i--)
  {
    QLayoutItem*  item    = m_innerLayout->itemAt(i);
    QWidget*      widget  = item->widget();

    m_innerLayout->removeItem(item);
    delete widget;
  }

  return true;
}

/**********************************************************************************************/

void RUsageTab :: resetObservable0()
{
  clearUnits();
}

/**********************************************************************************************/

void RUsageTab :: resetObservable()
{
  populateUnits();
}

/**********************************************************************************************/

void RUsageTab :: resizeEvent(QResizeEvent* event)
{
  QWidget*  viewport  = m_scrollArea->viewport();
  int       newWidth  = qMax(viewport->width(), m_innerWidget->minimumWidth());

  m_innerWidget->setFixedWidth(newWidth);
  RTab::resizeEvent(event);
}

/**********************************************************************************************/

void RUsageTab :: setIntervalSearchEnabled(bool enabled)
{
  if (enabled)
  {
    m_results->findLowestUsageIntervals();
  }

  for (int i = 0; i < m_innerLayout->count(); i++)
    if (RUsageWidget* widget = qobject_cast<RUsageWidget*>(m_innerLayout->itemAt(i)->widget()))
      widget->setIntervalSearchEnabled(enabled);
}

/**********************************************************************************************/

void RUsageTab :: setMode()
{
  if (QAction* action = qobject_cast<QAction*>(sender()))
  {
    int modifier = action->data().toInt();

    m_defaultMode &= modifier >> 16;
    m_defaultMode |= modifier &  0xFFFF;

    for (int i = 0; i < m_innerLayout->count(); i++)
      if (RUsageWidget* widget = qobject_cast<RUsageWidget*>(m_innerLayout->itemAt(i)->widget()))
        widget->modifyMode(modifier);
  }
}

/**********************************************************************************************/

void RUsageTab :: setUnits(RUnitPtrList* units)
{
  if (m_units)
  {
    clearUnits();
    m_units->removeObserver(this);
  }

  if ((m_units = units))
  {
    populateUnits();
    m_units->addObserver(this);
  }
}

/**********************************************************************************************/

void RUsageTab :: updateElement(RElement* element, int updateType)
{
  Q_UNUSED(updateType);
  if (RUsageWidget* widget = widgetForElement(element))
    widget->updateHeader();
}

/**********************************************************************************************/

void RUsageTab :: updateElementVisibility(RUnit* unit)
{
  if (RUsageWidget* widget = widgetForElement(unit))
    widget->setVisible(unit->isVisible());
}

/**********************************************************************************************/

RUsageWidget* RUsageTab :: widgetForElement(RElement* element)
{
  RUnit*          unit    = static_cast<RUnit*>(element);
  int             index   = m_units->indexOf(unit);
  R_GUARD(index != -1, 0);

  return qobject_cast<RUsageWidget*>(m_innerLayout->itemAt(index)->widget());
}

/**********************************************************************************************/
