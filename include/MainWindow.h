#ifndef MY_PAINT_MAINWINDOW_H
#define MY_PAINT_MAINWINDOW_H
#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QUndoStack>
#include <QUndoView>
#include <QUndoCommand>
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
    QUndoView *undoView = nullptr;
public slots:
    //menu slots
    void openEvent();
    void saveEvent();
    void newEvent();
    void exitEvent();
    void helpEvent();

    //canvas slots
    void onObjectAdded(QGraphicsItem* item);
    // void onObjectMoved(QGraphicsItem* item);
    // void onObjectRemoved(QGraphicsItem* item);
    // void onLayerAdded(Layer* layer);
    // void onLayerRemoved(Layer* layer);
    // void onLayerSwapped(size_t index1, size_t index2);


public:
    explicit MainWindow();
    void resizeEvent(QResizeEvent *event) override;
    void createUndoView();
    // ~MainWindow() override = default;

};


class AddCommand: public QUndoCommand
{
public:
    QGraphicsItem* item;
    Canvas* canvas;
    AddCommand(Canvas* canvas, QGraphicsItem* item,
               QUndoCommand *parent = nullptr);
    ~AddCommand() = default;

    void undo() override;
    void redo() override;
};

#endif //MY_PAINT_MAINWINDOW_H
