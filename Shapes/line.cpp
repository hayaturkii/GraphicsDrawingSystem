#include "line.h"
#include <QtMath>

Line::Line(const QPointF &startPoint, DrawingArea *parent)
    : Shape(startPoint, parent)
{
    m_type = Shape::Line;
}

void Line::draw(QPainter &painter)
{
    painter.setPen(m_pen);
    if (m_points.size() >= 2)
        painter.drawLine(m_points[0], m_points[1]);
}

bool Line::contains(const QPointF &point) const
{
    QLineF line(m_points[0], m_points[1]);
    QLineF toPoint(m_points[0], point);

    qreal distance = fabs(QLineF::fromPolar(1, line.angle()).dy() * (point.x() - m_points[0].x()) -
                          QLineF::fromPolar(1, line.angle()).dx() * (point.y() - m_points[0].y())) /
                     line.length();

    return distance < 5.0;
}

QRectF Line::boundingRect() const
{
    return QRectF(m_points[0], m_points[1]).normalized();
}

double Line::calculatePerimeter() const
{
    if (m_points.size() < 2) return 0;
    return QLineF(m_points[0], m_points[1]).length();
}
