#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape
{
public:
    Ellipse(const QPointF &startPoint, DrawingArea *parent = nullptr);

    void draw(QPainter &painter) override;
    bool contains(const QPointF &point) const override;
    QRectF boundingRect() const override;
    double calculateArea() const override;
    double calculatePerimeter() const override;
};

#endif // ELLIPSE_H
