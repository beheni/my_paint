#include "Menu.h"
#include <QSize>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QSvgGenerator>
#include <QFileDialog>
#include <QGraphicsPixmapItem>

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent) {
    Menu *file = new Menu("&File");
    file->addAction("New");
    QAction* openAction = file->addAction("Open");

    QAction* saveAction = file->addAction("Save");
    connect(saveAction, &QAction::triggered, this, &MenuBar::onSave);
    connect(openAction, &QAction::triggered, this, &MenuBar::onOpen);

    file->addSeparator();
    exitAction_ = file->addAction("Exit");
    Menu *edit = new Menu("&Edit");
    QAction* editAction = edit->addAction("Undo");
    // connect(editAction, &QAction::triggered, this, &MenuBar::onUndo);
    QAction* redoAction = edit->addAction("Redo");
    edit->addSeparator();
    // connect(redoAction, &QAction::triggered, this, &MenuBar::onRedo);
    QAction* cutAction = edit->addAction("Cut");
    // connect(cutAction, &QAction::triggered, this, &MenuBar::onCut);
    QAction* copyAction = edit->addAction("Copy");
    // connect(copyAction, &QAction::triggered, this, &MenuBar::onCopy);
    QAction* pasteAction = edit->addAction("Paste");
    // connect(pasteAction, &QAction::triggered, this, &MenuBar::onPaste);

    Menu *view = new Menu("&View");
    QAction* zoomInAction = view->addAction("Zoom In");
    QAction* zoomOutAction = view->addAction("Zoom Out");
    QAction* zoomResetAction = view->addAction("Zoom Reset");
    Menu *help = new Menu("&Help");
    QAction* helpAction = help->addAction("About");

    addMenu(file);
    addMenu(edit);
    addMenu(view);
    addMenu(help);

}

void MenuBar::setCanvas(Canvas *canvas_) {
    canvas = canvas_;
}


Menu::Menu(const QString &title, QWidget *parent) : QMenu(title, parent) {}

void MenuBar::onSave() {
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

void MenuBar::onOpen(){
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

QAction *MenuBar::exitAction() {
    return exitAction_;
}
