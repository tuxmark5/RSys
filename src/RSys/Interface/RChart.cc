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

  m_higlight[0] = RInterval();
  m_higlight[1] = RInterval();
  m_axisX       = new KDChart::CartesianAxis();
  m_axisY       = new KDChart::CartesianAxis();

  m_axisX->setPosition(Axis::Top);
  m_axisY->setPosition(Axis::Left);
  model->setOrientation(Qt::Vertical);

  connect(model, SIGNAL(modelReset()), this, SLOT(updateHighlight()));
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

void RChart :: setFillRange(int id, QDate fill0, QDate fill1)
{
  m_higlight[id] = RInterval(fill0, fill1);
  updateHighlight();
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
      diagram     = new KDChart::BarDiagram();
      m_recordMod = 0;
      break;

    case Line:
      diagram     = new KDChart::LineDiagram();
      m_recordMod = 1;
      break;

    default:
      return;
  }

  if (m_legend)
    m_legend->addDiagram(diagram);
  setDiagram(diagram);
}

/**********************************************************************************************/

auto RChart :: translate() -> Transform
{
  int     numRecords  = m_model->rowCount();
  R_GUARD(numRecords > 0, Transform());
  QDate   interval0   = m_model->headerData(0, Qt::Vertical).toDate();
  QDate   interval1   = m_model->headerData(numRecords, Qt::Vertical).toDate();
  double  scale       = double(numRecords) / interval0.daysTo(interval1);

  return Transform(interval0, scale);
}

/**********************************************************************************************/

void RChart :: updateHighlight()
{
  RCoordinatePlane* plane       = static_cast<RCoordinatePlane*>(coordinatePlane());
  Transform         transform   = translate();
  R_GUARD(transform.first.isValid(), Vacuum);

  auto trans = [&](RInterval& interval) -> DoublePair
  {
    return DoublePair(transform.first.daysTo(std::get<0>(interval)) * transform.second,
                      transform.first.daysTo(std::get<1>(interval)) * transform.second);
  };

  for (int i = 0; i < 2; i++)
  {
    RInterval&  interval = m_higlight[i];

    if (std::get<0>(interval).isValid() && std::get<1>(interval).isValid())
      plane->setFillInterval(i, trans(m_higlight[i]));
    else
      plane->setFillInterval(i, DoublePair(0, 0));
  }
}

/**********************************************************************************************/
