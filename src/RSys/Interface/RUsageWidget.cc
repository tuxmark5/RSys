#include <KDChart/KDChartBarDiagram>
#include <KDChart/KDChartCartesianAxis>
#include <KDChart/KDChartLineDiagram>
#include <KDChart/KDChartPieDiagram>
#include <KDChart/KDChartPolarCoordinatePlane>
#include <KDChart/KDChartWidget>
#include <QtGui/QStackedLayout>
#include <QtGui/QStandardItemModel>
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
using namespace KDChart;
#include <KDChart/KDChartDataValueAttributes>
#include <KDChart/KDChartGridAttributes>
#include <QtGui/QPainter>
#include <KDChart/KDChartPaintContext>
class Axis: public CartesianAxis //AbstractAxis
{
  public:
   Axis(AbstractCartesianDiagram* parent = 0):
     CartesianAxis(parent) { }

   void paintCtx(PaintContext* ctx)
   {
     CartesianCoordinatePlane* plane = dynamic_cast<CartesianCoordinatePlane*>(diagram()->coordinatePlane());
     DataDimensionsList ddl = plane->gridDimensionsList();

     DataDimension dimX = ddl.first(); //AbstractGrid::adjustedLowerUpperRange( ddl.first(), true, true );

     //ctx->

     ctx->painter()->restore();
     QPointF pt1(0, 0);
     QPointF pt2(5, -50);
     pt1 = plane->translate(pt1);
     pt2 = plane->translate(pt2);

     for (qreal x = dimX.start; x < dimX.end; x += 1)
     {
       ctx->painter()->drawRect(QRectF(pt1, pt2));
     }
     ctx->painter()->save();
     //ddl.r
     //diagram()->gre
     //parent()->c
     //for ()

   }

   QSize sizeHint() const { return QSize(); }
   QSize minimumSize() const { return QSize(); }
   QSize maximumSize() const { return QSize(); }
   /*QSize maximumSize() const { return QSize(); }*/
};

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

  /*widget->setDataset( 0, vec0, "v0" );
  widget->setDataset( 1, vec1, "v1" );
  widget->setDataset( 2, vec2, "v2" );
  widget->setType( KDChart::Widget::Line );*/

  QStringList labels;
  labels << "2011-01-02"
         << "2011-02-02"
         << "2011-03-02"
         << "2011-04-02"
         << "2011-05-02"
         << "2011-06-02";

  QStandardItemModel* model = new QStandardItemModel();

  for (auto it = vec2.begin(); it != vec2.end(); ++it)
  {
    QStandardItem* item = new QStandardItem();

    item->setData(*it, Qt::DisplayRole);
    model->appendRow(item);
  }

  LineDiagram*    line        = new LineDiagram(); line->setModel(model);
  //CartesianAxis*  bottomAxis  = new CartesianAxis(line);
  Axis*           bottomAxis  = new Axis(line);
  CartesianAxis*  leftAxis    = new CartesianAxis(line);


  //line->setReferenceDiagram();



  TextAttributes ta = bottomAxis->textAttributes();

  //ta.setRotation(90);
  //ta.set
  bottomAxis->setTextAttributes(ta);

  bottomAxis->setLabels(labels);
  bottomAxis->setPosition(CartesianAxis::Top);
  bottomAxis->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

  leftAxis->setPosition(CartesianAxis::Left);
  //leftAxis->

  RulerAttributes       ra = bottomAxis->rulerAttributes();
  DataValueAttributes   da = line->dataValueAttributes();

  da.setDataLabel("Z");
  //da.setTextAttributes();
  da.setVisible(true);

  line->setDataValueAttributes(da);



  //ra.setTickMarkPen(3.5, QPen(Qt::red));
  //ra.setMajorTickMarkPen(QPen(Qt::green));
  //ra.setLabelMargin(0);
  bottomAxis->setRulerAttributes(ra);

  line->addAxis(bottomAxis);
  line->addAxis(leftAxis);
  widget->coordinatePlane()->replaceDiagram(line);

  CartesianCoordinatePlane* plane = dynamic_cast<CartesianCoordinatePlane*>(line->coordinatePlane());
  GridAttributes ga = plane->gridAttributes(Qt::Horizontal);

  ga.setGridStepWidth(2);
  plane->setGridAttributes(Qt::Horizontal, ga);



  widget->setGlobalLeading(0, -5, 0, 0);



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
