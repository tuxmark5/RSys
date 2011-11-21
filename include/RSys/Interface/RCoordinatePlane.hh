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
    _T KDChart::CartesianCoordinatePlane   Base;
    _T KDChart::Chart                      Chart;

  public:
    _M double         m_fillX0;
    _M double         m_fillX1;
    _M bool           m_fillBack;

  public:
    _M Vacuum         RCoordinatePlane(Chart* parent = 0);
    _V Vacuum         ~RCoordinatePlane();
    _V void           paint(QPainter* painter);
    _M void           setFillEnabled(bool fill);
    _M void           setFillRange(double x0, double x1);
};

/**********************************************************************************************/

#endif /* RSYS_INTERFACE_RCOORDINATE_PLANE_HH */
