#include <QtGui/QScrollArea>
#include <QtGui/QVBoxLayout>
#include <RSys/Interface/RUsageTab.hh>
#include <RSys/Interface/RUsageWidget.hh>

/********************************************* RS *********************************************/
/*                                         RUsageTab                                          */
/**********************************************************************************************/

Vacuum RUsageTab :: RUsageTab(QWidget* parent):
  RTab(QString::fromUtf8("Apkrovos ir prognozės"), parent),
  m_scrollArea(new QScrollArea(this))
{
  this->layout()->addWidget(m_scrollArea);

  QWidget*      widget = new QWidget();
  QVBoxLayout*  layout = new QVBoxLayout(widget);

  layout->addWidget(new RUsageWidget());
  layout->addWidget(new RUsageWidget());
  layout->addWidget(new RUsageWidget());
  layout->addWidget(new RUsageWidget());
  layout->addWidget(new RUsageWidget());
  layout->addWidget(new RUsageWidget());
  layout->addWidget(new RUsageWidget());
  layout->addWidget(new RUsageWidget());
  layout->setSpacing(0);

  m_scrollArea->setWidget(widget);
}

/**********************************************************************************************/

Vacuum RUsageTab :: ~RUsageTab()
{
}

/**********************************************************************************************/

void RUsageTab :: resizeEvent(QResizeEvent* event)
{
  QWidget*  viewport  = m_scrollArea->viewport();
  QWidget*  widget    = m_scrollArea->widget();
  int       newWidth  = qMax(viewport->width(), 500);

  RTab::resizeEvent(event);

  widget->resize(newWidth, widget->height());
}

/**********************************************************************************************/
