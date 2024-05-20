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
#include <QUndoView>


MainWindow::MainWindow(){
    menu = new MenuBar(this);
    menu->setObjectName("menu");
    setMenuBar(menu);
    Menu* editMenu = menu->getEditMenu();
    editMenu->addSeparator();

    undoStack = new QUndoStack(this);

    QAction* undoAction = undoStack->createUndoAction(this, tr("Undo"));
    undoAction->setShortcut(QKeySequence::Undo);
    editMenu->addAction(undoAction);

    QAction* redoAction = undoStack->createRedoAction(this, tr("Redo"));
    redoAction->setShortcut(QKeySequence::Redo);
    editMenu->addAction(redoAction);


    connect(menu->exitAction(), &QAction::triggered, this, &MainWindow::exitEvent);
    connect(menu->openAction(), &QAction::triggered, this, &MainWindow::openEvent);
    connect(menu->saveAction(), &QAction::triggered, this, &MainWindow::saveEvent);
    connect(menu->newAction(), &QAction::triggered, this, &MainWindow::newEvent);
    connect(menu->helpAction(), &QAction::triggered, this, &MainWindow::helpEvent);


    createUndoView();


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
    // connect(layerBar->layerWidget(), &LayerWidget::layerSwap, canvas, &Canvas::onLayerSwap);
    // connect(layerBar->upLayer(), &QPushButton::pressed, layerBar->layerWidget(), &LayerWidget::onLayerUp);
    // connect(layerBar->downLayer(), &QPushButton::pressed, layerBar->layerWidget(), &LayerWidget::onLayerDown);

    connect(layerBar->thicknessSlider(), &QSlider::valueChanged, canvas, &Canvas::onThicknessChange);
    connect(canvas, &Canvas::objectAdded, this, &MainWindow::onObjectAdded);
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

void MainWindow::helpEvent() {
    QMessageBox::information(this, "Help", "This is a simple paint application. \n"
                                           "You can draw on the canvas with the selected tool. \n"
                                           "You can change the color and thickness of the tool. \n"
                                           "You can add and remove layers. \n"
                                           "You can save and open files in SVG format. \n"
                                           "You can exit the application. \n"
                                           "Enjoy drawing!\n"
                                            "For more info visit beheni\\my_paint at Github");

}

void MainWindow::createUndoView()
{
    //треба додати в нормальну частину або сказати шо так і задумували
    QDockWidget *undoDockWidget = new QDockWidget;
    undoDockWidget->setWindowTitle(tr("Command List"));
    undoDockWidget->setWidget(new QUndoView(undoStack));
    undoDockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    undoDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, undoDockWidget);
}

void MainWindow::onObjectAdded(QGraphicsItem *item) {
    qDebug() << "Object added";
    // undoStack->push(new QUndoCommand(QString("Object added on canvas"))); //basic vertion just with text
    auto addCommand = new AddCommand(canvas, item);
    addCommand->setText("Object added on canvas");
    undoStack->push(addCommand);
}

AddCommand::AddCommand(Canvas *canvas, QGraphicsItem *item, QUndoCommand *parent): QUndoCommand(parent), item(item), canvas(canvas) {
}

void AddCommand::undo() {
    canvas->scene()->removeItem(item);
    // canvas->currentLayer()->removeFromGroup(item);
    // canvas->layerItems()[canvas->currentLayer()].removeOne(item);
    canvas->scene()->update();
    qDebug() << "undo";
}

void AddCommand::redo() {
    canvas->scene()->addItem(item);
    // canvas->currentLayer()->addToGroup(item);
    // canvas->layerItems()[canvas->currentLayer()].push_back(item);
    canvas->scene()->update();
    qDebug() << "redo";
}

