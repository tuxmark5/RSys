#include <QtGui/QAction>
#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>
#include <RSys/Core/RData.hh>
#include <RSys/Core/RDivision.hh>
#include <RSys/Core/RSystem.hh>
#include <RSys/Interface/RMainWindow.hh>
#include <RSys/Interface/RUsageTab.hh>
#include <RSys/Interface/RUsageWidget.hh>

/********************************************* RS *********************************************/
/*                                         RUsageTab                                          */
/**********************************************************************************************/

Vacuum RUsageTab :: RUsageTab(RMainWindow* parent):
  RTab(R_S("Individualios apkrovos ir prognozės"), parent),
  m_scrollArea(new QScrollArea(this)),
  m_systemsMode(false)
{
  RData::connect(parent->data(), SIGNAL(elementChanged(RElement*,int)),
    this, SLOT(updateElement(RElement*,int)));
  QAction::connect(parent->systemsStateAction(), SIGNAL(toggled(bool)),
    this, SLOT(setMode(bool)));

  m_innerLayout = new QVBoxLayout();
  m_innerLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
  //m_innerLayout->setSpacing(0);

  m_innerWidget = new QWidget();
  m_innerWidget->setLayout(m_innerLayout);

  m_scrollArea->setWidget(m_innerWidget);
  layout()->addWidget(m_scrollArea);

  m_results     = parent->results();
  m_divisions   = parent->data()->divisions()->cast<RUnit*>();
  m_systems     = parent->data()->systems()->cast<RUnit*>();
  m_current     = m_divisions;
  setMode(false);
}

/**********************************************************************************************/

Vacuum RUsageTab :: ~RUsageTab()
{
}

/**********************************************************************************************/

void RUsageTab :: destroyWidgets()
{
  int count = m_innerLayout->count();

  m_innerWidget->setVisible(false);
  remove0(0, count);
  m_innerWidget->setVisible(true);
}

/**********************************************************************************************/

void RUsageTab :: insert1(int i0, int i1)
{
  for (; i0 < i1; i0++)
  {
    RUnit*        unit    = m_current->at(i0);
    RUsageWidget* widget  = new RUsageWidget(unit, m_results);

    m_innerLayout->insertWidget(i0, widget);
  }
}

/**********************************************************************************************/

void RUsageTab :: populateWidgets()
{
  m_innerWidget->setVisible(false);

  for (auto it = m_current->begin(); it != m_current->end(); ++it)
  {
    RUsageWidget* widget = new RUsageWidget(*it, m_results);

    m_innerLayout->addWidget(widget);
    widget->setVisible((*it)->visible());
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
    widget->deleteLater();
  }

  return true;
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

void RUsageTab :: setMode(bool systems)
{
  destroyWidgets();
  m_current->removeObserver(this);
  m_current       = systems ? m_systems : m_divisions;
  m_systemsMode   = systems;
  m_current->addObserver(this);
  populateWidgets();
}

/**********************************************************************************************/

void RUsageTab :: updateElement(RElement* element, int updateType)
{
  RUnit*          unit    = static_cast<RUnit*>(element);
  int             index   = m_current->indexOf(unit);
  R_GUARD(index != -1, Vacuum);
  RUsageWidget*   widget  = qobject_cast<RUsageWidget*>(m_innerLayout->itemAt(index)->widget());
  R_GUARD(widget, Vacuum);

  switch (updateType)
  {
    case RData::TitleOrName:
      widget->updateHeader();
      break;

    case RData::Visibility:
      widget->setVisible(unit->visible());
      break;
  }
}

/**********************************************************************************************/
