#include "drawingarea.h"
#include "Shapes/line.h"
#include "Shapes/rectangle.h"
#include "Shapes/ellipse.h"
#include "Shapes/polyline.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFile>
#include <QDataStream>

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

DrawingArea::~DrawingArea()
{
    clear();
}

void DrawingArea::setCurrentShape(Shape::ShapeType shapeType)
{
    if (m_currentShape) {
        if (m_currentShape->getPoints().size()>=2)
            m_shapes.append(m_currentShape);
         else
            delete m_currentShape;

        m_currentShape = nullptr;
    }

    m_currentMode = shapeType;
    clearSelection();
    update();
}

void DrawingArea::clear()
{
    if (m_currentShape) {
        delete m_currentShape;
        m_currentShape = nullptr;
    }

    qDeleteAll(m_shapes);
    m_shapes.clear();
    clearSelection();
    update();
}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (Shape* shape : m_shapes)
        shape->draw(painter);

    if (m_currentShape)
        m_currentShape->draw(painter);

    if (m_selectedShape) {
        painter.save();
        painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(m_selectedShape->boundingRect());
        painter.restore();
    }
}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button()!=Qt::LeftButton) return;

    if (m_currentMode==Shape::Select) {
        clearSelection();
        for (int i=m_shapes.size()-1; i>=0; --i) {
            if (m_shapes[i]->contains(event->pos())) {
                m_selectedShape = m_shapes[i];
                m_selectedShape->setSelected(true);
                emit shapeSelected(m_selectedShape);
                break;
            }
        }
        update();
    } else { //drawing line / ellipse / rectagnle
        if (!m_currentShape)
            m_currentShape = createShape(m_currentMode, event->pos());
        else if (m_currentMode==Shape::Polyline) { //drawing polyline
            static_cast<Polyline*>(m_currentShape)->addPoint(event->pos());
            update();
        }
    }
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if (m_currentShape && m_currentMode!=Shape::Polyline) {
        m_currentShape->addPoint(event->pos());
        update();
    }
}

void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_currentShape && m_currentMode!=Shape::Polyline) {
        if (m_currentShape->getPoints().size()>=2) {
            m_shapes.append(m_currentShape);
            m_currentShape = nullptr;
            update();
        }
    }
}

Shape* DrawingArea::createShape(Shape::ShapeType type, const QPointF &startPoint)
{
    switch (type) {
    case Shape::Line: return new Line(startPoint, this);
    case Shape::Rectangle: return new Rectangle(startPoint, this);
    case Shape::Ellipse: return new Ellipse(startPoint, this);
    case Shape::Polyline: return new Polyline(startPoint, this);
    default: return nullptr;
    }
}

void DrawingArea::clearSelection()
{
    if (m_selectedShape) {
        m_selectedShape->setSelected(false);
        m_selectedShape = nullptr;
        emit shapeSelected(nullptr);
    }
}

bool DrawingArea::saveToFile(const QString &fileName)
{
    if (m_currentShape && m_currentShape->getPoints().size()>=2) {
        m_shapes.append(m_currentShape);
        m_currentShape = nullptr;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QDataStream out(&file);

    for (Shape* shape : m_shapes)
        out << quint32(shape->getType()) << shape->getPen() << shape->getBrush() << shape->getPoints();

    return true;
}

bool DrawingArea::loadFromFile(const QString &fileName)
{
    clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QDataStream in(&file);

    while (!in.atEnd()) {
        quint32 type;
        QPen pen;
        QBrush brush;
        QVector<QPointF> points;

        in >> type >> pen >> brush >> points;

        if (points.isEmpty()) continue;

        Shape *shape = createShape(static_cast<Shape::ShapeType>(type), points.first());
        if (!shape) continue;

        shape->setPen(pen);
        shape->setBrush(brush);

        if (type == Shape::Polyline) {
            static_cast<Polyline*>(shape)->setPoints(points);
        } else if (points.size() > 1) {
            shape->addPoint(points.last());
        }

        m_shapes.append(shape);
    }

    update();
    return true;
}
