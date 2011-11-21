#include <KDChart/KDChartBarDiagram>
#include <KDChart/KDChartLegend>
#include <KDChart/KDChartLineAttributes> // ?
#include <KDChart/KDChartLineDiagram>
#include <RSys/Interface/RChart.hh>
#include <RSys/Interface/RCoordinatePlane.hh>
#include <RSys/Interface/RResultsModel.hh>

/********************************************* RS *********************************************/
/*                                           RChart                                           */
/**********************************************************************************************/

Vacuum RChart :: RChart(RResultsModel* model, QWidget* parent):
  KDChart::Chart(parent),
  m_model(model),
  m_diagram(0),
  m_legend(0)
{
  replaceCoordinatePlane(new RCoordinatePlane());
  setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

  m_axisX     = new KDChart::CartesianAxis();
  m_axisY     = new KDChart::CartesianAxis();

  m_axisX->setPosition(Axis::Top);
  m_axisY->setPosition(Axis::Left);
  model->setOrientation(Qt::Vertical);
}

/**********************************************************************************************/

Vacuum RChart :: ~RChart()
{
  //setDiagram(0);
  //delete m_axisX;
  //delete m_axisY;
}

/**********************************************************************************************/

void RChart :: paintEvent(QPaintEvent* event)
{
  QPainter p(this);

  //p.fillRect(QRectF(10, 10, 100, 100), QColor(0, 0x50, 0));

  Chart::paintEvent(event);
}

/**********************************************************************************************/

void RChart :: setDiagram(Diagram* diagram)
{
  if (m_diagram)
  {
    coordinatePlane()->takeDiagram(m_diagram);
    m_diagram->takeAxis(m_axisX);
    m_diagram->takeAxis(m_axisY);

    delete m_diagram;
    m_diagram = 0;
  }

  if ((m_diagram = diagram))
  {
    m_diagram->addAxis(m_axisX);
    m_diagram->addAxis(m_axisY);
    m_diagram->setModel(m_model);
    coordinatePlane()->replaceDiagram(m_diagram);
  }

  /*QModelIndex               index(m_model->index(5, 0));
  KDChart::LineAttributes   la(m_diagram->lineAttributes(index));

  la.setDisplayArea(true);
  la.setTransparency(0.5);
  m_diagram->setLineAttributes(index, la);*/
}

/**********************************************************************************************/

void RChart :: setFillRange(QDate fill0, QDate fill1)
{
  RCoordinatePlane* plane = static_cast<RCoordinatePlane*>(coordinatePlane());

  if (fill0.isValid() && fill1.isValid())
  {
    int     height      = m_diagram->numberOfAbscissaSegments();
    QDate   interval0   = m_model->headerData(0, Qt::Vertical).toDate();
    QDate   interval1   = m_model->headerData(height - 1, Qt::Vertical).toDate();
    auto    hrange      = plane->horizontalRange();
    double  scale       = (hrange.second - hrange.first) / interval0.daysTo(interval1);
    double  fillX0      = interval0.daysTo(fill0) * scale;
    double  fillX1      = interval0.daysTo(fill1) * scale;

    plane->setFillRange(fillX0, fillX1);
  }
  else
  {
    plane->setFillEnabled(false);
  }
}

/**********************************************************************************************/

void RChart :: setShowLegend(bool show)
{
  if (!m_legend && show)
  {
    m_legend  = new KDChart::Legend();
    m_legend->addDiagram(m_diagram);
    m_legend->setPosition(KDChart::Position::West);
    m_legend->setTitleText(QString());
    addLegend(m_legend);
  }
}

/**********************************************************************************************/

void RChart :: setType(ChartType type)
{
  Diagram* diagram = 0;

  switch (type)
  {
    case Bar:
      diagram = new KDChart::BarDiagram();
      break;

    case Line:
      diagram = new KDChart::LineDiagram();
      break;

    default:
      return;
  }

  if (m_legend)
    m_legend->addDiagram(diagram);
  setDiagram(diagram);
}

/**********************************************************************************************/
