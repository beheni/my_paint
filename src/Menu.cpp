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
    QAction* exitAction = file->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &MenuBar::onExit);
    Menu *edit = new Menu("&Edit");
    Menu *view = new Menu("&View");
    Menu *help = new Menu("&Help");

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

void MenuBar::onExit() {
    QMessageBox::StandardButton exit = QMessageBox::question(this, "Exit",
                                                               tr("Are you sure want to exit?\n"),
                                                               QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                               QMessageBox::Yes);
    if (exit==QMessageBox::Yes) {
        QApplication::quit();
    }
}
