#ifndef MY_PAINT_MAINWINDOW_H
#define MY_PAINT_MAINWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QUndoStack>
#include "Canvas.h"
#include "Menu.h"
#include "ToolBar.h"
#include "LayerBar.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
    Canvas* canvas;
    MenuBar* menu;
    ToolBar* toolBar; //якась збірка тулів
    LayerBar* layerBar;
    // Tool currentTool;
    QGraphicsScene * scene;
    QPainter * currentTool;
    QUndoStack * undoStack = nullptr;
public slots:
    void openEvent();
    void saveEvent();
    void newEvent();
    void exitEvent();

public:
    explicit MainWindow();
    void resizeEvent(QResizeEvent *event) override;
    // ~MainWindow() override = default;

};

#endif //MY_PAINT_MAINWINDOW_H
