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
#include <QFileDialog>
#include <QSvgGenerator>
#include <QColorDialog>
#include <QMessageBox>


MainWindow::MainWindow(){
    menu = new MenuBar(this);
    menu->setObjectName("menu");
    setMenuBar(menu);
    connect(menu->exitAction(), &QAction::triggered, this, &MainWindow::exitEvent);
    connect(menu->openAction(), &QAction::triggered, this, &MainWindow::openEvent);
    connect(menu->saveAction(), &QAction::triggered, this, &MainWindow::saveEvent);
    connect(menu->newAction(), &QAction::triggered, this, &MainWindow::newEvent);


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
    connect(layerBar->layerWidget(), &LayerWidget::layerSwap, canvas, &Canvas::onLayerSwap);
    connect(layerBar->upLayer(), &QPushButton::pressed, layerBar->layerWidget(), &LayerWidget::onLayerUp);
    connect(layerBar->downLayer(), &QPushButton::pressed, layerBar->layerWidget(), &LayerWidget::onLayerDown);

    connect(layerBar->thicknessSlider(), &QSlider::valueChanged, canvas, &Canvas::onThicknessChange);

}

void MainWindow::resizeEvent(QResizeEvent* event){
    QMainWindow::resizeEvent(event);
    QSize newSize = canvas->size();
    canvas->scene()->setSceneRect(0,0, newSize.width(), newSize.height());
}

void MainWindow::newEvent(){
    qDebug() << "new event";
}

void MainWindow::openEvent(){
    QString filename = QFileDialog::getOpenFileName(this, "Open", "");
    if (filename.isEmpty()) {
        return;
    }
    canvas->scene()->clear();
    auto* pixmap = new QGraphicsPixmapItem(QPixmap(filename));
    canvas->scene()->addItem(pixmap);
    canvas->scene()->setSceneRect(pixmap->boundingRect());
    QMessageBox::information(this, "Open", "Canvas loaded from " + filename);

}

void MainWindow::saveEvent(){
    QSvgGenerator generator;
    QString filename = QFileDialog::getSaveFileName(this, "Save", "canvas.svg", "SVG files (*.svg)");
    if (filename.isEmpty()) {
        return;
    }
    generator.setFileName(filename);
    generator.setSize(canvas->size());
    generator.setViewBox(canvas->scene()->sceneRect()); //size to be changed
    QPainter painter;
    painter.begin(&generator);
    canvas->render(&painter);
    painter.end();
    QMessageBox::information(this, "Save", "Canvas saved to canvas.svg");
}

void MainWindow::exitEvent(){
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
        QMainWindow::close();
}
