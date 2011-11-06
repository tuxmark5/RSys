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

  m_scrollArea->setWidget(widget);
  m_scrollArea->setWidgetResizable(true);
}

/**********************************************************************************************/

Vacuum RUsageTab :: ~RUsageTab()
{
}

/**********************************************************************************************/

void RUsageTab :: resizeEvent(QResizeEvent* event)
{
  m_scrollArea->widget()->resize(m_scrollArea->width(), m_scrollArea->widget()->height());

  RTab::resizeEvent(event);
}

/**********************************************************************************************/
