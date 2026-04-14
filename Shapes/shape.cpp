#include "shape.h"
#include "drawingarea.h"

Shape::Shape(const QPointF &startPoint, DrawingArea *parent)
    : m_parent(parent)
{
    m_points.append(startPoint);
    m_pen = QPen(Qt::black, 2);
    m_brush = Qt::NoBrush;
}

void Shape::addPoint(const QPointF &point)
{
    if (m_points.size() == 1)
        m_points.append(point);
    else
        m_points.last() = point;
}

void Shape::move(const QPointF &offset)
{
    for (QPointF &p : m_points)
        p += offset;
}
