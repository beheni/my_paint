#include <QDebug>
#include <QToolBar>
#include <QList>
#include <QMenuBar>
#include <QDockWidget>
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
    // QVBoxLayout *layout = new QVBoxLayout(canvas);
    // layout->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(canvas);
    // layout()->setContentsMargins(0, 0, 0, 0);
    // canvas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // QLayout *centralLayout = centralWidget()->layout();
    // if (centralLayout)
    //     centralLayout->setContentsMargins(0, 0, 0, 0);
    // layout()->setSpacing(0);
}
