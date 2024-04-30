#ifndef MY_PAINT_MAINWINDOW_H
#define MY_PAINT_MAINWINDOW_H
#include <QMainWindow>
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
    Tool currentTool;
// private slots:
    // void open();
    // void save();
public:
    explicit MainWindow();
    void resizeEvent(QResizeEvent *event) override;
    // ~MainWindow() override = default;
    // int run();
// private:
    // void setupVToolBar();
    // void setupMenu(); //QMenu from each


};

#endif //MY_PAINT_MAINWINDOW_H
