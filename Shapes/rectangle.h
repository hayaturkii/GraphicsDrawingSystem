#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
public:
    Rectangle(const QPointF &startPoint, DrawingArea *parent = nullptr);

    void draw(QPainter &painter) override;
    bool contains(const QPointF &point) const override;
    QRectF boundingRect() const override;
    double calculateArea() const override;
    double calculatePerimeter() const override;
};

#endif // RECTANGLE_H
