#include <QDebug>
#include <QToolBar>
#include <QList>
#include <QMenuBar>
#include <QDockWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "Menu.h"
#include "MainWindow.h"
#include <QObjectList>
#include <QDebug>


MainWindow::MainWindow(){
    menu = new MenuBar(this);
    menu->setObjectName("menu");
    setMenuBar(menu);
    toolBar = new ToolBar(this);
    toolBar->setObjectName("toolbar");
    addToolBar(Qt::LeftToolBarArea, toolBar);
    canvas = new Canvas(this);
    canvas->setObjectName("canvas");
    // layout->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(canvas);
    centralWidget()->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    centralWidget()->setContentsMargins(0,0,0,0);

    // centralWidget()->setFixedHeight(sizeHint().height());
    // layout()->setContentsMargins(0, 0, 0, 0);
    // canvas->setSizePolicy();
    // QLayout *centralLayout = centralWidget()->layout();
    // layout()->setSpacing(0);
}

void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);
    centralWidget()->resize(event->size());
}

