#include "polyline.h"
#include <QtMath>

Polyline::Polyline(const QPointF &startPoint, DrawingArea *parent)
    : Shape(startPoint, parent)
{
    m_type = Shape::Polyline;
}

void Polyline::draw(QPainter &painter)
{
    painter.setPen(m_pen);
    if (m_points.size() > 1)
        painter.drawPolyline(m_points.data(), m_points.size());
}

bool Polyline::contains(const QPointF &point) const
{
    for (int i = 0; i < m_points.size() - 1; ++i) {
        QLineF line(m_points[i], m_points[i + 1]);
        QPointF v = point - line.p1();
        QPointF d = line.p2() - line.p1();
        double len = QLineF(line.p1(), line.p2()).length();
        if (len == 0) continue;
        double t = qBound(0.0, QPointF::dotProduct(v, d) / (len * len), 1.0);
        QPointF projection = line.p1() + t * d;
        if (QLineF(point, projection).length() <= 5.0)
            return true;
    }
    return false;
}

QRectF Polyline::boundingRect() const
{
    if (m_points.isEmpty()) return QRectF();
    qreal minX = m_points[0].x(), maxX = m_points[0].x();
    qreal minY = m_points[0].y(), maxY = m_points[0].y();
    for (const QPointF &p : m_points) {
        minX = qMin(minX, p.x());
        maxX = qMax(maxX, p.x());
        minY = qMin(minY, p.y());
        maxY = qMax(maxY, p.y());
    }
    return QRectF(QPointF(minX, minY), QPointF(maxX, maxY));
}

double Polyline::calculatePerimeter() const
{
    double total = 0;
    for (int i = 0; i < m_points.size() - 1; ++i)
        total += QLineF(m_points[i], m_points[i + 1]).length();
    return total;
}

void Polyline::addPoint(const QPointF &point)
{
    m_points.push_back(point);
}
