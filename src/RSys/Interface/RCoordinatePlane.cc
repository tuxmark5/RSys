#include <QtGui/QPainter>
#include <RSys/Interface/RCoordinatePlane.hh>

/********************************************* RS *********************************************/
/*                                      RCoordinatePlane                                      */
/**********************************************************************************************/

Vacuum RCoordinatePlane :: RCoordinatePlane(Chart* parent):
  Base(parent),
  m_interval0(0, 0),
  m_interval1(0, 0)
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

  if ((m_interval0.first != 0) || (m_interval0.second != 0))
    paintRect(painter, m_interval0.first, m_interval0.second, QColor(0xFF, 0xFF, 0x00, 0x60));
  if ((m_interval1.first != 0) || (m_interval1.second != 0))
    paintRect(painter, m_interval1.first, m_interval1.second, QColor(0x00, 0xFF, 0x00, 0x80));
}

/**********************************************************************************************/

void RCoordinatePlane :: paintRect(QPainter* painter, double x0, double x1, const QColor& color)
{
  QRectF      area    = logicalArea();
  double      x0A     = x0 < area.left()  ? area.left()   : x0;
  double      x1A     = x1 > area.right() ? area.right()  : x1;
  QRectF      fill    = QRectF(QPointF(x0A, area.top()), QPointF(x1A, area.bottom()));
  QPointF     pt0     = translate(fill.topLeft());
  QPointF     pt1     = translate(fill.bottomRight());

  if (fill.left() < fill.right())
    painter->fillRect(QRectF(pt0, pt1), color);
}

/**********************************************************************************************/

void RCoordinatePlane :: setFillInterval(int id, Interval interval)
{
  if (id == 0)
    m_interval0 = interval;
  else
    m_interval1 = interval;
  update();
}

/**********************************************************************************************/
