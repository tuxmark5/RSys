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
  m_scrollArea->setWidgetResizable(true);
}

/**********************************************************************************************/

Vacuum RUsageTab :: ~RUsageTab()
{
}

/**********************************************************************************************/

void RUsageTab :: resizeEvent(QResizeEvent* event)
{
  int newWidth = qMax(m_scrollArea->viewport()->width(), 500);

  m_scrollArea->widget()->resize(newWidth, m_scrollArea->widget()->height());

  RTab::resizeEvent(event);
}

/**********************************************************************************************/
