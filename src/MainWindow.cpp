#include <QToolBar>
#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>
#include "Menu.h"
#include "MainWindow.h"

MainWindow::MainWindow(){
    menu = new MenuBar(this);
    setMenuBar(menu);
    toolBar = new ToolBar(this);
    addToolBar(Qt::LeftToolBarArea, toolBar);
    canvas = new Canvas(this);
    setCentralWidget(canvas);
}
