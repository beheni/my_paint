#ifndef MY_PAINT_MAINWINDOW_H
#define MY_PAINT_MAINWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include "Canvas.h"
#include "Menu.h"
#include "ToolBar.h"
#include "Tool.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
    Canvas* canvas;
    MenuBar* menu;
    ToolBar* toolBar; //якась збірка тулів
    // Tool currentTool;
    QGraphicsScene * scene;
    QPainter * currentTool;


public:
    explicit MainWindow();
    void resizeEvent(QResizeEvent *event) override;
    // ~MainWindow() override = default;

};

#endif //MY_PAINT_MAINWINDOW_H
