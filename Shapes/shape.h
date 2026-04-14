#ifndef SHAPE_H
#define SHAPE_H

#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QPen>
#include <QBrush>

class DrawingArea;

class Shape
{
public:
    enum ShapeType { None, Line, Rectangle, Ellipse, Polyline, Select };

    Shape(const QPointF &startPoint, DrawingArea *parent = nullptr)
    {
        m_points.append(startPoint);
        m_pen = QPen(Qt::black, 2);
        m_brush = Qt::NoBrush;
    }
    virtual ~Shape() = default;

    virtual void draw(QPainter &painter) = 0;
    virtual bool contains(const QPointF &point) const = 0;
    virtual QRectF boundingRect() const = 0;
    virtual double calculateArea() const { return 0; }
    virtual double calculatePerimeter() const { return 0; }

    virtual void move(const QPointF &offset)
    {
        for (QPointF &p : m_points)
            p += offset;
    }

    void addPoint(const QPointF &point)
    {
        if (m_points.size() == 1)
            m_points.append(point);
        else
            m_points.last() = point;
    }

    QVector<QPointF> getPoints() const { return m_points; }
    QPen getPen() const { return m_pen; }
    QBrush getBrush() const { return m_brush; }
    void setPen(const QPen &pen) { m_pen = pen; }
    void setBrush(const QBrush &brush) { m_brush = brush; }
    ShapeType getType() const { return m_type; }

    bool isSelected() const { return m_selected; }
    void setSelected(bool selected) { m_selected = selected; }

protected:
    QVector<QPointF> m_points;
    QPen m_pen;
    QBrush m_brush;
    bool m_selected = false;
    ShapeType m_type;
    DrawingArea *m_parent = nullptr;
};

#endif // SHAPE_H
