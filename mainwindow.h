#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawingarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionFileNew_triggered();
    void on_actionFileOpen_triggered();
    void on_actionFileSave_triggered();

    void on_actionDrawLine_triggered();
    void on_actionDrawRectangle_triggered();
    void on_actionDrawPolyline_triggered();
    void on_actionDrawEllipse_triggered();

    void on_actionEditSelect_triggered();
    void on_actionEditMove_triggered();
    void on_actionEditColor_triggered();

    void showShapeProperties(Shape* shape);

private:
    Ui::MainWindow *ui;
    DrawingArea *drawingArea;
};

#endif // MAINWINDOW_H
