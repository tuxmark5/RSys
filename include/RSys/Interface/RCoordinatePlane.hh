#ifndef RSYS_INTERFACE_RCOORDINATE_PLANE_HH
#define RSYS_INTERFACE_RCOORDINATE_PLANE_HH

/**********************************************************************************************/
#include <KDChart/KDChartCartesianCoordinatePlane>
#include <RSys/RSys.hh>
/********************************************* RS *********************************************/
/*                                      RCoordinatePlane                                      */
/**********************************************************************************************/

class RCoordinatePlane: public KDChart::CartesianCoordinatePlane
{
  Q_OBJECT

  public:
    _T KDChart::CartesianCoordinatePlane    Base;
    _T KDChart::Chart                       Chart;
    _T QPair<double, double>                Interval;

  public:
    _M Interval       m_interval0;
    _M Interval       m_interval1;

  public:
    _M Vacuum         RCoordinatePlane(Chart* parent = 0);
    _V Vacuum         ~RCoordinatePlane();
    _V void           paint(QPainter* painter);
    _M void           setFillInterval(int id, Interval interval0);

  protected:
    _M void           paintRect(QPainter* painter, double x0, double x1, const QColor& color);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RCOORDINATE_PLANE_HH */
