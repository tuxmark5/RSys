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

  public slots:
    _M void             setType(ChartType type);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RCHART_HH */