#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape
{
public:
    Line(const QPointF &startPoint, DrawingArea *parent = nullptr);

    void draw(QPainter &painter) override;
    bool contains(const QPointF &point) const override;
    QRectF boundingRect() const override;
    double calculatePerimeter() const override;
};

#endif // LINE_H
