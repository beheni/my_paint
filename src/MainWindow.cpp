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
#include <QColorDialog>
#include <QMessageBox>


MainWindow::MainWindow(){
    menu = new MenuBar(this);
    menu->setObjectName("menu");
    setMenuBar(menu);
    connect(menu->exitAction(), &QAction::triggered, this, &MainWindow::exitEvent);

    toolBar = new ToolBar(this);
    toolBar->setObjectName("toolbar");

    layerBar = new LayerBar(this);
    layerBar->setObjectName("layerbar");


    addToolBar(Qt::LeftToolBarArea, toolBar);
    addToolBar(Qt::RightToolBarArea, layerBar);
    canvas = new Canvas(this);
    scene = new QGraphicsScene(this);
    toolBar->setCanvas(canvas);
    toolBar->setup();

    menu->setCanvas(canvas);
    canvas->setScene(scene);
    canvas->scene()->setSceneRect(0, 0, canvas->width(), canvas->height());
    canvas->setObjectName("canvas");

    Layer* currentLayer = new Layer();
    canvas->layers().push_back(currentLayer);
    canvas->layerItems()[currentLayer] = QList<QGraphicsItem*>();
    canvas->setCurrentLayer(currentLayer);
    canvas->scene()->addItem(currentLayer);

    setCentralWidget(canvas);
    centralWidget()->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    centralWidget()->setContentsMargins(0,0,0,0);
    centralWidget()->show();

    connect(layerBar->colorPicker(), &QColorDialog::currentColorChanged, canvas, &Canvas::onColorChange);
    connect(layerBar->addLayer(), &QPushButton::pressed, canvas, &Canvas::onLayerAdd);
    connect(layerBar->addLayer(), &QPushButton::pressed, layerBar->layerWidget(), &LayerWidget::onLayerAdd);

    connect(layerBar->removeLayer(), &QPushButton::pressed, layerBar->layerWidget(), &LayerWidget::onLayerRemove);
    connect(layerBar->layerWidget(), &LayerWidget::layerRemove, canvas, &Canvas::onLayerRemove);
    connect(layerBar->layerWidget(), &QListWidget::currentRowChanged, canvas, &Canvas::onLayerChange);

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
