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
#include <QMessageBox>


MainWindow::MainWindow(){
    menu = new MenuBar(this);
    menu->setObjectName("menu");
    setMenuBar(menu);
    connect(menu->exitAction(), &QAction::triggered, this, &MainWindow::exitEvent);

    toolBar = new ToolBar(this);
    toolBar->setObjectName("toolbar");
    addToolBar(Qt::LeftToolBarArea, toolBar);

    canvas = new Canvas(this);
    scene = new QGraphicsScene(this);
    toolBar->setCanvas(canvas);
    toolBar->setup();
    menu->setCanvas(canvas);
    canvas->setScene(scene);
    canvas->scene()->setSceneRect(0, 0, canvas->width(), canvas->height());
    canvas->setObjectName("canvas");
    setCentralWidget(canvas);
    centralWidget()->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    centralWidget()->setContentsMargins(0,0,0,0);
    centralWidget()->show();

}

void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);
    QSize newSize = canvas->size();
    canvas->scene()->setSceneRect(0,0, newSize.width(), newSize.height());
}

void MainWindow::exitEvent(){
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
        QMainWindow::close();
}
