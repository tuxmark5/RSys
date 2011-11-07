#include <QtGui/QVBoxLayout>
#include <RSys/Interface/RUsageTab.hh>
#include <RSys/Interface/RUsageWidget.hh>

/********************************************* RS *********************************************/
/*                                         RUsageTab                                          */
/**********************************************************************************************/

Vacuum RUsageTab :: RUsageTab(QWidget* parent):
  QScrollArea(parent)
{
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

  setWidget(widget);
  //setWidgetResizable(true);
}

/**********************************************************************************************/

Vacuum RUsageTab :: ~RUsageTab()
{
}

/**********************************************************************************************/

void RUsageTab :: resizeEvent(QResizeEvent* event)
{
  int newWidth = qMax(viewport()->width(), 500);

  widget()->resize(newWidth, widget()->height());

  QScrollArea::resizeEvent(event);
}

/**********************************************************************************************/
