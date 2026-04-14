#include "rectangle.h"

Rectangle::Rectangle(const QPointF &startPoint, DrawingArea *parent)
    : Shape(startPoint, parent)
{
    m_type = Shape::Rectangle;
    m_brush = QBrush(Qt::transparent);
}

void Rectangle::draw(QPainter &painter)
{
    painter.setPen(m_pen);
    painter.setBrush(m_brush);

    if (m_points.size() >= 2)
        painter.drawRect(QRectF(m_points[0], m_points[1]));
}

bool Rectangle::contains(const QPointF &point) const
{
    if (m_points.size() < 2) return false;
    return QRectF(m_points[0], m_points[1]).normalized().contains(point);
}

QRectF Rectangle::boundingRect() const
{
    return QRectF(m_points[0], m_points[1]).normalized();
}

double Rectangle::calculateArea() const
{
    QRectF rect = boundingRect();
    return rect.width() * rect.height();
}

double Rectangle::calculatePerimeter() const
{
    QRectF rect = boundingRect();
    return 2 * (rect.width() + rect.height());
}
