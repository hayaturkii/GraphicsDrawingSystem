#ifndef POLYLINE_H
#define POLYLINE_H

#include "shape.h"

class Polyline : public Shape
{
public:
    Polyline(const QPointF &startPoint, DrawingArea *parent = nullptr);

    void draw(QPainter &painter) override;
    bool contains(const QPointF &point) const override;
    QRectF boundingRect() const override;
    double calculatePerimeter() const override;
    void addPoint(const QPointF &point);
    void setPoints(const QVector<QPointF>& points) { m_points = points; }
};

#endif // POLYLINE_H
