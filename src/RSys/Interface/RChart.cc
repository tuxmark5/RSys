#include <KDChart/KDChartBarDiagram>
#include <KDChart/KDChartLegend>
#include <KDChart/KDChartLineDiagram>
#include <RSys/Interface/RChart.hh>
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
  m_axisX     = new KDChart::CartesianAxis();
  m_axisY     = new KDChart::CartesianAxis();
  //m_legend    = new KDChart::Legend();

  m_axisX->setPosition(Axis::Top);
  m_axisY->setPosition(Axis::Left);
  //m_legend->setPosition(KDChart::Position::North);

  model->setOrientation(Qt::Vertical);

  //addLegend(m_legend);
}

/**********************************************************************************************/

Vacuum RChart :: ~RChart()
{
  //setDiagram(0);
  //delete m_axisX;
  //delete m_axisY;
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

  setDiagram(diagram);
}

/**********************************************************************************************/
