#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "movedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawingArea = ui->drawingArea;
    connect(drawingArea, &DrawingArea::shapeSelected, this, &MainWindow::showShapeProperties);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFileNew_triggered()
{
    drawingArea->clear();
}

void MainWindow::on_actionFileOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Drawing", "", "Drawing Files (*.draw)");
    if (!fileName.isEmpty() && !drawingArea->loadFromFile(fileName)) {
        QMessageBox::warning(this, "Error", "Could not open file");
    }
}

void MainWindow::on_actionFileSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Drawing", "", "Drawing Files (*.draw)");
    if (!fileName.isEmpty() && !drawingArea->saveToFile(fileName)) {
        QMessageBox::warning(this, "Error", "Could not save file");
    }
}

void MainWindow::on_actionDrawLine_triggered()
{
    drawingArea->setCurrentShape(Shape::Line);
}

void MainWindow::on_actionDrawRectangle_triggered()
{
    drawingArea->setCurrentShape(Shape::Rectangle);
}

void MainWindow::on_actionDrawPolyline_triggered()
{
    drawingArea->setCurrentShape(Shape::Polyline);
}

void MainWindow::on_actionDrawEllipse_triggered()
{
    drawingArea->setCurrentShape(Shape::Ellipse);
}

void MainWindow::on_actionEditSelect_triggered()
{
    drawingArea->setCurrentShape(Shape::Select);
}

void MainWindow::on_actionEditMove_triggered()
{
    Shape* selectedShape = drawingArea->getSelectedShape();
    if (selectedShape) {
        moveDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            QPointF offset(dialog.getDx(), dialog.getDy());
            selectedShape->move(offset);
            drawingArea->update();
        }
    } else {
        QMessageBox::information(this, "Info", "No shape selected");
    }
}

void MainWindow::on_actionEditColor_triggered()
{
    Shape* selectedShape = drawingArea->getSelectedShape();
    if (selectedShape) {
        QColor color = QColorDialog::getColor(selectedShape->getPen().color(), this, "Select Color");
        if (color.isValid()) {
            QPen pen = selectedShape->getPen();
            pen.setColor(color);
            selectedShape->setPen(pen);
            drawingArea->update();
        }
    } else {
        QMessageBox::information(this, "Info", "No shape selected");
    }
}

void MainWindow::showShapeProperties(Shape* shape)
{
    if (!shape) {
        ui->statusbar->showMessage("No shape selected", 2000);
        return;
    }

    QString typeStr;
    switch (shape->getType()) {
    case Shape::Line: typeStr = "Line"; break;
    case Shape::Rectangle: typeStr = "Rectangle"; break;
    case Shape::Ellipse: typeStr = "Ellipse"; break;
    case Shape::Polyline: typeStr = "Polyline"; break;
    default: typeStr = "Unknown"; break;
    }

    QString message = QString("Selected: %1").arg(typeStr);

    if (shape->getType()==Shape::Line || shape->getType()==Shape::Polyline)
        message += QString(" | Length: %1 px").arg(shape->calculatePerimeter(), 0, 'f', 2);
    else
        message += QString(" | Area: %1 | Perimeter: %2 ").arg(shape->calculateArea(), 0, 'f', 2).arg(shape->calculatePerimeter(), 0, 'f', 2);


    ui->statusbar->showMessage(message, 5000);
}
