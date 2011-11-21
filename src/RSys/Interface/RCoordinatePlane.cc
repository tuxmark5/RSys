#include <QtGui/QPainter>
#include <RSys/Interface/RCoordinatePlane.hh>

/********************************************* RS *********************************************/
/*                                      RCoordinatePlane                                      */
/**********************************************************************************************/

Vacuum RCoordinatePlane :: RCoordinatePlane(Chart* parent):
  Base(parent),
  m_fillX0(0.0),
  m_fillX1(10.0),
  m_fillBack(false)
{
}

/**********************************************************************************************/

Vacuum RCoordinatePlane :: ~RCoordinatePlane()
{
}

/**********************************************************************************************/

void RCoordinatePlane :: paint(QPainter* painter)
{
  Base::paint(painter);

  R_GUARD(m_fillBack, Vacuum);
  QRectF      area    = logicalArea();
  double      x0      = m_fillX0 < area.left()  ? area.left()   : m_fillX0;
  double      x1      = m_fillX1 > area.right() ? area.right()  : m_fillX1;
  QRectF      fill    = QRectF(QPointF(x0, area.top()), QPointF(x1, area.bottom()));
  QPointF     pt0     = translate(fill.topLeft());
  QPointF     pt1     = translate(fill.bottomRight());

  painter->fillRect(QRectF(pt0, pt1), QColor(0xFF, 0xFF, 0x00, 0x60));
}

/**********************************************************************************************/

void RCoordinatePlane :: setFillEnabled(bool fill)
{
  m_fillBack = fill;
}

/**********************************************************************************************/

void RCoordinatePlane :: setFillRange(double x0, double x1)
{
  m_fillX0    = x0;
  m_fillX1    = x1;
  m_fillBack  = true;
  update();
}

/**********************************************************************************************/
