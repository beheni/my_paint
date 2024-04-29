#include <QToolBar>
#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>
#include "Menu.h"
#include "MainWindow.h"

MainWindow::MainWindow(){
    menu = new Menu(this);
    setMenuBar(menu);
    toolBar = new ToolBar(this);
    addToolBar(Qt::LeftToolBarArea, toolBar);

}
