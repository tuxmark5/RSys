#include <KDChart/KDChartPieDiagram>
#include <KDChart/KDChartPolarCoordinatePlane>
#include <KDChart/KDChartWidget>
#include <QtGui/QStackedLayout>
#include <RSys/Interface/RUsageWidget.hh>

/********************************************* RS *********************************************/
/*                                        RUsageWidget                                        */
/**********************************************************************************************/

Vacuum RUsageWidget :: RUsageWidget(QWidget* parent):
  RLayerWidget(parent)
{
  setFixedHeight(200);
  layout()->addWidget(widgetAt(0));
}

/**********************************************************************************************/

Vacuum RUsageWidget :: ~RUsageWidget()
{
}

/**********************************************************************************************/

QString RUsageWidget :: nameAt(int index) const
{

}

/**********************************************************************************************/

int RUsageWidget :: numWidgets() const
{

}

/**********************************************************************************************/

QWidget* RUsageWidget :: widgetAt(int index)
{
  KDChart::Widget* widget = new KDChart::Widget(this);

  //widget.resize( 600, 600 );
  widget->setGlobalLeading( 5, 5, 5, 5 );

  QVector< double > vec0,  vec1,  vec2;

  vec0 << 1 << -4 << -3 << -2 << -1 << 0
       << 1 << 2 << 3 << 4 << 5;
  vec1 << 2 << 16 << 9 << 4 << 1 << 0
       << 1 << 4 << 9 << 16 << 25;
  vec2 << 3 << -64 << -27 << -8 << -1 << 0
       << 1 << 8 << 27 << 64 << 125;

  widget->setDataset( 0, vec0, "v0" );
  widget->setDataset( 1, vec1, "v1" );
  widget->setDataset( 2, vec2, "v2" );
  widget->setType( KDChart::Widget::Bar );

  // Draw a line around the
  // third sections
  // for example
  QPen piePen;
  piePen.setWidth( 3 );
  piePen.setColor( Qt::white );
  //widget.pieDiagram()->setPen( 2,  piePen );
  //((KDChart::PolarCoordinatePlane*)widget.coordinatePlane())->setStartPosition( 90 );

  return widget;
}

/**********************************************************************************************/
