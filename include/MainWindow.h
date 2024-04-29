#ifndef MY_PAINT_MAINWINDOW_H
#define MY_PAINT_MAINWINDOW_H
#include <QMainWindow>
#include "Canvas.h"
#include "Menu.h"
#include "ContextMenu.h"
#include "Tool.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
    Canvas canvas;
    Menu menu;
    ContextMenu context;
    Tool currentTool;
// private slots:
    // void open();
    // void save();
public:
    MainWindow();
    // ~MainWindow() override = default;
    // int run();
};

#endif //MY_PAINT_MAINWINDOW_H
