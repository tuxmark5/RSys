#ifndef RSYS_INTERFACE_RCHART_HH
#define RSYS_INTERFACE_RCHART_HH

/**********************************************************************************************/
#include <KDChart/KDChartChart>
#include <RSys/RSys.hh>
/**********************************************************************************************/
namespace KDChart
{
  class AbstractCartesianDiagram;
  class CartesianAxis;
  class CartesianCoordinatePlane;
  class Legend;
}
/********************************************* RS *********************************************/
/*                                           RChart                                           */
/**********************************************************************************************/

class RChart: public KDChart::Chart
{
  Q_OBJECT

  public:
    _E ChartType
    {
      Bar,
      Line
    };

  public:
    _T KDChart::CartesianAxis               Axis;
    _T KDChart::CartesianCoordinatePlane    CoordinatePlane;
    _T KDChart::Chart                       Chart;
    _T KDChart::AbstractCartesianDiagram    Diagram;
    _T KDChart::Legend                      Legend;

  public:
    _M RResultsModel*   m_model;
    _M Diagram*         m_diagram;
    _M Axis*            m_axisX;
    _M Axis*            m_axisY;
    _M Legend*          m_legend;

  public:
    _M Vacuum           RChart(RResultsModel* model, QWidget* parent = 0);
    _V Vacuum           ~RChart();
    _M void             setDiagram(Diagram* diagram);
    _M void             setDiagramType(Diagram* diagram);
    _M void             setFillRange(QDate date0, QDate date1);

  public slots:
    _M void             setShowLegend(bool show);
    _M void             setType(ChartType type);

  protected:
    _M void             paintEvent(QPaintEvent* event);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RCHART_HH */
