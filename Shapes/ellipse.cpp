#include "ellipse.h"
#include <QtMath>

Ellipse::Ellipse(const QPointF &startPoint, DrawingArea *parent)
    : Shape(startPoint, parent)
{
    m_type = Shape::Ellipse;
}

void Ellipse::draw(QPainter &painter)
{
    painter.setPen(m_pen);
    painter.setBrush(m_brush);

    if (m_points.size() >= 2)
        painter.drawEllipse(QRectF(m_points[0], m_points[1]).normalized());
}

bool Ellipse::contains(const QPointF &point) const
{
    if (m_points.size() < 2) return false;

    QRectF rect = QRectF(m_points[0], m_points[1]).normalized();
    double rx = rect.width() / 2.0;
    double ry = rect.height() / 2.0;
    double cx = rect.center().x();
    double cy = rect.center().y();

    double dx = (point.x() - cx) / rx;
    double dy = (point.y() - cy) / ry;
    return (dx * dx + dy * dy) <= 1.0;
}

QRectF Ellipse::boundingRect() const
{
    return QRectF(m_points[0], m_points[1]).normalized();
}

double Ellipse::calculateArea() const
{
    QRectF rect = boundingRect();
    return M_PI * (rect.width() / 2.0) * (rect.height() / 2.0);
}

double Ellipse::calculatePerimeter() const
{
    QRectF rect = boundingRect();
    double a = rect.width() / 2.0;
    double b = rect.height() / 2.0;
    return M_PI * (3 * (a + b) - qSqrt((3 * a + b) * (a + 3 * b)));
}
