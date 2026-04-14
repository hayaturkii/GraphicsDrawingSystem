#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QVector>
#include "Shapes/shape.h"

class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = nullptr);
    ~DrawingArea();

    void setCurrentShape(Shape::ShapeType shapeType);
    void clear();
    bool saveToFile(const QString &fileName);
    bool loadFromFile(const QString &fileName);
    Shape* getSelectedShape() const { return m_selectedShape; }

signals:
    void shapeSelected(Shape* shape);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QVector<Shape*> m_shapes;
    Shape *m_currentShape = nullptr;
    Shape *m_selectedShape = nullptr;
    Shape::ShapeType m_currentMode = Shape::Select;

    Shape* createShape(Shape::ShapeType type, const QPointF &startPoint);
    void completeDrawing();
    void clearSelection();
};

#endif // DRAWINGAREA_H
